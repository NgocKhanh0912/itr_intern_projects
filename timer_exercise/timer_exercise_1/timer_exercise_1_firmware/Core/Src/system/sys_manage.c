/**
 * @file       sys_manage.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      System for manage fsm of the system
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "system/sys_manage.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static sys_fsm_state_t fsm_state = IDLE;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
sys_status_t sys_init(bsp_gpio_t *BUTTON, bsp_gpio_t *LED,
                      drv_led_active_level_t led_active_level,
                      TIM_HandleTypeDef *htim, uint32_t prescaler, uint32_t autoreload)
{
  sys_led_init(LED, led_active_level);
  drv_button_init(BUTTON);
  bsp_timer_set_autoreload(htim, autoreload);
  bsp_timer_set_prescaler(htim, prescaler);
  bsp_timer_start_it(htim);
  return SYS_OK;
}

sys_status_t sys_manage_fsm(bsp_gpio_t *LED,
                            drv_led_active_level_t led_active_level,
                            sys_button_evt_t button_evt,
                            bool *timer_flag)
{
  switch(fsm_state)
  {
    case IDLE: 
      if (button_evt == BUTTON_EVT_SINGLE_CLICK) 
      {
        fsm_state = LED1_BLINK;
      }
      break;

    case LED1_BLINK:
      switch (button_evt)
      {
        case BUTTON_EVT_DOUBLE_CLICK:
          fsm_state = LED1_WAIT_TRANSIT;
          break;
        case BUTTON_EVT_HOLD:
          fsm_state = LED1_WAIT_OFF;
          break;
        default:
          break;
      }
      break;

    case LED1_WAIT_TRANSIT:
      if (*timer_flag == 1) 
      {
        fsm_state = LED2_BLINK;
        *timer_flag = 0;
      }
      break;

    case LED1_WAIT_OFF:
      if (*timer_flag == 1) 
      {
        fsm_state = IDLE;
        *timer_flag = 0;
      }
      break;

    case LED2_BLINK:
      switch (button_evt)
      {
        case BUTTON_EVT_DOUBLE_CLICK:
          fsm_state = LED2_WAIT_TRANSIT;
          break;
        case BUTTON_EVT_HOLD:
          fsm_state = LED2_WAIT_OFF;
          break;
        default:
          break;
      }
      break;

    case LED2_WAIT_TRANSIT:
      if (*timer_flag == 1) 
      {
        fsm_state = LED3_BLINK;
        *timer_flag = 0;
      }
      break;

    case LED2_WAIT_OFF:
      if (*timer_flag == 1) 
      {
        fsm_state = IDLE;
        *timer_flag = 0;
      }
      break;

    case LED3_BLINK:
      switch (button_evt)
      {
        case BUTTON_EVT_DOUBLE_CLICK:
          fsm_state = LED3_WAIT_TRANSIT;
          break;
        case BUTTON_EVT_HOLD:
          fsm_state = LED3_WAIT_OFF;
          break;
        default:
          break;
      }
      break;

    case LED3_WAIT_TRANSIT:
      if (*timer_flag == 1) 
      {
        fsm_state = LED1_BLINK;
        *timer_flag = 0;
      }
      break;
    
    case LED3_WAIT_OFF:
      if (*timer_flag == 1) 
      {
        fsm_state = IDLE;
        *timer_flag = 0;
      }
      break;
  }

  switch(fsm_state)
  {
    case(IDLE):
      sys_led_effect_for_sys_state_0(LED, led_active_level);
      break;

    case(LED1_BLINK):
      while (*timer_flag)
      {
        sys_led_effect_for_sys_state_1(LED, led_active_level);
        *timer_flag = 0;
      }
      break;

    case(LED2_BLINK):
      while (*timer_flag)
      {
        sys_led_effect_for_sys_state_2(LED, led_active_level);
        *timer_flag = 0;
      }
      break;

      case(LED3_BLINK):
      while (*timer_flag)
      {
        sys_led_effect_for_sys_state_3(LED, led_active_level);
        *timer_flag = 0;
      }
      break;

    default:
      break;
  }

  return SYS_OK;
}


/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
