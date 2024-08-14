/**
 * @file       sys_manage.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       07/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs definition of sys_manage.h
 */
/* Includes ----------------------------------------------------------- */
#include "system/sys_manage.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
#ifdef DEBUG
#define __ASSERT(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)
#else
#define __ASSERT(_EXPR_, _RET_VAL_) ((void)0)
#endif

/* Public variables --------------------------------------------------- */
sys_button_evt_t button_evt = 0;

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
static sys_manage_status_t sys_manage_start();
static sys_manage_status_t sys_manage_button();

/**
 * @brief     Select LEDs ON/OFF
 *
 * @param[in]   input: input is entered by the user to change the state of LEDs
 *
 * @attention   None
 *
 * @return    None
 */
void sys_manage_fsm();
/* Function definitions ----------------------------------------------- */
void sys_manage_loop() {
	sys_manage_start();

	while (1) {
		sys_manage_button();
		sys_manage_fsm();
	}
}

/* Private function definitions --------------------------------------- */
void sys_manage_fsm() {
	static sys_fsm_state_t fsm_state = SYS_STATE_0;
	// State transition
	switch (fsm_state) {
	case (SYS_STATE_0):
		switch (button_evt) {
		case SYS_BUTTON_EVT_SINGLE_CLICK:
			fsm_state = SYS_STATE_1;
			break;
		default:
			fsm_state = SYS_STATE_0;
			break;
		}
		break;
	case (SYS_STATE_1):
		switch (button_evt) {
		case SYS_BUTTON_EVT_DOUBLE_CLICK:
			fsm_state = SYS_STATE_2;
			break;
		case SYS_BUTTON_EVT_HOLD:
			fsm_state = SYS_STATE_0;
			break;
		default:
			fsm_state = SYS_STATE_1;
			break;
		}
		break;
	case (SYS_STATE_2):
		switch (button_evt) {
		case SYS_BUTTON_EVT_DOUBLE_CLICK:
			fsm_state = SYS_STATE_3;
			break;
		case SYS_BUTTON_EVT_HOLD:
			fsm_state = SYS_STATE_0;
			break;
		default:
			fsm_state = SYS_STATE_2;
			break;
		}
		break;
	case (SYS_STATE_3):
		switch (button_evt) {
		case SYS_BUTTON_EVT_DOUBLE_CLICK:
			fsm_state = SYS_STATE_1;
			break;
		case SYS_BUTTON_EVT_HOLD:
			fsm_state = SYS_STATE_0;
			break;
		default:
			fsm_state = SYS_STATE_3;
			break;
		}
		break;
	default:
		break;
	}
	// Output based on current state
	switch (fsm_state) {
	case (SYS_STATE_0):
		set_led_for_state_idle();
		break;
	case (SYS_STATE_1):
		set_led_for_state_1(LED1_PB3_RED);
		break;
	case (SYS_STATE_2):
		set_led_for_state_1(LED2_PB5_GREEN);
		break;
	case (SYS_STATE_3):
		set_led_for_state_1(LED3_PB7_BLUE);
		break;
	}
}

static sys_manage_status_t sys_manage_start() {
	HAL_Delay(1000); // System voltage stabilization

	sys_manage_status_t error_handler = SYS_MANAGE_OK;

	error_handler = (sys_manage_status_t) sys_button_start();
	sys_led_start();
	__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);

	return SYS_MANAGE_OK;
}

