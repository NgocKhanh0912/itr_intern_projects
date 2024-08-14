/**
 * @file       button.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs definition of bsp_timer.h
 */
/* Includes ----------------------------------------------------------- */
#include "bsp_timer.h"
#include "common.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_timer_cb_t b_period_elapsed = NULL;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_timer_status_t bsp_timer_set_prescaler(bsp_tim_typedef_t *htim, uint32_t prescaler)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((prescaler >= 0) && (prescaler < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_PRESCALER(htim, prescaler);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_set_autoreload(bsp_tim_typedef_t *htim, uint32_t autoreload)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((autoreload >= 0) && (autoreload < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_AUTORELOAD(htim, autoreload);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_set_output_compare(bsp_tim_typedef_t *htim, uint32_t tim_channel, uint32_t compare)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
               (tim_channel == TIM_CHANNEL_2) ||
               (tim_channel == TIM_CHANNEL_3) ||
               (tim_channel == TIM_CHANNEL_4),
           BSP_TIMER_ERROR);
  __ASSERT((compare >= 0) && (compare < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_COMPARE(htim, tim_channel, compare);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_start(bsp_tim_typedef_t *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_Base_Start(htim);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_start_it(bsp_tim_typedef_t *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_Base_Start_IT(htim);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_stop(bsp_tim_typedef_t *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_Base_Stop(htim);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_stop_it(bsp_tim_typedef_t *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_Base_Stop_IT(htim);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_start(bsp_tim_typedef_t *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
               (tim_channel == TIM_CHANNEL_2) ||
               (tim_channel == TIM_CHANNEL_3) ||
               (tim_channel == TIM_CHANNEL_4),
           BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_OC_Start(htim, tim_channel);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_start_it(bsp_tim_typedef_t *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
               (tim_channel == TIM_CHANNEL_2) ||
               (tim_channel == TIM_CHANNEL_3) ||
               (tim_channel == TIM_CHANNEL_4),
           BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_OC_Start_IT(htim, tim_channel);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_stop(bsp_tim_typedef_t *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
               (tim_channel == TIM_CHANNEL_2) ||
               (tim_channel == TIM_CHANNEL_3) ||
               (tim_channel == TIM_CHANNEL_4),
           BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_OC_Stop(htim, tim_channel);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_stop_it(bsp_tim_typedef_t *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
               (tim_channel == TIM_CHANNEL_2) ||
               (tim_channel == TIM_CHANNEL_3) ||
               (tim_channel == TIM_CHANNEL_4),
           BSP_TIMER_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_TIM_OC_Stop_IT(htim, tim_channel);

  __ASSERT(ret == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_register_callback(bsp_timer_cb_t period_elapsed)
{
  __ASSERT(period_elapsed != NULL, BSP_TIMER_ERROR);
  b_period_elapsed = period_elapsed;

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_period_callback_handler(bsp_tim_typedef_t *htim)
{
  __CALLBACK(b_period_elapsed, htim);

  return BSP_TIMER_OK;
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
