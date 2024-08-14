/**
 * @file       sys_button.h
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

/* Define to prevent recursive inclusion ------------------------------ */

#ifndef INC_SYSTEM_SYS_BUTTON_H_
#define INC_SYSTEM_SYS_BUTTON_H_

/* Includes ----------------------------------------------------------- */
#include "drv/drv_button.h"

/* Public defines ----------------------------------------------------- */
#define BUTTON_DEBOUNCE_TIME  (50UL)
#define BUTTON_RELEASE_TIME   (300UL)
#define BUTTON_HOLD_TIME      (3000UL)
#define BUTTON_CLICK_TIME     (500UL)

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BUTTON_EVT_NONE = 0U,
  BUTTON_EVT_SINGLE_CLICK,
  BUTTON_EVT_DOUBLE_CLICK,
  BUTTON_EVT_HOLD,
  BUTTON_EVT_RELEASE,
  BUTTON_EVT_ERROR
} sys_button_evt_t;

typedef enum
{
  BUTTON_STATE_IDLE = 0U,
  BUTTON_STATE_DETECT_POSEDGE,
  BUTTON_STATE_DETECT_SINGLE_CLICK,
  BUTTON_STATE_END_SINGLE_CLICK,
  BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK,
  BUTTON_STATE_DETECT_DOUBLE_CLICK,
  BUTTON_STATE_DOUBLE_CLICK,
  BUTTON_STATE_SINGLE_CLICK,
  BUTTON_STATE_DETECT_HOLD,
  BUTTON_STATE_HOLD,
  BUTTON_STATE_DETECT_RELEASE,
  BUTTON_STATE_RELEASE,
  BUTTON_STATE_ERROR_HANDLER,
} sys_button_state_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       this function manage the state and get the event of the button
 *
 * @param[in]   *gpio_button:  bsp_gpio_t type of variable that defined by user
 *
 * @return      drv_button_status_t
 */
sys_button_evt_t sys_button_fsm(bsp_gpio_t *gpio_button);

#endif /* INC_SYSTEM_SYS_BUTTON_H_ */
