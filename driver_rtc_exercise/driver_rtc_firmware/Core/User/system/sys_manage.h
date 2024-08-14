/**
 * @file       sys_manage.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-07-22
 * @authors    Viet Hoang Xuan
 *             Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_MANAGE_H
#define __SYS_MANAGE_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "sys_protocol.h"
#include "sys_time.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_MANAGE_ERROR = -2,
  SYS_MANAGE_FAILED,
  SYS_MANAGE_OK
} sys_manage_status_t;

typedef enum
{
  SYS_MANAGE_IDLE = -1,
  SYS_MANAGE_SET_TIME_24H = 0,
  SYS_MANAGE_SET_TIME_12H,
  SYS_MANAGE_SET_EPOCH_TIME,
  SYS_MANAGE_GET_TIME,
  SYS_MANAGE_SET_TIME_FORMAT,
  SYS_MANAGE_SET_ALARM_MODE_12H,
  SYS_MANAGE_SET_ALARM_MODE_24H,
  SYS_MANAGE_CANCEL_ALARM
} sys_manage_cmd_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

sys_manage_status_t sys_manage_start(UART_HandleTypeDef *uart,
                                     I2C_HandleTypeDef *i2c);
sys_manage_status_t sys_manage_loop();
#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
