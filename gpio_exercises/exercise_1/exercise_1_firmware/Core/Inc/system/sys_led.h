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
#define NUMBER_OF_LEDS 3
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
} led_state_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief	Initialize System Led
 *
 * @param	None
 *
 * @attention	None
 *
 * @return	None
 */
void sys_led_init();

/**
 * @brief	Handle System Manager State
 *
 * @param	current_state: State from System Manager
 *
 * @attention	None
 *
 * @return	None
 */
void sys_led_handler(led_state_t current_state);

#endif /* INC_SYSTEM_SYS_LED_H_ */
