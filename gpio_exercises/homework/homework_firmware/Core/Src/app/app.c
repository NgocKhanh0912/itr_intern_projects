/**
 * @file       app.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Pass input to system_manage to perform functions on LEDs
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "app/app.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void app()
{
  sys_manage_loop();
}

/* End of file -------------------------------------------------------- */