static sys_manage_status_t sys_manage_button() {
	static sys_manage_status_t error_handler = SYS_MANAGE_OK;
	static sys_button_state_t button_current_state = SYS_BUTTON_STATE_IDLE;
	static uint32_t start_tick = 0;

	switch (button_current_state) {
	case SYS_BUTTON_STATE_IDLE: {
		button_evt = SYS_BUTTON_EVT_NONE;

		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if (button_state == 1) {
			button_current_state = SYS_BUTTON_STATE_DETECT_POSEDGE;
			start_tick = button_get_tick();
		}
		break;
	}
	case SYS_BUTTON_STATE_DETECT_POSEDGE: {
		GPIO_PinState button_state;
		if ((button_get_tick() - start_tick) >= BUTTON_DEBOUNCE_TIME) {
			error_handler = (sys_manage_status_t) button_get_state(
					&button_state);
			__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
			if (button_state == 0) {
				button_current_state = SYS_BUTTON_STATE_IDLE;
			} else {
				button_current_state = SYS_BUTTON_STATE_DETECT_SINGLE_CLICK;
				start_tick = button_get_tick();
			}
		}
		break;
	}
	case SYS_BUTTON_STATE_DETECT_SINGLE_CLICK: {
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if ((button_state == 0)
				&& ((button_get_tick() - start_tick) < BUTTON_CLICK_TIME)) {
			button_current_state = SYS_BUTTON_STATE_END_SINGLE_CLICK;
			start_tick = button_get_tick();
		} else if ((button_get_tick() - start_tick) >= BUTTON_CLICK_TIME) {
			button_current_state = SYS_BUTTON_STATE_DETECT_HOLD;
		}
		break;
	}
	case SYS_BUTTON_STATE_END_SINGLE_CLICK: {
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if ((button_state == 0)
				&& (button_get_tick() - start_tick) >= BUTTON_RELEASE_TIME) {
			button_current_state = SYS_BUTTON_STATE_SINGLE_CLICK;
		} else if ((button_state == 1)
				&& (button_get_tick() - start_tick) < BUTTON_RELEASE_TIME) {
			button_current_state = SYS_BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK;
			start_tick = button_get_tick();
		}
		break;
	}
	case SYS_BUTTON_STATE_SINGLE_CLICK: {
		button_evt = sys_button_single_click();
		button_current_state = SYS_BUTTON_STATE_IDLE;
		break;
	}
	case SYS_BUTTON_STATE_DETECT_PRE_DOUBLE_CLICK: {
		if ((button_get_tick() - start_tick) >= BUTTON_DEBOUNCE_TIME) {
			GPIO_PinState button_state;
			error_handler = (sys_manage_status_t) button_get_state(
					&button_state);
			__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
			if (button_state == 0) {
				button_current_state = SYS_BUTTON_STATE_SINGLE_CLICK;
			} else if (button_state == 1) {
				button_current_state = SYS_BUTTON_STATE_DETECT_DOUBLE_CLICK;
				start_tick = button_get_tick();
			}
		}
		break;
	}
	case SYS_BUTTON_STATE_DETECT_DOUBLE_CLICK: {
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if ((button_state == 0)
				&& ((button_get_tick() - start_tick) < BUTTON_CLICK_TIME)) {
			button_current_state = SYS_BUTTON_STATE_DOUBLE_CLICK;
		} else if ((button_state == 1)
				&& ((button_get_tick() - start_tick) >= BUTTON_CLICK_TIME)) {
			button_current_state = SYS_BUTTON_STATE_ERROR_HANDLER;
		}
		break;
	}
	case SYS_BUTTON_STATE_DOUBLE_CLICK: {
		button_evt = sys_button_double_click();
		button_current_state = SYS_BUTTON_STATE_IDLE;
		break;
	}
	case SYS_BUTTON_STATE_DETECT_HOLD: {
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if ((button_state == 0)
				&& ((button_get_tick() - start_tick) <= BUTTON_HOLD_TIME)) {
			button_current_state = SYS_BUTTON_STATE_ERROR_HANDLER;
		} else if ((button_get_tick() - start_tick) > BUTTON_HOLD_TIME) {
			button_current_state = SYS_BUTTON_STATE_HOLD;
		}
		break;
	}
	case SYS_BUTTON_STATE_HOLD: {
		button_evt = sys_button_hold();
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if (button_state == 0) {
			button_current_state = SYS_BUTTON_STATE_DETECT_RELEASE;
			start_tick = button_get_tick();
		}
		break;
	}
	case SYS_BUTTON_STATE_DETECT_RELEASE: {
		GPIO_PinState button_state;
		error_handler = (sys_manage_status_t) button_get_state(&button_state);
		__ASSERT((error_handler == SYS_MANAGE_OK), SYS_MANAGE_FAIL);
		if ((button_state == 1)
				&& ((button_get_tick() - start_tick) <= BUTTON_RELEASE_TIME)) {
			button_current_state = SYS_BUTTON_STATE_HOLD;
		} else if ((button_get_tick() - start_tick) > BUTTON_RELEASE_TIME) {
			button_current_state = SYS_BUTTON_STATE_RELEASE;
		}
		break;
	}
	case SYS_BUTTON_STATE_RELEASE: {
		button_evt = sys_button_release();
		button_current_state = SYS_BUTTON_STATE_IDLE;
		break;
	}
	case SYS_BUTTON_STATE_ERROR_HANDLER: {
		button_evt = SYS_BUTTON_EVT_ERROR;
		button_current_state = SYS_BUTTON_STATE_IDLE;
		break;
	}
	default:
		break;
	}

	return SYS_MANAGE_OK;
}
/* End of file -------------------------------------------------------- */