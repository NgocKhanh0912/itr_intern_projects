/**
 * @file       sys_button.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-13
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Layer controls button events
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_button.h"
#include "bsp_timer.h"
#include "bsp_utils.h"
#include "common.h"
#include <stdbool.h>

/* Private defines ---------------------------------------------------- */
#define SYS_BUTTON_MAX_EVT (3)

#define SYS_BUTTON_EVT_SINGLE_CLICK_CB (0)
#define SYS_BUTTON_EVT_DOUBLE_CLICK_CB (1)
#define SYS_BUTTON_EVT_HOLD_CB (2)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
sys_button_t s_button;
sys_button_evt_cb_t s_button_evt_cb[SYS_BUTTON_MAX_EVT] = {0};
/* Private function prototypes ---------------------------------------- */
static void sys_button_detect_edge(uint16_t exti_line);
/* Function definitions ----------------------------------------------- */
sys_button_status_t sys_button_init(GPIO_TypeDef *gpio, uint16_t pin, uint32_t button_active_level)
{
  drv_button_t dbutton;
  drv_button_status_t ret = DRV_BUTTON_OK;

  ret = drv_button_init(&dbutton, gpio, pin, button_active_level);
  __ASSERT(ret == DRV_BUTTON_OK, SYS_BUTTON_FAIL);

  s_button.dbutton = dbutton;
  s_button.transient_state = SYS_BUTTON_STATE_STABLE;
  s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
  drv_button_register_callback(sys_button_detect_edge);

  return SYS_BUTTON_OK;
}

sys_button_status_t sys_button_manage()
{
  if (s_button.transient_state == SYS_BUTTON_STATE_DEBOUNCE)
  {
    if (HAL_GetTick() - s_button.dbutton.time_debounce >= BUTTON_DEBOUNCE_TIME)
    {
      uint32_t button_current_state = bsp_gpio_read_pin(s_button.dbutton.port, s_button.dbutton.pin);
      if (button_current_state != s_button.dbutton.current_state)
      {
        s_button.dbutton.current_state = button_current_state;
      }
      s_button.transient_state = SYS_BUTTON_STATE_STABLE;
    }
  }

  switch (s_button.fsm_state)
  {
  case SYS_BUTTON_FSM_STATE_IDLE:
  {
    if (s_button.dbutton.current_state == s_button.dbutton.active_level)
    {
      s_button.fsm_state = SYS_BUTTON_FSM_STATE_PRESS;
      s_button.dbutton.time_change = bsp_utils_get_tick();
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_PRESS:
  {
    uint32_t current_tick = bsp_utils_get_tick();
    if (s_button.dbutton.current_state != s_button.dbutton.active_level)
    {
      if (current_tick - s_button.dbutton.time_change < BUTTON_SINGLE_CLICK_TIME)
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_WAIT_SINGLE_CLICK;
        s_button.dbutton.time_change = bsp_utils_get_tick();
      }
      else
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
      }
    }
    else if ((s_button.dbutton.current_state == s_button.dbutton.active_level) &&
             (current_tick - s_button.dbutton.time_change >= BUTTON_SINGLE_CLICK_TIME))
    {
      s_button.fsm_state = SYS_BUTTON_FSM_STATE_WAIT_HOLD;
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_WAIT_SINGLE_CLICK:
  {
    uint32_t current_tick = bsp_utils_get_tick();
    if (current_tick - s_button.dbutton.time_change >= BUTTON_RELEASE_TIME)
    {
      if (s_button.dbutton.current_state != s_button.dbutton.active_level)
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_SINGLE_CLICK;
      }
    }
    else if ((s_button.dbutton.current_state == s_button.dbutton.active_level) &&
             (current_tick - s_button.dbutton.time_change < BUTTON_RELEASE_TIME))
    {
      s_button.fsm_state = SYS_BUTTON_FSM_STATE_WAIT_DOUBLE_CLICK;
      s_button.dbutton.time_change = bsp_utils_get_tick();
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_WAIT_DOUBLE_CLICK:
  {
    uint32_t current_tick = bsp_utils_get_tick();
    if (s_button.dbutton.current_state != s_button.dbutton.active_level)
    {
      if (current_tick - s_button.dbutton.time_change < BUTTON_SINGLE_CLICK_TIME)
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_DOUBLE_CLICK;
      }
      else
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
      }
    }
    else if ((s_button.dbutton.current_state == s_button.dbutton.active_level) &&
             (current_tick - s_button.dbutton.time_change >= BUTTON_SINGLE_CLICK_TIME))
    {
      s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_WAIT_HOLD:
  {
    uint32_t current_tick = bsp_utils_get_tick();
    if (current_tick - s_button.dbutton.time_change >= BUTTON_HOLD_TIME)
    {
      if (s_button.dbutton.current_state == s_button.dbutton.active_level)
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_HOLD;
      }
      else
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
      }
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_WAIT_RELEASE:
  {
    uint32_t current_tick = bsp_utils_get_tick();
    if (s_button.dbutton.current_state != s_button.dbutton.active_level)
    {
      if (current_tick - s_button.dbutton.time_change >= BUTTON_RELEASE_TIME)
      {
        s_button.fsm_state = SYS_BUTTON_FSM_STATE_RELEASE;
      }
    }
    break;
  }

  case SYS_BUTTON_FSM_STATE_SINGLE_CLICK:
  {
    __CALLBACK(s_button_evt_cb[SYS_BUTTON_EVT_SINGLE_CLICK_CB]);
    s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
    break;
  }

  case SYS_BUTTON_FSM_STATE_DOUBLE_CLICK:
  {
    __CALLBACK(s_button_evt_cb[SYS_BUTTON_EVT_DOUBLE_CLICK_CB]);
    s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
    break;
  }

  case SYS_BUTTON_FSM_STATE_HOLD:
  {
    __CALLBACK(s_button_evt_cb[SYS_BUTTON_EVT_HOLD_CB]);
    s_button.fsm_state = SYS_BUTTON_FSM_STATE_WAIT_RELEASE;
    s_button.dbutton.time_change = bsp_utils_get_tick();
    break;
  }

  case SYS_BUTTON_FSM_STATE_RELEASE:
  {
    s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
    break;
  }

  default:
  {
    s_button.fsm_state = SYS_BUTTON_FSM_STATE_IDLE;
    break;
  }
  }
  return SYS_BUTTON_OK;
}

sys_button_status_t sys_button_register_cb_function(sys_button_evt_cb_t single_click,
                                                    sys_button_evt_cb_t double_click,
                                                    sys_button_evt_cb_t hold)
{
  __ASSERT(single_click != NULL, SYS_BUTTON_ERROR);
  __ASSERT(double_click != NULL, SYS_BUTTON_ERROR);
  __ASSERT(hold != NULL, SYS_BUTTON_ERROR);

  s_button_evt_cb[SYS_BUTTON_EVT_SINGLE_CLICK_CB] = single_click;
  s_button_evt_cb[SYS_BUTTON_EVT_DOUBLE_CLICK_CB] = double_click;
  s_button_evt_cb[SYS_BUTTON_EVT_HOLD_CB] = hold;

  return SYS_BUTTON_OK;
}
/* Private definitions ------------------------------------------------ */
static void sys_button_detect_edge(uint16_t exti_line)
{
  if ((s_button.dbutton.pin == exti_line) &&
      (s_button.transient_state == SYS_BUTTON_STATE_STABLE))
  {
    s_button.transient_state = SYS_BUTTON_STATE_DEBOUNCE;
    s_button.dbutton.time_debounce = bsp_utils_get_tick();
  }
}
/* End of file -------------------------------------------------------- */
