/**
 * @file       drv_button.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRV_DRV_BUTTON_H_
#define INC_DRV_DRV_BUTTON_H_

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp_gpio.h"
#include "bsp/bsp_timer.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BUTTON_STATUS_OK = 1U,
  BUTTON_STATUS_ERROR = 2U
} drv_button_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function initializes the button
 *
 * @param[in]   *gpio_button:  bsp_gpio_t type of variable that defined by user
 *
 * @attention   None
 *
 * @return      return BUTTON_STATUS_OK
 */
drv_button_status_t drv_button_init(bsp_gpio_t *gpio_button);

/**
 * @brief       This function read logic level of the button
 *
 * @param[in]   *gpio_button:  bsp_gpio_t type of variable that defined by user
 *
 * @attention   gpio_button->mode: Must be OUTPUT (PP, OD)
 *
 * @return      Pin state of the button
 */
GPIO_PinState drv_button_read_pin(bsp_gpio_t *gpio_button);

/**
 * @brief       This function get SysTick
 *
 * @param[in]   None
 *
 * @return      current SysTick
 */
uint32_t drv_button_get_tick();

#endif /* INC_DRV_DRV_BUTTON_H_ */
