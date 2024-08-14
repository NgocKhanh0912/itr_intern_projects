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
 * @brief      APIs of LED Drivers
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef USER_DRV_DRV_TIMER_H_
#define USER_DRV_DRV_TIMER_H_

/* Includes ----------------------------------------------------------- */
#include "bsp_timer.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  DRV_LED_ERROR = -2,
  DRV_LED_FAIL,
  DRV_LED_OK
} drv_led_status_t;

typedef struct __attribute__((__packed__))
{
  TIM_HandleTypeDef *htim;
  uint32_t pwm_channel;
  uint32_t prescaler;
  uint16_t period;
  uint16_t duty_cycle;
} drv_led_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */
typedef void (*drv_led_callback)(TIM_HandleTypeDef *);
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Inititialize the LED.
 *
 * @param[in]   dled                Pointer to LED handler.
 * @param[in]   dled_htim           Pointer of timer LED handler.
 * @param[in]   dled_htim_prescaler Prescaler for timer clock source.
 * @param[in]   dled_pwm_channel    Channel PWM connect to LED.
 * @param[in]   dled_period         LED blink period.
 * @param[in]   dled_duty_cycle     LED on-time.
 *
 * @attention   the valid LED period and duty cycle.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to initialize LED,
 *              0 if initialize LED successfully.
 */
drv_led_status_t drv_led_init(drv_led_t *dled,
                              TIM_HandleTypeDef *dled_htim,
                              uint32_t dled_htim_prescaler,
                              uint32_t dled_pwm_channel,
                              uint16_t dled_period,
                              uint16_t dled_duty_cycle);

/**
 * @brief       Set the frequency for blinking LED.
 *
 * @param[in]   dled                Pointer to LED handler.
 * @param[in]   dled_frequency      Desired frequency of LED.
 *
 * @attention   the range of the frequency and valid frequency value,
 *              remember to determine the clock source.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to set frequency,
 *              0 if set frequency successfully.
 */
drv_led_status_t drv_led_set_period(drv_led_t *dled, uint16_t dled_period);

/**
 * @brief       Set the LED on-time.
 *
 * @param[in]   dled                Pointer to LED handler.
 * @param[in]   dled_frequency      Desired frequency of LED.
 *
 * @note        Duty cycle equal to dled_on_time divided by dled_period.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to set duty cycle,
 *              0 if set duty cycle successfully.
 */
drv_led_status_t drv_led_set_duty_cycle(drv_led_t *dled, uint16_t dled_on_time);

/**
 * @brief       Enable PWM channel connect to the LED.
 *
 * @param[in]   dled                Pointer to LED handler.
 *
 * @note        Should be configured before use this function.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to enable this LED,
 *              0 if enable this LED successfully.
 */
drv_led_status_t drv_led_enable(drv_led_t *dled);

/**
 * @brief       Disable PWM channel connect to the LED.
 *
 * @param[in]   dled                Pointer to LED handler.
 *
 * @note        Should be configuared before use this function.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to disable this LED,
 *              0 if disable this LED successfully.
 */
drv_led_status_t drv_led_disable(drv_led_t *dled);

/**
 * @brief       Register PWM period elapsed callback.
 *
 * @param[in]   pulse_finished_callback Function pointer point to pulse finished callback function.
 * @param[in]   period_elapsed_callback Function pointer point to period elapsed callback function.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to register this callback,
 *              0 if register this callback successfully.
 */
drv_led_status_t drv_led_register_callback(drv_led_callback pulse_finished_callback,
                                           drv_led_callback period_elapsed_callback);

/**
 * @brief       Function to PWM period elapsed callback.
 *
 * @param[in]   htim          Pointer of timer handler.
 *
 * @return      -2 if input parameters error,
 *              -1 if fail to register this callback,
 *              0 if register this callback successfully.
 */
drv_led_status_t drv_led_pulse_finished_handler(TIM_HandleTypeDef *htim);
#endif /* USER_DRV_DRV_TIMER_H_ */
