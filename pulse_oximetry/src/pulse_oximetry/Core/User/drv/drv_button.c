/**
 * @file       drv_button.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Driver for interfacing with the button
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv_button.h"
#include "common.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static drv_button_callback drv_button_exti_callback = NULL;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_button_status_t drv_button_init(drv_button_t *button,
                                    GPIO_TypeDef *button_port,
                                    uint16_t button_pin,
                                    uint32_t button_active_level)
{
  __ASSERT(button != NULL, DRV_BUTTON_ERROR);
  __ASSERT((button_port == GPIOA) ||
           (button_port == GPIOB) ||
           (button_port == GPIOC) ||
           (button_port == GPIOE),
           DRV_BUTTON_ERROR);
  __ASSERT((button_pin >= 0) && (button_pin < 16), DRV_BUTTON_ERROR);
  __ASSERT((button_active_level == 0) ||
           (button_active_level == 1),
           DRV_BUTTON_ERROR);

  button->port = button_port;
  button->pin = button_pin;
  button->active_level = button_active_level;
  button->time_debounce = 0;
  button->time_change = 0;
  button->current_state = !button_active_level;
  button->click_cnt = 0;

  return DRV_BUTTON_OK;
}

drv_button_status_t drv_button_exti_handler(uint16_t exti_line)
{
  __ASSERT((exti_line >= 0) && (exti_line < 16), DRV_BUTTON_ERROR);
  __CALLBACK(drv_button_exti_callback, exti_line);

  return DRV_BUTTON_OK;
}

drv_button_status_t drv_button_register_callback(drv_button_callback callback_function)
{
  drv_button_exti_callback = callback_function;

  return DRV_BUTTON_OK;
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
