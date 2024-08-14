/**
 * @file       sys_led.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-11
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Manage LEDs of the system
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_SYS_LED_H
#define __USER_SYS_SYS_LED_H

/* Includes ----------------------------------------------------------- */
#include "drv_led.h"
#include <stdbool.h>

/* Public defines ----------------------------------------------------- */
typedef enum
{
  SYS_LED_ERROR = -2,
  SYS_LED_FAIL,
  SYS_LED_OK
} sys_led_status_t;

typedef enum
{
  SYS_LED_STATE_LED_IDLE = 0,
  SYS_LED_STATE_LED_RED_BLINK,
  SYS_LED_STATE_LED_GREEN_BLINK,
  SYS_LED_STATE_LED_BLUE_BLINK
} sys_led_state_blink_t;

typedef struct __attribute__((__packed__))
{
  drv_led_t dled[3];
  sys_led_state_blink_t fsm_state;
  bool transit_active;
} sys_led_t;
/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  State machine to manage LEDs blink
 *
 * @param[in]   htim          Pointer of timer handler.
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  -  (0): Success
 */
sys_led_status_t sys_led_init(TIM_HandleTypeDef *htim);

/**
 * @brief  v.
 *
 * @param[in]   change_effect_permission   Flag to control LEDs effect transition.
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  -  (0): Success
 */
sys_led_status_t sys_led_change_effect(bool change_effect_permission);

/**
 * @brief  Get the flag to control the LED effect transition
 *
 * @return
 *  - (true): ready
 *  - (false): busy
 */
bool sys_led_ready_to_change_effect();

/**
 * @brief  State machine to manage LEDs blink
 *
 * @param[in]   sled_state_blink    Input variable to determine LED on.
 *
 * @attention  Must be init first
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  -  (0): Success
 */
sys_led_status_t sys_led_manage(sys_led_state_blink_t sled_state_blink);

#endif // __USER_SYS_SYS_LED_H

/* End of file -------------------------------------------------------- */
