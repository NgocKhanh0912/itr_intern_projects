/**
 * @file       sys_manager.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       05/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      To trigger the event of button and print that event for user
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_MANAGER_H_
#define INC_SYSTEM_SYS_MANAGER_H_

/* Includes ----------------------------------------------------------- */
#include "sys_button.h"
#include "sys_led.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum {
	SYS_MANAGE_FAIL = 0U, SYS_MANAGE_OK = 1U, SYS_MANAGE_ERROR = 2U
} sys_manage_status_t;

typedef enum {
	SYS_STATE_0, // All LEDs are OFF
	SYS_STATE_1, // LED_1 ON
	SYS_STATE_2, // LED_2 ON
	SYS_STATE_3	// LED_3 ON
} sys_fsm_state_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief   System management loop function.
 *
 * @details This function is responsible for managing system tasks and operations in a loop.
 *          It typically handles tasks such as scheduling, monitoring, and responding to events
 *          or conditions within the system. It may involve coordinating various subsystems,
 *          managing resources, handling interrupts, and ensuring the overall stability and
 *          functionality of the system.
 *
 * @note    This function is expected to run continuously to maintain system functionality.
 *          It may interact with other modules or functions within the system to perform
 *          specific tasks and respond to system events.
 *
 * @return  None
 */
void sys_manage_loop();

#endif /* INC_SYSTEM_SYS_MANAGER_H_ */
