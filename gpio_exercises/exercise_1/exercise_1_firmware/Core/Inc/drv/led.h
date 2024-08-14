/**
 * @file       led.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRV_LED_H_
#define INC_DRV_LED_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "common.h"

/* Public defines ----------------------------------------------------- */
#define HIGH_LEVEL_OUTPUT 1

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  LED_INIT_STATUS_OK = 0,
  LED_INIT_STATUS_ERROR = 1,
  LED_SET_STATUS_OK = 2,
  LED_SET_STATUS_ERROR = 3,
  LED_RESET_STATUS_OK = 4,
  LED_RESET_STATUS_ERROR = 5
} led_status_t;

#ifdef HIGH_LEVEL_OUTPUT
typedef enum
{
	GPIO_RESET = 0,
	GPIO_SET = 1
} gpio_output_enum;
#else
typedef enum
{
	GPIO_SET = 0,
	GPIO_RESET = 1
} gpio_output_enum;
#endif

typedef struct
{
	GPIO_TypeDef *gpio_x;
	uint16_t gpio_pin;
} drv_led_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief     Initialize LED
 *
 * @param[in]   None
 *
 * @attention   Should call this function first before using other function
 *
 * @return    OK    success
 * @return    ERROR failed
 */
led_status_t led_init(drv_led_t *led, GPIO_TypeDef *gpio_x, uint16_t gpio_pin);

/**
 * @brief     Choose which LED is ON/OFF
 *
 * @param[in]	led: LED which you want to turn ON or OFF
 *
 * @attention   None
 *
 * @return    LED_SET_STATUS_OK if success
 * @return	LED_SET_STATUS_ERROR if failed
 */
led_status_t led_set(drv_led_t *led);

/**
 * @brief     Reset the chosen LED
 *
 * @param[in]   led: The LED which you want to reset
 *
 * @attention   None
 *
 * @return    LED_CLEAR_STATUS_OK if success
 * @return	LED_CLEAR_STATUS_ERROR if failed
 */
led_status_t led_reset(drv_led_t *led);

#endif /* INC_DRV_LED_H_ */
