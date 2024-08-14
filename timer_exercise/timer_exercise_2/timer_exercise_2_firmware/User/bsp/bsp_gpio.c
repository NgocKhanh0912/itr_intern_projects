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
#include "bsp_gpio.h"
#include "drv_button.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_gpio_status_t bsp_gpio_write_pin(GPIO_TypeDef *gpio, uint16_t pin, GPIO_PinState state)
{
  __ASSERT((gpio == GPIOA) ||
               (gpio == GPIOB) ||
               (gpio == GPIOC) ||
               (gpio == GPIOE),
           BSP_GPIO_ERROR);
  __ASSERT((pin >= 0) && (pin < 16), BSP_GPIO_ERROR);
  __ASSERT((state == 0) | (state == 1), BSP_GPIO_ERROR);

  HAL_GPIO_WritePin(gpio, pin, state);
  return BSP_GPIO_OK;
}

GPIO_PinState bsp_gpio_read_pin(GPIO_TypeDef *gpio, uint16_t pin)
{
  __ASSERT((gpio == GPIOA) ||
               (gpio == GPIOB) ||
               (gpio == GPIOC) ||
               (gpio == GPIOE),
           BSP_GPIO_ERROR);
  __ASSERT((pin >= 0) && (pin < 16), BSP_GPIO_ERROR);

  return HAL_GPIO_ReadPin(gpio, pin);
}

bsp_gpio_status_t bsp_gpio_toggle_pin(GPIO_TypeDef *gpio, uint16_t pin)
{
  __ASSERT((gpio == GPIOA) ||
               (gpio == GPIOB) ||
               (gpio == GPIOC) ||
               (gpio == GPIOE),
           BSP_GPIO_ERROR);
  __ASSERT((pin >= 0) && (pin < 16), BSP_GPIO_ERROR);
  HAL_GPIO_TogglePin(gpio, pin);
  return BSP_GPIO_OK;
}

bsp_gpio_status_t bsp_gpio_exti_enable(uint16_t pin)
{
  __ASSERT((pin >= 0) && (pin < 16), BSP_GPIO_ERROR);

  IRQn_Type exti_line;

  switch (pin)
  {
  case GPIO_PIN_0:
    exti_line = EXTI0_IRQn;
    break;

  case GPIO_PIN_1:
    exti_line = EXTI1_IRQn;
    break;

  case GPIO_PIN_2:
    exti_line = EXTI2_IRQn;
    break;

  case GPIO_PIN_3:
    exti_line = EXTI3_IRQn;
    break;

  case GPIO_PIN_4:
    exti_line = EXTI4_IRQn;
    break;

  case GPIO_PIN_5:
  case GPIO_PIN_6:
  case GPIO_PIN_7:
  case GPIO_PIN_8:
  case GPIO_PIN_9:
    exti_line = EXTI9_5_IRQn;
    break;

  case GPIO_PIN_10:
  case GPIO_PIN_11:
  case GPIO_PIN_12:
  case GPIO_PIN_13:
  case GPIO_PIN_14:
  case GPIO_PIN_15:
    exti_line = EXTI15_10_IRQn;
    break;

  default:
    break;
  }

  HAL_NVIC_EnableIRQ(exti_line);

  return BSP_GPIO_OK;
}

bsp_gpio_status_t bsp_gpio_exti_disable(uint16_t pin)
{
  __ASSERT((pin >= 0) && (pin < 16), BSP_GPIO_ERROR);

  IRQn_Type exti_line;

  switch (pin)
  {
  case GPIO_PIN_0:
    exti_line = EXTI0_IRQn;
    break;

  case GPIO_PIN_1:
    exti_line = EXTI1_IRQn;
    break;

  case GPIO_PIN_2:
    exti_line = EXTI2_IRQn;
    break;

  case GPIO_PIN_3:
    exti_line = EXTI3_IRQn;
    break;

  case GPIO_PIN_4:
    exti_line = EXTI4_IRQn;
    break;

  case GPIO_PIN_5:
  case GPIO_PIN_6:
  case GPIO_PIN_7:
  case GPIO_PIN_8:
  case GPIO_PIN_9:
    exti_line = EXTI9_5_IRQn;
    break;

  case GPIO_PIN_10:
  case GPIO_PIN_11:
  case GPIO_PIN_12:
  case GPIO_PIN_13:
  case GPIO_PIN_14:
  case GPIO_PIN_15:
    exti_line = EXTI15_10_IRQn;
    break;

  default:
    break;
  }

  HAL_NVIC_DisableIRQ(exti_line);

  return BSP_GPIO_OK;
}

bsp_gpio_status_t bsp_gpio_exti_handler(uint16_t pin)
{
  drv_button_status_t ret = DRV_BUTTON_OK;

  ret = drv_button_exti_handler(pin);
  __ASSERT(ret == DRV_BUTTON_OK, BSP_GPIO_ERROR);

  return BSP_GPIO_OK;
}
/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */