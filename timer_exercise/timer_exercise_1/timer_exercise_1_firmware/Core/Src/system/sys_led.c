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

/* Includes ----------------------------------------------------------- */
#include "system/sys_led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
sys_led_status_t sys_led_init(bsp_gpio_t *LED, drv_led_active_level_t led_active_level)
{
  drv_led_init(LED, led_active_level);
  drv_led_init(LED + 1, led_active_level);
  drv_led_init(LED + 2, led_active_level);
  return SYS_LED_INIT_OK;
}

sys_led_status_t sys_led_effect_for_sys_state_0(bsp_gpio_t *LED, drv_led_active_level_t led_active_level)
{
  drv_led_set_off(LED, led_active_level);
  drv_led_set_off(LED + 1, led_active_level);
  drv_led_set_off(LED + 2, led_active_level);
  return SYS_LED_EFFECT_FOR_SYS_STATE_0_OK;
}

sys_led_status_t sys_led_effect_for_sys_state_1(bsp_gpio_t *LED, drv_led_active_level_t led_active_level)
{
  drv_led_toggle(LED, led_active_level);
  drv_led_set_off(LED + 1, led_active_level);
  drv_led_set_off(LED + 2, led_active_level);
  return SYS_LED_EFFECT_FOR_SYS_STATE_1_OK;
}

sys_led_status_t sys_led_effect_for_sys_state_2(bsp_gpio_t *LED, drv_led_active_level_t led_active_level)
{
  drv_led_toggle(LED + 1, led_active_level);
  drv_led_set_off(LED, led_active_level);
  drv_led_set_off(LED + 2, led_active_level);
  return SYS_LED_EFFECT_FOR_SYS_STATE_2_OK;
}

sys_led_status_t sys_led_effect_for_sys_state_3(bsp_gpio_t *LED, drv_led_active_level_t led_active_level)
{
  drv_led_toggle(LED + 2, led_active_level);
  drv_led_set_off(LED + 1, led_active_level);
  drv_led_set_off(LED, led_active_level);
  return SYS_LED_EFFECT_FOR_SYS_STATE_3_OK;
}
/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
