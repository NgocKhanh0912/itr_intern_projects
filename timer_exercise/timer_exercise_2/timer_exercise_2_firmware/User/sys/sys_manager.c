/**
 * @file       sys_manager.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-13
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Manage all components of system.
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_manager.h"
#include "sys_button.h"
#include "sys_led.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
sys_manager_state_t sys_manager_state = SYS_MANAGER_STATE_IDLE;
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
sys_manager_status_t sys_manager_loop()
{
  static sys_button_evt_t sys_button_evt = SYS_BUTTON_EVT_NONE;
  sys_button_evt = sys_button_manage();
  switch (sys_manager_state)
  {
  case SYS_MANAGER_STATE_IDLE:
  {
    sys_led_manage(SYS_LED_STATE_LED_IDLE);
    if (sys_button_evt == SYS_BUTTON_EVT_SINGLE_CLICK)
    {
      sys_manager_state = SYS_MANAGER_STATE_RED_BLINK;
    }
    sys_led_change_effect(false);
    break;
  }
  case SYS_MANAGER_STATE_RED_BLINK:
  {
    sys_led_change_effect(false);

    sys_led_manage(SYS_LED_STATE_LED_RED_BLINK);
    if (sys_button_evt == SYS_BUTTON_EVT_DOUBLE_CLICK)
    {
      sys_manager_state = SYS_MANAGER_STATE_RED_WAIT_TRANSIT;
    }
    else if (sys_button_evt == SYS_BUTTON_EVT_HOLD)
    {
      sys_manager_state = SYS_MANAGER_STATE_RED_WAIT_OFF;
    }
    break;
  }

  case SYS_MANAGER_STATE_RED_WAIT_TRANSIT:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_GREEN_BLINK;
    }
    break;
  }

  case SYS_MANAGER_STATE_GREEN_BLINK:
  {
    sys_led_change_effect(false);

    sys_led_manage(SYS_LED_STATE_LED_GREEN_BLINK);
    if (sys_button_evt == SYS_BUTTON_EVT_DOUBLE_CLICK)
    {
      sys_manager_state = SYS_MANAGER_STATE_GREEN_WAIT_TRANSIT;
    }
    else if (sys_button_evt == SYS_BUTTON_EVT_HOLD)
    {
      sys_manager_state = SYS_MANAGER_STATE_GREEN_WAIT_OFF;
    }
    break;
  }

  case SYS_MANAGER_STATE_GREEN_WAIT_TRANSIT:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_BLUE_BLINK;
    }
    break;
  }

  case SYS_MANAGER_STATE_BLUE_BLINK:
  {
    sys_led_change_effect(false);

    sys_led_manage(SYS_LED_STATE_LED_BLUE_BLINK);
    if (sys_button_evt == SYS_BUTTON_EVT_DOUBLE_CLICK)
    {
      sys_manager_state = SYS_MANAGER_STATE_BLUE_WAIT_TRANSIT;
    }
    else if (sys_button_evt == SYS_BUTTON_EVT_HOLD)
    {
      sys_manager_state = SYS_MANAGER_STATE_BLUE_WAIT_OFF;
    }
    break;
  }

  case SYS_MANAGER_STATE_BLUE_WAIT_TRANSIT:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_RED_BLINK;
    }
    break;
  }

  case SYS_MANAGER_STATE_RED_WAIT_OFF:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_IDLE;
    }
    break;
  }

  case SYS_MANAGER_STATE_GREEN_WAIT_OFF:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_IDLE;
    }
    break;
  }

  case SYS_MANAGER_STATE_BLUE_WAIT_OFF:
  {
    if (sys_led_ready_to_change_effect())
    {
      sys_manager_state = SYS_MANAGER_STATE_IDLE;
    }
    break;
  }

  default:
    break;
  }

  return SYS_MANAGER_OK;
}
/* Private definitions ------------------------------------------------ */

/* End of file -------------------------------------------------------- */
