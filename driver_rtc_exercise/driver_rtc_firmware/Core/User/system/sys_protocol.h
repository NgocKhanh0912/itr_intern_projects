/**

 * @file       sys_protocol.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-19
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Manage the PC interface process
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_PROTOCOL_H
#define __USER_SYS_PROTOCOL_H

/* Includes ----------------------------------------------------------- */
#include "drv_serial.h"
#include "drv_ds1307.h"
#include "cbuffer.h"
/* Public defines ----------------------------------------------------- */
#define SYS_PROTOCOL_MAX_NODE (1)
/* Public enumerate/structure ----------------------------------------- */
enum sys_protocol_status_t
{
  SYS_PROTOCOL_ERROR = -2,
  SYS_PROTOCOL_FAILED,
  SYS_PROTOCOL_OK
};
typedef struct
{
  uint8_t data_length;
  uint32_t cmd;
  uint8_t *data;
} sys_protocol_packet_format_t;

typedef enum
{
  SYS_PROTOCOL_STATE_IDLE = -2,
  SYS_PROTOCOL_STATE_TRANSMIT,
  SYS_PROTOCOL_STATE_RECEIVE
} sys_protocol_state_t;

typedef enum
{
  SYS_PROTOCOL_NODE_MNG = 0
} sys_protocol_node_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Start the system to control protocol
 *
 * @param[in] uart  Hardware UART handler
 *
 * @return
 *  - (-2): Error
 *  - (-1): Failed
 *  -  (0): Success
 */
uint32_t sys_protocol_init(UART_HandleTypeDef *uart);
uint32_t sys_protocol_register_node_to_send(sys_protocol_node_t rx_node, cbuffer_t *rx_cb);
uint32_t sys_protocol_send_packet_to_node(sys_protocol_node_t rx_node, uint8_t *data, uint16_t size);
uint32_t sys_protocol_send_packet_to_port(uint8_t *data, uint16_t size);

#endif // __USER_SYS_PROTOCOL_H

/* End of file -------------------------------------------------------- */
