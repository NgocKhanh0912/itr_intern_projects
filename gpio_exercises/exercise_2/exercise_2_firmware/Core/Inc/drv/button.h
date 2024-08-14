/**
 * @file       button.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       05/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      driver for interfacing to button
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRV_BUTTON_H_
#define INC_DRV_BUTTON_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"
/* Public defines ----------------------------------------------------- */
#define BUTTON_DEBOUNCE_TIME  (50UL)
#define BUTTON_RELEASE_TIME   (300UL)
#define BUTTON_HOLD_TIME      (3000UL)
#define BUTTON_CLICK_TIME     (500UL)
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BUTTON_STATUS_FAIL = 0U,
  BUTTON_STATUS_OK = 1U,
  BUTTON_STATUS_ERROR = 2U
} button_status_t;

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t pin;
  GPIO_PinState state;
} button_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief       this function initializes the button
 *
 * @param[in]   sys_button  system saves all information related to button in this variable
 *
 * @attention   only active-high button
 *
 * @return      button_status_t
 */
button_status_t button_init(button_t sys_button);

/**
 * @brief       this function get state of the button
 *
 * @param[in]   sys_button  this function get state of the button and save in this variable
 *
 * @attention   only active-high button
 *
 * @return      button_status_t
 */
button_status_t button_get_state(GPIO_PinState *button_state);

/**
 * @brief       this function get SysTick
 *
 * @param[in]   None
 *
 * @return      current SysTick
 */
uint32_t button_get_tick();

#endif /* INC_DRV_BUTTON_H_ */
