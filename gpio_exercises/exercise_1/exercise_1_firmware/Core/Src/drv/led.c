/**
 * @file       led.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       05/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Driver for LED
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv/led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
led_status_t led_init(drv_led_t *led, GPIO_TypeDef *gpio_x, uint16_t gpio_pin)
{
	// Check the parameters
	ASSERT((led != NULL), LED_INIT_STATUS_ERROR);
	ASSERT((gpio_x != NULL), LED_INIT_STATUS_ERROR);
	ASSERT((gpio_pin >= GPIO_PIN_0) && (gpio_pin <= GPIO_PIN_15), LED_INIT_STATUS_ERROR);
	// Initialize
	led->gpio_x = gpio_x;
	led->gpio_pin = gpio_pin;
	// Reset output value
	HAL_GPIO_WritePin(gpio_x, gpio_pin, GPIO_RESET);
	return LED_INIT_STATUS_OK;
}

led_status_t led_set(drv_led_t *led)
{
	// Check the parameters
	ASSERT(led != NULL, LED_SET_STATUS_ERROR);
	// Set output
	HAL_GPIO_WritePin(led->gpio_x, led->gpio_pin, GPIO_SET);
	return LED_SET_STATUS_OK;
}

led_status_t led_reset(drv_led_t *led)
{
	// Check the parameters
	ASSERT(led != NULL, LED_RESET_STATUS_ERROR);
	// Reset output
	HAL_GPIO_WritePin(led->gpio_x, led->gpio_pin, GPIO_RESET);
	return LED_RESET_STATUS_OK;
}

/* End of file -------------------------------------------------------- */
