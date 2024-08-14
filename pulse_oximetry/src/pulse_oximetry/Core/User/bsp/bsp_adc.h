/**
 * @file       bsp_adc.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_BSP_ADC_H
#define __USER_BSP_ADC_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "cbuffer.h"
/* Public defines ----------------------------------------------------- */
typedef ADC_HandleTypeDef bsp_adc_typedef_t;
typedef HAL_StatusTypeDef hal_status_t;
/* Public enumerate/structure ----------------------------------------- */
enum bsp_adc_status_t
{
  BSP_ADC_ERROR = 0xFFFFFFFF,
  BSP_ADC_FAILED = 0x7FFFFFFF,
  BSP_ADC_OK = 0x3FFFFFFF
};
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Enable and Start ADC conversion
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_start(bsp_adc_typedef_t *badc);

/**
 * @brief         Enables the interrupt and starts ADC conversion of regular channels.
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_start_it(bsp_adc_typedef_t *badc);

/**
 * @brief         Enables ADC DMA request after last transfer (Single-ADC mode) and enables ADC peripheral.
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_start_dma(bsp_adc_typedef_t *badc, uint32_t *dma_buf, uint32_t length);

/**
 * @brief  Disables ADC and stop conversion of regular channels.
 *
 * @note   Caution: This function will stop also injected channels.
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_stop(bsp_adc_typedef_t *badc);

/**
 * @brief  Disables the interrupt and stop ADC conversion of regular channels.
 *
 * @note   Caution: This function will stop also injected channels.
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_stop_it(bsp_adc_typedef_t *badc);

/**
 * @brief  Disables ADC DMA (Single-ADC mode) and disables ADC peripheral
 *
 * @note   Caution: This function will stop also injected channels.
 *
 * @param[in]     badc pointer to a bsp_adc_typedef_t structure that contains
 *                the configuration information for the specified ADC.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_stop_dma(bsp_adc_typedef_t *badc);

/**
 * @brief  Gets the converted value from data register of regular channel.
 *
 * @note   Caution: This function will stop also injected channels.
 *
 * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
 *         the configuration information for the specified ADC.
 *
 * @return
 *  - Converted value.
 */
uint32_t bsp_adc_get_value(bsp_adc_typedef_t *badc);

/**
 * @brief  Register the upper-layer function to handle the callback event.
 *
 * @param  bsp_adc_cb pointer to a function handle this callback.
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t bsp_adc_register_handler(cbuffer_t *adc_conv_cbuf);

/**
 * @brief  Regular conversion complete callback in non blocking mode.
 *
 * @note   Caution: This function will stop also injected channels.
 *
 * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
 *         the configuration information for the specified ADC.
 *
 * @return
 *  - None.
 */
void bsp_adc_conv_cplt_callback(bsp_adc_typedef_t *badc);

#endif // __USER_BSP_ADC_H

/* End of file -------------------------------------------------------- */
