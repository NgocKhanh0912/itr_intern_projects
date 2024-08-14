/**
 * @file       sys_button.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_SYS_BUTTON_H
#define __USER_SYS_SYS_BUTTON_H

/* Includes ----------------------------------------------------------- */
#include "drv_button.h"
/* Public defines ----------------------------------------------------- */
#define BUTTON_DEBOUNCE_TIME (50UL)
#define BUTTON_RELEASE_TIME (300UL)
#define BUTTON_SINGLE_CLICK_TIME (500UL)
#define BUTTON_HOLD_TIME (3000UL)
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_BUTTON_ERROR = -2,
  SYS_BUTTON_FAIL,
  SYS_BUTTON_OK
} sys_button_status_t;

typedef enum
{
  SYS_BUTTON_STATE_STABLE = 0,
  SYS_BUTTON_STATE_DEBOUNCE,
} sys_button_state_t;

typedef enum
{
  SYS_BUTTON_FSM_STATE_IDLE = 0,
  SYS_BUTTON_FSM_STATE_PRESS,
  SYS_BUTTON_FSM_STATE_WAIT_SINGLE_CLICK,
  SYS_BUTTON_FSM_STATE_WAIT_HOLD,
  SYS_BUTTON_FSM_STATE_WAIT_DOUBLE_CLICK,
  SYS_BUTTON_FSM_STATE_WAIT_RELEASE,
  SYS_BUTTON_FSM_STATE_SINGLE_CLICK,
  SYS_BUTTON_FSM_STATE_DOUBLE_CLICK,
  SYS_BUTTON_FSM_STATE_HOLD,
  SYS_BUTTON_FSM_STATE_RELEASE
} sys_button_fsm_state_t;

typedef enum
{
  SYS_BUTTON_EVT_NONE = 0,
  SYS_BUTTON_EVT_SINGLE_CLICK,
  SYS_BUTTON_EVT_DOUBLE_CLICK,
  SYS_BUTTON_EVT_HOLD,
  SYS_BUTTON_EVT_RELEASE
} sys_button_evt_t;

typedef struct __attribute__((__packed__))
{
  drv_button_t dbutton;
  sys_button_state_t transient_state;
  sys_button_fsm_state_t fsm_state;
} sys_button_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Initialize the system button
 *
 * @param[in]   gpio  Pointer point to GPIO port
 * @param[in]   pin   pin of that port
 * @param[in]   button_active_level Determine the active high or active low button
 * @return      -2 if error,
 *              -1 if fail,
 *              0 if success.
 */
sys_button_status_t sys_button_init(GPIO_TypeDef *gpio, uint16_t pin, uint32_t button_active_level);

/**
 * @brief       Manage the system button
 *
 * @return      event of button
 */
sys_button_evt_t sys_button_manage();

#endif // __USER_SYS_SYS_BUTTON_H

/* End of file -------------------------------------------------------- */
