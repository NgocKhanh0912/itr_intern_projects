/**
 * @file       drv_led.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Driver for interfacing with the LEDs
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv/drv_led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
enum drv_led_set_level
{
  LED_ACTIVE_LEVEL_LOW_ON = 0,
  LED_ACTIVE_LEVEL_LOW_OFF = 1,
  LED_ACTIVE_LEVEL_HIGH_ON = 1,
  LED_ACTIVE_LEVEL_HIGH_OFF = 0,
};

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_led_status_t drv_led_init(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level)
{
  bsp_gpio_init(gpio_led);

  if (led_active_level == LED_ACTIVE_LEVEL_HIGH)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_HIGH_OFF);
    }
  else if (led_active_level == LED_ACTIVE_LEVEL_LOW)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_LOW_OFF);
    }
  return LED_INIT_STATUS_OK;
}

drv_led_status_t drv_led_set_on(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level)
{
  if (led_active_level == LED_ACTIVE_LEVEL_HIGH)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_HIGH_ON);
    }
  else if (led_active_level == LED_ACTIVE_LEVEL_LOW)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_LOW_ON);
    }
  return LED_SET_STATUS_OK;
}

drv_led_status_t drv_led_set_off(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level)
{
  if (led_active_level == LED_ACTIVE_LEVEL_HIGH)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_HIGH_OFF);
    }
  else if (led_active_level == LED_ACTIVE_LEVEL_LOW)
    {
      bsp_gpio_write_pin(gpio_led, LED_ACTIVE_LEVEL_LOW_OFF);
    }
  return LED_CLEAR_STATUS_OK;
}

drv_led_status_t drv_led_toggle(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level)
{
  bsp_gpio_toggle_pin(gpio_led);
  return LED_TOGGLE_STATUS_OK;
}
/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
