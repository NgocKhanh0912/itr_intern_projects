/**
 * @file       bsp_gpio.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      BSP for interfacing between HAL and top layers
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_BSP_BSP_GPIO_H_
#define INC_BSP_BSP_GPIO_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t pin;
  GPIO_PinState state;
  uint32_t mode;
} bsp_gpio_t;

typedef enum
{
  GPIO_STATUS_ERROR = -1,
  GPIO_STATUS_FAIL,
  GPIO_STATUS_OK
} bsp_gpio_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function initializes the GPIO
 *
 * @param[in]   *gpio:  bsp_gpio_t type of variable that defined by user
 *
 * @attention   None
 *
 * @return      GPIO_STATUS_OK
 */
bsp_gpio_status_t bsp_gpio_init(bsp_gpio_t *gpio);

/**
 * @brief       This function write logic level for the OUTPUT GPIO
 *
 * @param[in]   *gpio:  bsp_gpio_t type of variable that defined by user
 * @param[in]   gpio_state:  Logic level you want to write
 *
 * @attention   gpio->mode: Must be OUTPUT (PP, OD)
 *
 * @return      GPIO_STATUS_OK
 */
bsp_gpio_status_t bsp_gpio_write_pin(bsp_gpio_t *gpio, GPIO_PinState gpio_state);

/**
 * @brief       This function read logic level of the INPUT GPIO
 *
 * @param[in]   *gpio:  bsp_gpio_t type of variable that defined by user
 *
 * @attention   gpio->mode: Must be INPUT
 *
 * @return      GPIO_PIN_RESET or GPIO_PIN_SET
 */
GPIO_PinState bsp_gpio_read_pin(bsp_gpio_t *gpio);

/**
 * @brief       This function toggle logic level for the OUTPUT GPIO
 *
 * @param[in]   *gpio:  bsp_gpio_t type of variable that defined by user
 *
 * @attention   gpio->mode: Must be OUTPUT (PP, OD)
 *
 * @return      GPIO_STATUS_OK
 */
bsp_gpio_status_t bsp_gpio_toggle_pin(bsp_gpio_t *gpio);

#endif /* INC_BSP_BSP_GPIO_H_ */
