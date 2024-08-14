/**
 * @file       sys_protocol.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.1
 * @date       2024-07-29
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
#ifndef __SYS_PROTOCOL_H
#define __SYS_PROTOCOL_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "cbuffer.h"
/* Public defines ----------------------------------------------------- */
#define SYS_PROTOCOL_MAX_NODE (1)
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_PROTOCOL_ERROR = 0xFFFFFFFF,
  SYS_PROTOCOL_FAILED = 0x7FFFFFFF,
  SYS_PROTOCOL_OK = 0x3FFFFFFF
} sys_protocol_status_t;
typedef struct
{
  uint8_t command;
  uint32_t data;
  uint8_t threshold_level;
} sys_protocol_pkt_t;
typedef enum
{
  SYS_PROTOCOL_SYS_MNG = 0
} sys_protocol_node_t;
/* Public macros ------------------------------------------------------ */
#define COMMAND_FIELD (0xFF)
#define DATA_FIELD (0xFF)
#define TH_LEVEL_FIELD (0xFF)
#define PKT_SIZE (6)
#define CMD_PKT_SIZE (1)
#define DATA_PKT_SIZE (4)
#define TH_PKT_SIZE (1)
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief                 Start system protocol
 *
 * @param[in]     uart    Hardware UART handler
 *
 * @return
 * -  (0xFFFFFFFF)  : Error
 * -  (0x7FFFFFFF)  : Failed
 * -  (0x3FFFFFFF)  : Success
 */
uint32_t sys_protocol_init(UART_HandleTypeDef *uart);
/**
 * @brief                 Register node to send packet to
 *
 * @param[in]     rx_node Node to register
 * @param[in]     rx_cb   List of node
 *
 * @return
 * -  (0xFFFFFFFF)  : Error
 * -  (0x7FFFFFFF)  : Failed
 * -  (0x3FFFFFFF)  : Success
 */
uint32_t sys_protocol_register_node_to_send(sys_protocol_node_t rx_node, cbuffer_t *rx_cb);
/**
 * @brief                 Send packet to node registered
 *
 * @param[in]     rx_node Node to be sent
 * @param[in]     pkt     Packet to be sent
 *
 * @return
 * -  (0xFFFFFFFF)  : Error
 * -  (0x7FFFFFFF)  : Failed
 * -  (0x3FFFFFFF)  : Success
 */
uint32_t sys_protocol_send_pkt_to_node(sys_protocol_node_t rx_node, sys_protocol_pkt_t pkt);
/**
 * @brief                 Send packet to COM port
 *
 * @param[in]     pkt     Packet to be sent
 *
 * @return
 * -  (0xFFFFFFFF)  : Error
 * -  (0x7FFFFFFF)  : Failed
 * -  (0x3FFFFFFF)  : Success
 */
uint32_t sys_protocol_send_pkt_to_port(sys_protocol_pkt_t pkt);
#endif // __SYS_PROTOCOL_H

/* End of file -------------------------------------------------------- */
