/**
 * @file       sys_led.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-11
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Definitions of sys_led APIs
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_led.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define NUM_OF_LEDS (3)
#define LED_PRESCALER (1599UL)
#define LED_BLINK_PERIOD (4999UL)
#define LED_ON_TIME (2499UL)
/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_LED_RED = 0,
  SYS_LED_BLUE,
  SYS_LED_GREEN
} sys_led_type_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_led_t s_led;
/* Private function prototypes ---------------------------------------- */
static void sys_led_pulse_finished_callback(TIM_HandleTypeDef *htim);
/* Function definitions ----------------------------------------------- */
sys_led_status_t sys_led_init(TIM_HandleTypeDef *htim)
{
  drv_led_t sled_config[3];
  __ASSERT(htim != NULL, SYS_LED_ERROR);
  drv_led_status_t ret = DRV_LED_OK;
  for (uint8_t i = 0; i < NUM_OF_LEDS; i++)
  {
    ret = drv_led_init(&sled_config[i],
                       htim,
                       LED_PRESCALER,
                       TIM_CHANNEL_2 + (4 * i),
                       LED_BLINK_PERIOD,
                       LED_ON_TIME);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    s_led.dled[i] = sled_config[i];
    drv_led_disable(&sled_config[i]);
  }
  s_led.fsm_state = SYS_LED_STATE_LED_IDLE;
  s_led.transit_active = false;

  drv_led_register_callback(sys_led_pulse_finished_callback, NULL);

  return SYS_LED_OK;
}

sys_led_status_t sys_led_change_effect(bool change_effect_permission)
{
  s_led.transit_active = change_effect_permission;

  return SYS_LED_OK;
}

bool sys_led_ready_to_change_effect()
{
  return s_led.transit_active;
}

sys_led_status_t sys_led_manage(sys_led_state_blink_t sled_state_blink)
{
  s_led.fsm_state = sled_state_blink;
  switch (sled_state_blink)
  {
  case SYS_LED_STATE_LED_IDLE:
  {
    drv_led_status_t ret = DRV_LED_OK;

    for (uint8_t i = 0; i < NUM_OF_LEDS; i++)
    {
      ret = drv_led_disable(&s_led.dled[i]);
      __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    }

    break;
  }
  case SYS_LED_STATE_LED_RED_BLINK:
  {
    drv_led_status_t ret = DRV_LED_OK;

    ret = drv_led_enable(&s_led.dled[SYS_LED_RED]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_GREEN]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_BLUE]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);

    break;
  }
  case SYS_LED_STATE_LED_GREEN_BLINK:
  {
    drv_led_status_t ret = DRV_LED_OK;

    ret = drv_led_enable(&s_led.dled[SYS_LED_GREEN]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_RED]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_BLUE]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);

    break;
  }
  case SYS_LED_STATE_LED_BLUE_BLINK:
  {
    drv_led_status_t ret = DRV_LED_OK;

    ret = drv_led_enable(&s_led.dled[SYS_LED_BLUE]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_GREEN]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);
    ret = drv_led_disable(&s_led.dled[SYS_LED_RED]);
    __ASSERT(ret == DRV_LED_OK, SYS_LED_FAIL);

    break;
  }

  default:
    break;
  }
  return SYS_LED_OK;
}
/* Private definitions ----------------------------------------------- */
static void sys_led_pulse_finished_callback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == s_led.dled[0].htim->Instance)
    s_led.transit_active = true;
}

/* End of file -------------------------------------------------------- */
