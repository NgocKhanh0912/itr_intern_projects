/**
 * @file       sys_manage.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Manage the states and call the control LEDs function from sys_led
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_MANAGE_H_
#define INC_SYSTEM_SYS_MANAGE_H_

/* Includes ----------------------------------------------------------- */
#include "system/sys_led.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum {
	RELEASE, SINGLE_CLICK, DOUBLE_CLICK, HOLD
} input_event_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief	Initialize System Manager
 *
 * @param[in]	None
 *
 * @attention	None
 *
 * @return	None
 */
void sys_manage_init();

/**
 * @brief     Execute FSM
 *
 * @param[in]   input: input is entered by the user to change the state
 *
 * @attention   None
 *
 * @return    None
 */
void sys_manage(input_event_t input);

#endif /* INC_SYSTEM_SYS_MANAGE_H_ */
