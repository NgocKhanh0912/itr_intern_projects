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
#include "drv/drv_button.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_button_status_t drv_button_init(bsp_gpio_t *gpio_button)
{
  bsp_gpio_init(gpio_button);
  return BUTTON_STATUS_OK;
}

GPIO_PinState drv_button_read_pin(bsp_gpio_t *gpio_button)
{
  return bsp_gpio_read_pin(gpio_button);
}

uint32_t drv_button_get_tick()
{
  return bsp_get_systick();
}

/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
