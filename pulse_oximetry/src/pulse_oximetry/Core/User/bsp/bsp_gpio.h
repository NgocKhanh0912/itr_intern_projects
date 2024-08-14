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
#ifndef USER_BSP_BSP_GPIO_H_
#define USER_BSP_BSP_GPIO_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BSP_GPIO_ERROR = 0xFFFFFFFF,
  BSP_GPIO_FAIL = 0x7FFFFFFF,
  BSP_GPIO_OK = 0x3FFFFFFF
} bsp_gpio_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function write logic level for the OUTPUT GPIO
 *
 * @param[in]   gpio  Pointer point to GPIO port
 * @param[in]   pin   pin of that port
 * @param[in]   gpio_state:  Logic level you want to write
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_gpio_status_t bsp_gpio_write_pin(GPIO_TypeDef *gpio, uint16_t pin, GPIO_PinState gpio_state);

/**
 * @brief       This function read logic level of the INPUT GPIO
 *
 * @param[in]   gpio  Pointer point to GPIO port
 * @param[in]   pin   pin of that port
 *
 * @return      GPIO_PIN_RESET or GPIO_PIN_SET
 */
GPIO_PinState bsp_gpio_read_pin(GPIO_TypeDef *gpio, uint16_t pin);

/**
 * @brief       This function toggle logic level for the OUTPUT GPIO
 *
 * @param[in]   gpio  Pointer point to GPIO port
 * @param[in]   pin   pin of that port
 *
 * @attention   gpio->mode: Must be OUTPUT (PP, OD)
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_gpio_status_t bsp_gpio_toggle_pin(GPIO_TypeDef *gpio, uint16_t pin);

/**
 * @brief       This function enable external interrupt line
 *
 * @param[in]   pin  Same pin per port is in the same external interrupt line
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_gpio_status_t bsp_gpio_exti_enable(uint16_t pin);

/**
 * @brief       This function disable external interrupt line
 *
 * @param[in]   pin  Same pin per port is in the same external interrupt line
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_gpio_status_t bsp_gpio_exti_enable(uint16_t pin);

/**
 * @brief       This function handle external interrupt line
 *
 * @param[in]   pin  Same pin per port is in the same external interrupt line
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_gpio_status_t bsp_gpio_exti_handler(uint16_t pin);

#endif /* USER_BSP_BSP_GPIO_H_ */