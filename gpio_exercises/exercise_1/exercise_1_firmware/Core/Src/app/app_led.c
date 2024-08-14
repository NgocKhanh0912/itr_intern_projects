/**
 * @file       app_led.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Pass input to system_manage to perform functions on LEDs
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "app/app_led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void app_led() {
	sys_manage(RELEASE);
	HAL_Delay(1000);
	sys_manage(SINGLE_CLICK);
	HAL_Delay(1000);
	sys_manage(SINGLE_CLICK);
	HAL_Delay(1000);
	sys_manage(SINGLE_CLICK);
	HAL_Delay(1000);
	sys_manage(DOUBLE_CLICK);
	HAL_Delay(1000);
	sys_manage(DOUBLE_CLICK);
	HAL_Delay(1000);
	sys_manage(DOUBLE_CLICK);
	HAL_Delay(1000);
	sys_manage(HOLD);
	HAL_Delay(1000);
}

/* End of file -------------------------------------------------------- */
