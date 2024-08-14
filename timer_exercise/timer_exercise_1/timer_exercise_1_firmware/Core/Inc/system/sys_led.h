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
 * @brief      System layer for interfacing with the LEDs
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_LED_H_
#define INC_SYSTEM_SYS_LED_H_

/* Includes ----------------------------------------------------------- */
#include "drv/drv_led.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_LED_INIT_OK = 0,
  SYS_LED_INIT_ERROR,
  SYS_LED_EFFECT_FOR_SYS_STATE_0_OK,
  SYS_LED_EFFECT_FOR_SYS_STATE_0_ERROR,
  SYS_LED_EFFECT_FOR_SYS_STATE_1_OK,
  SYS_LED_EFFECT_FOR_SYS_STATE_1_ERROR,
  SYS_LED_EFFECT_FOR_SYS_STATE_2_OK,
  SYS_LED_EFFECT_FOR_SYS_STATE_2_ERROR,
  SYS_LED_EFFECT_FOR_SYS_STATE_3_OK,
  SYS_LED_EFFECT_FOR_SYS_STATE_3_ERROR,
} sys_led_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function initializes the LEDs
 *
 * @param[in]   bsp_gpio_t *LED:  pointer of bsp_gpio_t type of variable array
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      sys_led_status_t
 */
sys_led_status_t sys_led_init(bsp_gpio_t *LED, drv_led_active_level_t led_active_level);

/**
 * @brief       Set 3 LEDs to OFF for SYS_STATE_0
 *
 * @param[in]   bsp_gpio_t *LED:  pointer of bsp_gpio_t type of variable array
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      sys_led_status_t
 */
sys_led_status_t sys_led_effect_for_sys_state_0(bsp_gpio_t *LED, drv_led_active_level_t led_active_level);

/**
 * @brief       Toggle LED1 based on timer, LED2 and 3 are OFF for SYS_STATE_1
 *
 * @param[in]   bsp_gpio_t *LED:  pointer of bsp_gpio_t type of variable array
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      sys_led_status_t
 */
sys_led_status_t sys_led_effect_for_sys_state_1(bsp_gpio_t *LED, drv_led_active_level_t led_active_level);

/**
 * @brief       Toggle LED2 based on timer, LED1 and 3 are OFF for SYS_STATE_2
 *
 * @param[in]   bsp_gpio_t *LED:  pointer of bsp_gpio_t type of variable array
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      sys_led_status_t
 */
sys_led_status_t sys_led_effect_for_sys_state_2(bsp_gpio_t *LED, drv_led_active_level_t led_active_level);

/**
 * @brief       Toggle LED3 based on timer, LED1 and 2 are OFF for SYS_STATE_3
 *
 * @param[in]   bsp_gpio_t *LED:  pointer of bsp_gpio_t type of variable array
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 *
 * @attention   None
 *
 * @return      sys_led_status_t
 */
sys_led_status_t sys_led_effect_for_sys_state_3(bsp_gpio_t *LED, drv_led_active_level_t led_active_level);


#endif /* INC_SYSTEM_SYS_LED_H_ */
