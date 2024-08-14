/**
 * @file       sys_button.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       05/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      To manage the states of button
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_BUTTON_H_
#define INC_SYSTEM_SYS_BUTTON_H_

/* Includes ----------------------------------------------------------- */
#include "drv/button.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_BUTTON_STATUS_FAIL = 0U,
  SYS_BUTTON_STATUS_OK = 1U,
  SYS_BUTTON_STATUS_ERROR = 2U
} sys_button_status_t;

typedef enum
{
  SYS_BUTTON_EVT_NONE = 0U,
  SYS_BUTTON_EVT_SINGLE_CLICK,
  SYS_BUTTON_EVT_DOUBLE_CLICK,
  SYS_BUTTON_EVT_HOLD,
  SYS_BUTTON_EVT_RELEASE,
  SYS_BUTTON_EVT_ERROR
} sys_button_evt_t;

typedef enum
{
  SYS_BUTTON_STATE_IDLE = 0U,
  SYS_BUTTON_STATE_DETECT_POSEDGE,
  SYS_BUTTON_STATE_DETECT_SINGLE_CLICK,
  SYS_BUTTON_STATE_END_SINGLE_CLICK,
  SYS_BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK,
  SYS_BUTTON_STATE_DETECT_DOUBLE_CLICK,
  SYS_BUTTON_STATE_DOUBLE_CLICK,
  SYS_BUTTON_STATE_SINGLE_CLICK,
  SYS_BUTTON_STATE_DETECT_HOLD,
  SYS_BUTTON_STATE_HOLD,
  SYS_BUTTON_STATE_DETECT_RELEASE,
  SYS_BUTTON_STATE_RELEASE,
  SYS_BUTTON_STATE_ERROR_HANDLER,
} sys_button_state_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Start the system button module.
 *
 * @param[in]   None
 *
 * @attention   This function should be called first before using other functions in the system button module.
 *
 * @return      The status of the button start operation.
 */
sys_button_status_t sys_button_start();

/**
 * @brief       Get the event of the button
 *
 * @param[in]   None
 *
 * @return      The button single-click event
 */
sys_button_evt_t sys_button_single_click();

/**
 * @brief       Get the event of the button
 *
 * @param[in]   None
 *
 * @return      The button double-click event
 */
sys_button_evt_t sys_button_double_click();

/**
 * @brief       Get the event of the button
 *
 * @param[in]   None
 *
 * @return      The button hold event
 */
sys_button_evt_t sys_button_hold();

/**
 * @brief       Get the event of the button
 *
 * @param[in]   None
 *
 * @return      The button release event
 */
sys_button_evt_t sys_button_release();

#endif /* INC_SYSTEM_SYS_BUTTON_H_ */
