/**
 * @file       sys_protocol.c
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
 * @note
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_protocol.h"
#include "common.h"
#include <string.h>
#include <stdbool.h>
/* Private defines ---------------------------------------------------- */
#define PACKET_MAX_LENGTH (108)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
const uint8_t s_protocol_msg[] = "\r\nStart the System Protocol finished SUCCESSFULLY!\r\n";
static bool s_packet_cplt_flag = false;
static uint8_t s_packet_buf[PACKET_MAX_LENGTH] = {0};
static uint8_t s_packet[PACKET_MAX_LENGTH] = {0};
static uint16_t s_received_bytes = 0;

static cbuffer_t *s_protocol_node[SYS_PROTOCOL_MAX_NODE] = {NULL};
/* Private function prototypes ---------------------------------------- */
static void sys_protocol_receive_packet_cplt_handler(uint16_t received_bytes);
/* Function definitions ----------------------------------------------- */
uint32_t sys_protocol_init(UART_HandleTypeDef *uart)
{
  __ASSERT(uart != NULL, SYS_PROTOCOL_ERROR);

  uint32_t ret = drv_serial_init(uart);
  __ASSERT(ret == DRV_SERIAL_OK, SYS_PROTOCOL_FAILED);

  ret = drv_serial_register_cb_function(sys_protocol_receive_packet_cplt_handler);
  __ASSERT(ret == DRV_SERIAL_OK, SYS_PROTOCOL_FAILED);

  ret = drv_serial_transmit((uint8_t *)s_protocol_msg, __SIZE_OF(s_protocol_msg));
  __ASSERT(ret == DRV_SERIAL_OK, SYS_PROTOCOL_FAILED);

  return SYS_PROTOCOL_OK;
}
uint32_t sys_protocol_register_node_to_send(sys_protocol_node_t rx_node, cbuffer_t *rx_cb)
{
  __ASSERT(rx_node < SYS_PROTOCOL_MAX_NODE, SYS_PROTOCOL_ERROR);
  __ASSERT(rx_cb != NULL, SYS_PROTOCOL_ERROR);

  s_protocol_node[rx_node] = rx_cb;

  return SYS_PROTOCOL_OK;
}

uint32_t sys_protocol_send_packet_to_node(sys_protocol_node_t rx_node, uint8_t *data, uint16_t size)
{
  __ASSERT(s_protocol_node[rx_node] != NULL, SYS_PROTOCOL_ERROR);
  __ASSERT(data != NULL, SYS_PROTOCOL_ERROR);
  __ASSERT(size > 0, SYS_PROTOCOL_ERROR);

  if (cb_space_count(s_protocol_node[rx_node]) < size)
  {
    return SYS_PROTOCOL_FAILED;
  }

  cb_write(s_protocol_node[rx_node], data, size);
  return SYS_PROTOCOL_OK;
}

uint32_t sys_protocol_send_packet_to_port(uint8_t *data, uint16_t size)
{
  __ASSERT(data != NULL, SYS_PROTOCOL_ERROR);
  __ASSERT(size > 0, SYS_PROTOCOL_ERROR);

  uint32_t ret = DRV_SERIAL_OK;
  ret = drv_serial_transmit(data, size);
  __ASSERT(ret == DRV_SERIAL_OK, DRV_SERIAL_FAILED);

  return DRV_SERIAL_OK;
}

/* Private definitions ----------------------------------------------- */
static void sys_protocol_receive_packet_cplt_handler(uint16_t received_bytes)
{
  drv_serial_receive(s_packet_buf + s_received_bytes);
  s_received_bytes += received_bytes;
  uint8_t *start_byte_pos = strstr(s_packet_buf, "@@");
  uint8_t *stop_byte_pos = strstr(s_packet_buf, "&&");

  if ((start_byte_pos != NULL) && (stop_byte_pos != NULL))
  {
    if (strstr(start_byte_pos + 1, "@@") != NULL)
    {
      start_byte_pos = strstr(start_byte_pos + 1, "@@");
    }
    memmove(s_packet, start_byte_pos + 2, stop_byte_pos - start_byte_pos - 2);
    s_packet_cplt_flag = true;
  }
  if (s_packet_cplt_flag)
  {
    uint16_t data_length = (s_packet[1] - '0') * 10 + (s_packet[2] - '0') + 3;
    sys_protocol_send_packet_to_node(SYS_PROTOCOL_NODE_MNG, s_packet, data_length);
    memset(s_packet_buf, 0, 108);
    s_received_bytes = 0;
    s_packet_cplt_flag = false;
  }
}