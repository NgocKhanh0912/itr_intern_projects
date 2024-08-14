/**
 * @file       sys_led.c
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

/* Includes ----------------------------------------------------------- */
#include "system/sys_led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static drv_led_t led[NUMBER_OF_LEDS];

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void sys_led_init() {
	led_init(&led[0], GPIOD, GPIO_PIN_12);
	led_init(&led[1], GPIOD, GPIO_PIN_13);
	led_init(&led[2], GPIOD, GPIO_PIN_14);
}

void sys_led_handler(led_state_t current_state) {
	switch (current_state) {
	case STATE_IDLE:
		led_reset(&led[0]);
		led_reset(&led[1]);
		led_reset(&led[2]);
		break;
	case LED_1:
		led_reset(&led[1]);
		led_reset(&led[2]);
		led_set(&led[0]);
		break;
	case LED_2:
		led_reset(&led[0]);
		led_reset(&led[2]);
		led_set(&led[1]);
		break;
	case LED_3:
		led_reset(&led[0]);
		led_reset(&led[1]);
		led_set(&led[2]);
		break;
	case LED_12:
		led_reset(&led[2]);
		led_set(&led[0]);
		led_set(&led[1]);
		break;
	case LED_23:
		led_reset(&led[0]);
		led_set(&led[1]);
		led_set(&led[2]);
		break;
	case LED_31:
		led_reset(&led[1]);
		led_set(&led[2]);
		led_set(&led[0]);
		break;
	case LED_123:
		led_set(&led[0]);
		led_set(&led[1]);
		led_set(&led[2]);
		break;
	default:
		break;
	}
}

/* End of file -------------------------------------------------------- */
