/**
 * @file       sys_manage.c
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

/* Includes ----------------------------------------------------------- */
#include "system/sys_manage.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static led_state_t current_state = STATE_IDLE;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void sys_manage_init()
{
	sys_led_init();
}

void sys_manage(input_event_t event) {
	switch (current_state) {
	case (STATE_IDLE):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_1):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_2;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_2):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_3;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_3):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_12):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_23;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_23):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_31;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_31):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	case (LED_123):
		switch (event) {
		case RELEASE:
			current_state = STATE_IDLE;
			break;
		case SINGLE_CLICK:
			current_state = LED_1;
			break;
		case DOUBLE_CLICK:
			current_state = LED_12;
			break;
		case HOLD:
			current_state = LED_123;
			break;
		default:
			current_state = STATE_IDLE;
			break;
		}
		break;
	}
	// Output based on current state
	sys_led_handler(current_state);
}

/* End of file -------------------------------------------------------- */
