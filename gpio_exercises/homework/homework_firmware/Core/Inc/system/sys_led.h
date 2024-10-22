/**
 * @file       sys_led.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Control LEDs according to each states
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_LED_H_
#define INC_SYSTEM_SYS_LED_H_

/* Includes ----------------------------------------------------------- */
#include "drv/led.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  STATE_IDLE = 0, // All LEDs are OFF
  LED_1,	// LED_1 is ON
  LED_2,	// LED_2 is ON
  LED_3,	// LED_3 is ON
  LED_12,	// LED_1 and LED_2 are ON
  LED_23,	// LED_2 and LED_3 are ON
  LED_31,	// LED_3 and LED_1 are ON
  LED_123	// All LEDs are OFF
} state_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

void sys_led_start();

/**
 * @brief     Control LEDs for STATE_IDLE: LED1, LED2, LED3 are OFF
 *
 * @param[in]   None
 *
 * @attention   None
 *
 * @return    None
 */
void set_led_for_state_idle();

/**
 * @brief     Control LEDs for STATE_1 (1 LED is ON), including LED_1, LED_2, LED_3
 *
 * @param[in]   LED we want to set ON
 *
 * @attention   None
 *
 * @return    None
 */
void set_led_for_state_1(led_num_t led_num);

/**
 * @brief     Control LEDs for STATE_2 (2 LED are ON), including LED_12, LED_23, LED_31
 *
 * @param[in]   LEDs we want to set ON
 *
 * @attention   None
 *
 * @return    None
 */
void set_led_for_state_2(led_num_t led_num_1, led_num_t led_num_2);

/**
 * @brief     Control LEDs for STATE_3 (all LEDs are ON)
 *
 * @param[in]   None
 *
 * @attention   None
 *
 * @return    None
 */
void set_led_for_state_3();

#endif /* INC_SYSTEM_SYS_LED_H_ */
