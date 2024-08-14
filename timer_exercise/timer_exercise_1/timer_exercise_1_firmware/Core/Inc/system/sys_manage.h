/**
 * @file       sys_manage.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      System for manage fsm of the system
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */

#ifndef INC_SYSTEM_SYS_MANAGE_H_
#define INC_SYSTEM_SYS_MANAGE_H_

/* Includes ----------------------------------------------------------- */
#include "system/sys_button.h"
#include "system/sys_led.h"
#include "bsp/bsp_timer.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  IDLE = 0,
  LED1_BLINK,
  LED1_WAIT_TRANSIT,
  LED1_WAIT_OFF,
  LED2_BLINK,
  LED2_WAIT_TRANSIT,
  LED2_WAIT_OFF,
  LED3_BLINK,
  LED3_WAIT_TRANSIT,
  LED3_WAIT_OFF,
} sys_fsm_state_t;

typedef enum
{
  SYS_ERROR = -1,
  SYS_OK = 0,
} sys_status_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       this function manage the state of the system
 *
 * @param[in]   *BUTTON:  bsp_gpio_t type of button variable that defined by user
 * @param[in]   *LED:  bsp_gpio_t type of LEDs variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 * @param[in]   htim          Pointer of timer handler.
 * @param[in]   autoreload    Desired counter period.
 * @param[in]   prescale      Desired prescaler .
 * @return      sys_status_t
 */
sys_status_t sys_init(bsp_gpio_t *BUTTON, bsp_gpio_t *LED,
                      drv_led_active_level_t led_active_level,
                      TIM_HandleTypeDef *htim, uint32_t prescaler, uint32_t autoreload);

/**
 * @brief       this function manage the state of the system
 *
 * @param[in]   *BUTTON:  bsp_gpio_t type of button variable that defined by user
 * @param[in]   *LED:  bsp_gpio_t type of LEDs variable that defined by user
 * @param[in]   led_active_level: LED active LOW or LED active HIGH
 * @return      sys_status_t
 */
sys_status_t sys_manage_fsm(bsp_gpio_t *LED,
                            drv_led_active_level_t led_active_level,
                            sys_button_evt_t button_evt,
							              bool *timer_flag);

#endif /* INC_SYSTEM_SYS_MANAGE_H_ */
