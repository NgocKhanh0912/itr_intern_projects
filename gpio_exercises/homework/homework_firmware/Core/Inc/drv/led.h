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
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Public defines ----------------------------------------------------- */
#define NUM_OF_LEDS 3
#define LED_PORT GPIOB

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  LED_INIT_STATUS_OK = 0,
  LED_INIT_STATUS_ERROR = 1,
  LED_SET_STATUS_OK = 2,
  LED_SET_STATUS_ERROR = 3,
  LED_CLEAR_STATUS_OK = 4,
  LED_CLEAR_STATUS_ERROR = 5
} led_init_status_t;

typedef enum
{
  LED1_PB3_RED = 0,
  LED2_PB5_GREEN = 1,
  LED3_PB7_BLUE = 2,
} led_num_t;

typedef enum
{
  LED_OFF = 0,
  LED_ON = 1,
} led_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief     Initialize for driver
 *
 * @param[in]   None
 *
 * @attention   Should call this function first before using other function
 *
 * @return    OK    success
 * @return    ERROR failed
 */
uint16_t led_init();

/**
 * @brief     Choose which LED is ON/OFF
 *
 * @param[in]   led_num: choose which LED you want to control ON/OFF
 *              led_set_status: choose LED ON or OFF
 *
 * @attention   data type of led_num is led_num_t, data type of led_set_status is led_set_status_t
 *
 * @return    LED_SET_STATUS_OK if success
 * @return	LED_SET_STATUS_ERROR if failed
 */
uint16_t led_set(led_num_t led_num);

/**
 * @brief     Clear the chosen LED
 *
 * @param[in]   led_num: The LED number
 *
 * @attention   None
 *
 * @return    LED_CLEAR_STATUS_OK if success
 * @return	LED_CLEAR_STATUS_ERROR if failed
 */
uint16_t led_clear(led_num_t led_num);

#endif /* INC_DRV_LED_H_ */
