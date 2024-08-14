/**
 * @file       bsp_gpio.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      BSP for interfacing between HAL and top layers
 */

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp_gpio.h"

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
bsp_gpio_status_t bsp_gpio_init(bsp_gpio_t *gpio)
{
  __ASSERT((gpio->port != NULL), GPIO_STATUS_ERROR);
  __ASSERT((gpio->pin >= 0), GPIO_STATUS_ERROR);
  __ASSERT((gpio->pin <= 15), GPIO_STATUS_ERROR);
  __ASSERT((gpio->state == 0) ||
           (gpio->state == 1), GPIO_STATUS_ERROR);
  __ASSERT((gpio->mode == GPIO_MODE_INPUT) ||
           (gpio->mode == GPIO_MODE_OUTPUT_PP) ||
           (gpio->mode == GPIO_MODE_OUTPUT_OD), GPIO_STATUS_ERROR);

  return GPIO_STATUS_OK;
}

bsp_gpio_status_t bsp_gpio_write_pin(bsp_gpio_t *gpio, GPIO_PinState gpio_state)
{
  __ASSERT((gpio->state == 0) ||
           (gpio->state == 1), GPIO_STATUS_ERROR);
  __ASSERT((gpio->mode == GPIO_MODE_OUTPUT_PP) ||
           (gpio->mode == GPIO_MODE_OUTPUT_OD), GPIO_STATUS_ERROR);

  HAL_GPIO_WritePin(gpio->port, gpio->pin, gpio_state);
  return GPIO_STATUS_OK;
}

GPIO_PinState bsp_gpio_read_pin(bsp_gpio_t *gpio)
{
  __ASSERT((gpio->mode == GPIO_MODE_INPUT), GPIO_STATUS_ERROR);

  gpio->state = HAL_GPIO_ReadPin(gpio->port, gpio->pin);
  return gpio->state;
}

bsp_gpio_status_t bsp_gpio_toggle_pin(bsp_gpio_t *gpio)
{
  __ASSERT((gpio->mode == GPIO_MODE_OUTPUT_PP) ||
           (gpio->mode == GPIO_MODE_OUTPUT_OD), GPIO_STATUS_ERROR);

  HAL_GPIO_TogglePin(gpio->port, gpio->pin);
  return GPIO_STATUS_OK;
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
