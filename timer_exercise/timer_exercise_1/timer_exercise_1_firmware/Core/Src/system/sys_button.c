/**
 * @file       sys_button.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      System for interfacing and manage fsm of the button
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "system/sys_button.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static sys_button_state_t button_current_state = BUTTON_STATE_IDLE;
static uint32_t start_tick = 0;
static GPIO_PinState button_state = 0;
static sys_button_evt_t button_evt = BUTTON_EVT_NONE;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
sys_button_evt_t sys_button_fsm(bsp_gpio_t *gpio_button)
{
  switch (button_current_state)
  {
    case BUTTON_STATE_IDLE:
    {
      button_evt = BUTTON_EVT_NONE;
      button_state = drv_button_read_pin(gpio_button);
      if (button_state == 1)
        {
          button_current_state = BUTTON_STATE_DETECT_POSEDGE;
          start_tick = drv_button_get_tick();
        }
      break;
    }

    case BUTTON_STATE_DETECT_POSEDGE:
    {
      if ((drv_button_get_tick() - start_tick) >= BUTTON_DEBOUNCE_TIME)
        {
          button_state = drv_button_read_pin(gpio_button);
          if (button_state == 0)
            {
              button_current_state = BUTTON_STATE_IDLE;
            }
          else
            {
              button_current_state = BUTTON_STATE_DETECT_SINGLE_CLICK;
              start_tick = drv_button_get_tick();
            }
      }
      break;
    }

    case BUTTON_STATE_DETECT_SINGLE_CLICK:
    {
      button_state = drv_button_read_pin(gpio_button);
      if ((button_state == 0) && ((drv_button_get_tick() - start_tick) < BUTTON_CLICK_TIME))
        {
          button_current_state = BUTTON_STATE_END_SINGLE_CLICK;
          start_tick = drv_button_get_tick();
        }
      else if ((drv_button_get_tick() - start_tick) >= BUTTON_CLICK_TIME)
        {
          button_current_state = BUTTON_STATE_DETECT_HOLD;
        }
      break;
    }

    case BUTTON_STATE_END_SINGLE_CLICK:
    {
      button_state = drv_button_read_pin(gpio_button);
      if ((button_state == 0) && (drv_button_get_tick() - start_tick) >= BUTTON_RELEASE_TIME)
        {
          button_current_state = BUTTON_STATE_SINGLE_CLICK;
        }
      else if ((button_state == 1) && (drv_button_get_tick() - start_tick) < BUTTON_RELEASE_TIME)
        {
          button_current_state = BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK;
          start_tick = drv_button_get_tick();
        }
      break;
    }

    case BUTTON_STATE_SINGLE_CLICK:
    {
      button_evt = BUTTON_EVT_SINGLE_CLICK;
      button_current_state = BUTTON_STATE_IDLE;
      break;
    }

    case BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK:
    {
      if ((drv_button_get_tick() - start_tick) >= BUTTON_DEBOUNCE_TIME)
      {
        button_state = drv_button_read_pin(gpio_button);
        if (button_state == 0)
        {
          button_current_state = BUTTON_STATE_SINGLE_CLICK;
        }
        else if (button_state == 1)
        {
          button_current_state = BUTTON_STATE_DETECT_DOUBLE_CLICK;
          start_tick = drv_button_get_tick();
        }
      }
      break;
    }
    case BUTTON_STATE_DETECT_DOUBLE_CLICK:
    {
      button_state = drv_button_read_pin(gpio_button);
      if ((button_state == 0) && ((drv_button_get_tick() - start_tick) < BUTTON_CLICK_TIME))
      {
        button_current_state = BUTTON_STATE_DOUBLE_CLICK;
      }
      else if ((button_state == 1) && ((drv_button_get_tick() - start_tick) >= BUTTON_CLICK_TIME))
      {
        button_current_state = BUTTON_STATE_ERROR_HANDLER;
      }
      break;
    }

    case BUTTON_STATE_DOUBLE_CLICK:
    {
      button_evt = BUTTON_EVT_DOUBLE_CLICK;
      button_current_state =BUTTON_STATE_IDLE;
      break;
    }

    case BUTTON_STATE_DETECT_HOLD:
    {
      button_state = drv_button_read_pin(gpio_button);
      if ((button_state == 0) && ((drv_button_get_tick() - start_tick) <= BUTTON_HOLD_TIME))
      {
        button_current_state = BUTTON_STATE_ERROR_HANDLER;
      }
      else if ((drv_button_get_tick() - start_tick) > BUTTON_HOLD_TIME)
      {
        button_current_state = BUTTON_STATE_HOLD;
      }
      break;
    }

    case BUTTON_STATE_HOLD:
    {
      button_evt = BUTTON_EVT_HOLD;
      button_state = drv_button_read_pin(gpio_button);
      if (button_state == 0)
      {
        button_current_state = BUTTON_STATE_DETECT_RELEASE;
        start_tick = drv_button_get_tick();
      }
      break;
    }

    case BUTTON_STATE_DETECT_RELEASE:
    {
      button_state = drv_button_read_pin(gpio_button);
      if ((button_state == 1) && ((drv_button_get_tick() - start_tick) <= BUTTON_RELEASE_TIME))
      {
        button_current_state = BUTTON_STATE_HOLD;
      } 
      else if ((drv_button_get_tick() - start_tick) > BUTTON_RELEASE_TIME)
      {
        button_current_state = BUTTON_STATE_RELEASE;
      }
      break;
    }

    case BUTTON_STATE_RELEASE:
    {
      button_evt = BUTTON_EVT_RELEASE;
      button_current_state = BUTTON_STATE_IDLE;
      break;
    }

    case BUTTON_STATE_ERROR_HANDLER:
    {
      button_evt = BUTTON_EVT_ERROR;
      button_current_state = BUTTON_STATE_IDLE;
      break;
    }

    default:
      break;
    }

  return button_evt;
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
