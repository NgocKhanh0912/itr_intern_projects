/**
 * @file       bso_callback.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-27
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      None
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "bsp_adc.h"
#include "bsp_timer.h"
#include "bsp_gpio.h"
#include "bsp_uart.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  bsp_adc_conv_cplt_callback(hadc);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  bsp_gpio_exti_handler(GPIO_Pin);
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  uint32_t ret = BSP_UART_OK;
  ret = bsp_uart_rx_cb_handler(huart, Size);

  if (ret != BSP_UART_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  bsp_timer_period_callback_handler(htim);
}
/* Private definitions ------------------------------------------------ */
/* End of file -------------------------------------------------------- */
