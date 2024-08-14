/**
 * @file       drv_led.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRV_DRV_LED_H_
#define INC_DRV_DRV_LED_H_

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp_gpio.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  LED_INIT_STATUS_OK = 0,
  LED_INIT_STATUS_ERROR = 1,
  LED_SET_STATUS_OK = 2,
  LED_SET_STATUS_ERROR = 3,
  LED_CLEAR_STATUS_OK = 4,
  LED_CLEAR_STATUS_ERROR = 5,
  LED_TOGGLE_STATUS_OK = 6,
  LED_TOGGLE_STATUS_ERROR = 7,
} drv_led_status_t;

typedef enum
{
  LED_ACTIVE_LEVEL_LOW = 0,
  LED_ACTIVE_LEVEL_HIGH = 1,
} drv_led_active_level_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function initializes the LEDs
 *
 * @param[in]   *gpio_led:  bsp_gpio_t type of variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      drv_led_status_t
 */
drv_led_status_t drv_led_init(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level);

/**
 * @brief       This function set LED to ON
 *
 * @param[in]   *gpio_led:  bsp_gpio_t type of variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      drv_led_status_t
 */
drv_led_status_t drv_led_set_on(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level);

/**
 * @brief       This function set LED to OFF
 *
 * @param[in]   *gpio_led:  bsp_gpio_t type of variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      drv_led_status_t
 */
drv_led_status_t drv_led_set_off(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level);

/**
 * @brief       This function toggle LED
 *
 * @param[in]   *gpio_led:  bsp_gpio_t type of variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      drv_led_status_t
 */
drv_led_status_t drv_led_toggle(bsp_gpio_t *gpio_led, drv_led_active_level_t led_active_level);

#endif /* INC_DRV_DRV_LED_H_ */
