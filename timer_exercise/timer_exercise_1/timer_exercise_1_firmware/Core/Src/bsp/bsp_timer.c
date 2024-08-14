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
#include "bsp/bsp_timer.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
#ifdef DEBUG
#define __ASSERT(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)
#else
#define __ASSERT(_EXPR_, _RET_VAL_) ((void)0)
#endif

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_timer_status_t bsp_timer_set_prescaler(TIM_HandleTypeDef *htim, uint32_t prescaler)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((prescaler >= 0) && (prescaler < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_PRESCALER(htim, prescaler);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_set_autoreload(TIM_HandleTypeDef *htim, uint32_t autoreload)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((autoreload >= 0) && (autoreload < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_AUTORELOAD(htim, autoreload);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_set_output_compare(TIM_HandleTypeDef *htim, uint32_t tim_channel, uint32_t compare)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
          (tim_channel == TIM_CHANNEL_2) ||
          (tim_channel == TIM_CHANNEL_3) ||
          (tim_channel == TIM_CHANNEL_4), BSP_TIMER_ERROR);
  __ASSERT((compare >= 0) && (compare < 65536), BSP_TIMER_ERROR);

  __HAL_TIM_SET_COMPARE(htim, tim_channel, compare);

  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_start(TIM_HandleTypeDef *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_Base_Start(htim);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_start_it(TIM_HandleTypeDef *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_Base_Start_IT(htim);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_stop(TIM_HandleTypeDef *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_Base_Stop(htim);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_timer_stop_it(TIM_HandleTypeDef *htim)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_Base_Stop_IT(htim);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_start(TIM_HandleTypeDef *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
          (tim_channel == TIM_CHANNEL_2) ||
          (tim_channel == TIM_CHANNEL_3) ||
          (tim_channel == TIM_CHANNEL_4), BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_PWM_Start(htim, tim_channel);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_start_it(TIM_HandleTypeDef *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
          (tim_channel == TIM_CHANNEL_2) ||
          (tim_channel == TIM_CHANNEL_3) ||
          (tim_channel == TIM_CHANNEL_4), BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_PWM_Start_IT(htim, tim_channel);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_stop(TIM_HandleTypeDef *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
          (tim_channel == TIM_CHANNEL_2) ||
          (tim_channel == TIM_CHANNEL_3) ||
          (tim_channel == TIM_CHANNEL_4), BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_PWM_Stop(htim, tim_channel);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

bsp_timer_status_t bsp_pwm_stop_it(TIM_HandleTypeDef *htim, uint32_t tim_channel)
{
  __ASSERT(htim != NULL, BSP_TIMER_ERROR);
  __ASSERT((tim_channel == TIM_CHANNEL_1) ||
          (tim_channel == TIM_CHANNEL_2) ||
          (tim_channel == TIM_CHANNEL_3) ||
          (tim_channel == TIM_CHANNEL_4), BSP_TIMER_ERROR);

  HAL_StatusTypeDef btim_err = BSP_TIMER_OK;
  btim_err = HAL_TIM_PWM_Stop_IT(htim, tim_channel);

  __ASSERT(btim_err == HAL_OK, BSP_TIMER_FAIL);
  return BSP_TIMER_OK;
}

uint32_t bsp_get_systick()
{
  return HAL_GetTick();
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
