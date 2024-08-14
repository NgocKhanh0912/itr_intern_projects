/**
 * @file       drv_led.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-11
 * @author     Giang Phan Truong
 * @author     Viet Hoang Xuan
 *             Khanh Nguyen Ngoc
 *
 * @brief      Definitions of drv_led APIs
 *
 * @note       None
 * @example    None
 *
 */

/* Includes ----------------------------------------------------------- */
#include "drv_led.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_led_callback drv_led_callback_pulse_finished = NULL;
static drv_led_callback drv_led_callback_period_elapsed = NULL;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_led_status_t drv_led_init(drv_led_t *dled,
                              TIM_HandleTypeDef *dled_htim,
                              uint32_t dled_htim_prescaler,
                              uint32_t dled_pwm_channel,
                              uint16_t dled_period,
                              uint16_t dled_duty_cycle)
{
  __ASSERT(dled != NULL, DRV_LED_ERROR);
  __ASSERT(dled_htim != NULL, DRV_LED_ERROR);

  dled->htim = dled_htim;
  dled->pwm_channel = dled_pwm_channel;
  dled->prescaler = dled_htim_prescaler;
  dled->period = dled_period;
  dled->duty_cycle = dled_duty_cycle;

  bsp_timer_status_t ret = BSP_TIMER_OK;

  ret = bsp_timer_set_prescaler(dled_htim, dled_htim_prescaler);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  ret = bsp_timer_set_autoreload(dled_htim, dled_period);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  ret = bsp_timer_set_output_compare(dled_htim, dled_pwm_channel, dled_duty_cycle);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  return DRV_LED_OK;
}

drv_led_status_t drv_led_set_period(drv_led_t *dled, uint16_t dled_period)
{
  __ASSERT(dled != NULL, DRV_LED_ERROR);

  bsp_timer_status_t ret = BSP_TIMER_OK;

  ret = bsp_timer_set_autoreload(dled->htim, dled_period);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  return DRV_LED_OK;
}

drv_led_status_t drv_led_set_duty_cycle(drv_led_t *dled, uint16_t dled_on_time)
{
  __ASSERT(dled != NULL, DRV_LED_ERROR);

  bsp_timer_status_t ret = BSP_TIMER_OK;

  ret = bsp_timer_set_output_compare(dled->htim, dled->pwm_channel, dled_on_time);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  return DRV_LED_OK;
}

drv_led_status_t drv_led_enable(drv_led_t *dled)
{
  __ASSERT(dled != NULL, DRV_LED_ERROR);

  bsp_timer_status_t ret = BSP_TIMER_OK;

  ret = bsp_pwm_start_it(dled->htim, dled->pwm_channel);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  return DRV_LED_OK;
}

drv_led_status_t drv_led_disable(drv_led_t *dled)
{
  __ASSERT(dled != NULL, DRV_LED_ERROR);

  bsp_timer_status_t ret = BSP_TIMER_OK;

  ret = bsp_pwm_stop_it(dled->htim, dled->pwm_channel);
  __ASSERT(ret == BSP_TIMER_OK, DRV_LED_FAIL);

  return DRV_LED_OK;
}

drv_led_status_t drv_led_register_callback(drv_led_callback pulse_finished_callback,
                                           drv_led_callback period_elapsed_callback)
{
  drv_led_callback_pulse_finished = pulse_finished_callback;
  drv_led_callback_period_elapsed = period_elapsed_callback;

  return DRV_LED_OK;
}

drv_led_status_t drv_led_pulse_finished_handler(TIM_HandleTypeDef *htim)
{
  __ASSERT(htim != NULL, DRV_LED_ERROR);

  __CALLBACK(drv_led_callback_pulse_finished, htim);

  return DRV_LED_OK;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
