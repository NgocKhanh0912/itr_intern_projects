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
#ifndef USER_DRV_DRV_BUTTON_H_
#define USER_DRV_DRV_BUTTON_H_

/* Includes ----------------------------------------------------------- */
#include "bsp_gpio.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  DRV_BUTTON_FAIL = 0xFFFFFFFF,
  DRV_BUTTON_ERROR = 0x7FFFFFFF,
  DRV_BUTTON_OK = 0x3FFFFFFF
} drv_button_status_t;

typedef struct __attribute__((__packed__))
{
  GPIO_TypeDef *port;
  uint16_t pin;
  uint32_t time_debounce;
  uint32_t time_change;
  uint32_t current_state;
  uint32_t active_level;
  uint32_t click_cnt;
} drv_button_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
typedef void (*drv_button_callback)(uint16_t exti_line);
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       This function initializes the button
 *
 * @param[in]   button      Pointer points to the button data
 * @param[in]   button_port Pointer points to port connecting to the button
 * @param[in]   button_pin  Pin of that port
 * @param[in]   button_active_level Determine the active high or active low button
 *
 * @attention   None
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
drv_button_status_t drv_button_init(drv_button_t *button,
                                    GPIO_TypeDef *button_port,
                                    uint16_t button_pin,
                                    uint32_t button_active_level);

/**
 * @brief       This function handle the button external interrupt
 *
 * @param[in]   exti_line  External interrupt line
 *
 * @attention   None
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
drv_button_status_t drv_button_exti_handler(uint16_t exti_line);

/**
 * @brief       This function register the callback function for external interrupt
 *
 * @param[in]   callback_function  External interrupt line
 *
 * @attention   None
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
drv_button_status_t drv_button_register_callback(drv_button_callback callback_function);

#endif /* USER_DRV_DRV_BUTTON_H_ */