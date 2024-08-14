/**
 * @file       drv_buzzer.C
 * @copyright
 * @license
 * @version    1.0.0
 * @date       31/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Driver for interfacing with the buzzer
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv_buzzer.h"
#include "bsp_utils.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define TIM_CLOCK_SRC (96000000)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

static uint16_t drv_buzzer_calculate_prescaler(uint32_t frequency);
/* Function definitions ----------------------------------------------- */
uint32_t drv_buzzer_init(drv_buzzer_t *buzzer,
                         bsp_tim_typedef_t *tim,
                         uint32_t pwm_channel)
{
  __ASSERT(buzzer != NULL, DRV_BUZZER_ERROR);
  __ASSERT(tim != NULL, DRV_BUZZER_ERROR);

  sound_effect_t initialization_effect[] =
      {{NOTE_FS5, 50},
       {NOTE_CS6, 100},
       {NOTE_GS7, 200},
       {NOTE_C5, 500}};

  buzzer->config.htim = tim;
  buzzer->config.pwm_channel = pwm_channel;
  buzzer->config.prescaler = 0;
  buzzer->config.duty_cycle = 500;
  buzzer->config.period = 1000;
  buzzer->sound_effect = initialization_effect;
  buzzer->note_nums = 4;
  bsp_timer_set_prescaler(buzzer->config.htim, buzzer->config.prescaler);
  bsp_timer_set_autoreload(buzzer->config.htim, buzzer->config.period);
  bsp_timer_set_output_compare(buzzer->config.htim,
                               buzzer->config.pwm_channel,
                               buzzer->config.duty_cycle);
  bsp_pwm_start(buzzer->config.htim, buzzer->config.pwm_channel);
  buzzer->active = true;

  uint8_t i = 0;
  uint32_t current_tick = bsp_utils_get_tick();
  do
  {
    if (bsp_utils_get_tick() - current_tick > (buzzer->sound_effect[i].duration))
    {
      uint16_t prescaler = drv_buzzer_calculate_prescaler(buzzer->sound_effect[i].note);
      bsp_timer_set_prescaler(buzzer->config.htim, prescaler);
      current_tick = bsp_utils_get_tick();
      i++;
    }
  } while (i < buzzer->note_nums);

  buzzer->config.prescaler = 0;
  bsp_timer_set_prescaler(buzzer->config.htim, buzzer->config.prescaler);

  return DRV_BUZZER_OK;
}

uint32_t drv_buzzer_play(drv_buzzer_t *buzzer, sound_effect_t *sound_effect_buf, uint32_t length)
{
  __ASSERT(buzzer != NULL, DRV_BUZZER_ERROR);
  __ASSERT(sound_effect_buf != NULL, DRV_BUZZER_ERROR);
  __ASSERT(length > 0, DRV_BUZZER_ERROR);
  __ASSERT(buzzer->active == true, DRV_BUZZER_ERROR);

  buzzer->sound_effect = sound_effect_buf;
  buzzer->note_nums = length;

  uint8_t i = 0;
  uint32_t current_tick = bsp_utils_get_tick();
  do
  {
    if (bsp_utils_get_tick() - current_tick > (buzzer->sound_effect[i].duration))
    {
      uint16_t prescaler = drv_buzzer_calculate_prescaler(buzzer->sound_effect[i].note);
      bsp_timer_set_prescaler(buzzer->config.htim, prescaler);
      current_tick = bsp_utils_get_tick();
      i++;
    }
  } while (i < buzzer->note_nums);

  buzzer->config.prescaler = 0;
  bsp_timer_set_prescaler(buzzer->config.htim, buzzer->config.prescaler);
}
/* Private definitions ----------------------------------------------- */
static uint16_t drv_buzzer_calculate_prescaler(uint32_t frequency)
{
  if (frequency == 0)
    return 0;
  return (TIM_CLOCK_SRC / (1000 * (frequency)) - 1);
}
/* End of file -------------------------------------------------------- */
