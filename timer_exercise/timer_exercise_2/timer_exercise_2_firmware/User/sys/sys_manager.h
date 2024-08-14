/**
 * @file       sys_manage.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_SYS_MANGER_H
#define __USER_SYS_SYS_MANGER_H

/* Includes ----------------------------------------------------------- */
#include "sys_led.h"
#include "sys_button.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_MANAGER_ERROR = -2,
  SYS_MANAGER_FAIL,
  SYS_MANAGER_OK
} sys_manager_status_t;

typedef enum
{
  SYS_MANAGER_STATE_IDLE = 0,
  SYS_MANAGER_STATE_RED_BLINK,
  SYS_MANAGER_STATE_GREEN_BLINK,
  SYS_MANAGER_STATE_BLUE_BLINK,
  SYS_MANAGER_STATE_RED_WAIT_OFF,
  SYS_MANAGER_STATE_GREEN_WAIT_OFF,
  SYS_MANAGER_STATE_BLUE_WAIT_OFF,
  SYS_MANAGER_STATE_RED_WAIT_TRANSIT,
  SYS_MANAGER_STATE_GREEN_WAIT_TRANSIT,
  SYS_MANAGER_STATE_BLUE_WAIT_TRANSIT,
} sys_manager_state_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Initialize the system
 *
 * @return      -2 if error,
 *              -1 if fail,
 *              0 if success.
 */
sys_manager_status_t sys_manager_init();

/**
 * @brief       Initialize the system
 *
 * @return      -2 if error,
 *              -1 if fail,
 *              0 if success.
 */
sys_manager_status_t sys_manager_loop();

#endif // __USER_SYS_SYS_MANGER_H

/* End of file -------------------------------------------------------- */
