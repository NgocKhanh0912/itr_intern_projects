/**
 * @file       bsp_callback.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-11
 * @author     Giang Phan Truong
 *             Viet Hoang Xuan
 *             Khanh Nguyen Ngoc
 *
 * @brief      Re-define Callback of HAL
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_callback.h"
#include "bsp_timer.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  bsp_pwm_pulse_finished_handler(htim);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  bsp_gpio_exti_handler(GPIO_Pin);
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
