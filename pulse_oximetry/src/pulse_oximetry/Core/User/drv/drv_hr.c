/**
 * @file       drv_hr.c
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
 * @note
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv_hr.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/**
 * @brief  Start the peripherals that use for sensor
 *
 * @param[in]     hr_sen  pointer to a drv_hr_t structure that store the information of Heart Rate sensor
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
static uint32_t drv_hr_peri_init(drv_hr_t *hr_sen);
/* Function definitions ----------------------------------------------- */
uint32_t drv_hr_init(drv_hr_t *hr_sen,
                     bsp_adc_typedef_t *sen_adc,
                     bsp_tim_typedef_t *tim,
                     uint32_t prescaler,
                     uint32_t autoreload)
{
  __ASSERT(hr_sen != NULL, DRV_HR_ERROR);
  __ASSERT(sen_adc != NULL, DRV_HR_ERROR);
  __ASSERT(tim != NULL, DRV_HR_ERROR);
  __ASSERT(prescaler != 0, DRV_HR_ERROR);
  __ASSERT(autoreload > 0, DRV_HR_ERROR);

  hr_sen->adc = sen_adc;
  hr_sen->sampling_rate.timer = tim;
  hr_sen->sampling_rate.prescaler = prescaler;
  hr_sen->sampling_rate.autoreload = autoreload;

  uint32_t ret = DRV_HR_OK;
  ret = drv_hr_peri_init(hr_sen);
  __ASSERT(ret == DRV_HR_OK, DRV_HR_FAIL);

  ret = bsp_adc_register_handler(&(hr_sen->adc_conv));
  __ASSERT(ret == BSP_ADC_OK, DRV_HR_FAIL);

  hr_sen->active = true;

  return DRV_HR_OK;
}

uint32_t drv_hr_sleep(drv_hr_t *hr_sen)
{
  __ASSERT(hr_sen != NULL, DRV_HR_ERROR);

  uint32_t ret = BSP_TIMER_OK;
  ret = bsp_timer_stop_it(hr_sen->sampling_rate.timer);
  __ASSERT(ret == BSP_TIMER_OK, DRV_HR_FAIL);
  ret = bsp_adc_stop_it(hr_sen->adc);
  __ASSERT(ret == BSP_ADC_OK, DRV_HR_FAIL);

  hr_sen->active = false;

  return DRV_HR_OK;
}

uint32_t drv_hr_wakeup(drv_hr_t *hr_sen)
{
  __ASSERT(hr_sen != NULL, DRV_HR_ERROR);

  uint32_t ret = BSP_ADC_OK;
  ret = bsp_adc_start_it(hr_sen->adc);
  __ASSERT(ret == BSP_ADC_OK, DRV_HR_FAIL);
  ret = bsp_timer_start_it(hr_sen->sampling_rate.timer);
  __ASSERT(ret == BSP_TIMER_OK, DRV_HR_FAIL);

  hr_sen->active = true;

  return DRV_HR_OK;
}

/* Private definitions ------------------------------------------------ */
static uint32_t drv_hr_peri_init(drv_hr_t *hr_sen)
{
  __ASSERT(hr_sen != NULL, DRV_HR_ERROR);

  uint32_t ret = BSP_TIMER_OK;
  ret = bsp_timer_set_prescaler(hr_sen->sampling_rate.timer, hr_sen->sampling_rate.prescaler);
  __ASSERT(ret == BSP_TIMER_OK, DRV_HR_FAIL);

  ret = bsp_timer_set_autoreload(hr_sen->sampling_rate.timer, hr_sen->sampling_rate.autoreload);
  __ASSERT(ret == BSP_TIMER_OK, DRV_HR_FAIL);

  ret = bsp_timer_start_it(hr_sen->sampling_rate.timer);
  __ASSERT(ret == BSP_ADC_OK, DRV_HR_FAIL);

  ret = bsp_adc_start_it(hr_sen->adc);
  __ASSERT(ret == BSP_ADC_OK, DRV_HR_FAIL);

  return DRV_HR_OK;
}

/* End of file -------------------------------------------------------- */
