/**
 * @file       drv_buzzer.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       31/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Driver for interfacing with the passive buzzer
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef USER_BSP_UTILS_H_
#define USER_BSP_UTILS_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief       Get time that from current to begining of the system.
 *
 * @return      current tick of system.
 */
uint32_t bsp_utils_get_tick();

#endif /* USER_BSP_UTILS_H_ */