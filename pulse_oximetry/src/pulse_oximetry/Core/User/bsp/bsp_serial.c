/**
 * @file       bsp_cp2102.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-19
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs support CP2102 UART to TTL interface
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_serial.h"
#include "common.h"
#include <string.h>
#include <stdbool.h>
/* Private defines ---------------------------------------------------- */
#define DMA_BUFFER_SIZE (16)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_serial_t b_serial;
static bsp_evt_cb_t b_new_rx_data_cb;

static uint8_t dma_buffer[DMA_BUFFER_SIZE] = {0};
static uint8_t swap_buffer_a[DMA_BUFFER_SIZE] = {0};
static uint8_t swap_buffer_b[DMA_BUFFER_SIZE] = {0};

/* Private function prototypes ---------------------------------------- */
/**
 * @brief         Handle the trigger of data receive event
 *
 * @param[in]     uart   Hardware UART handler
 * @param[in]     size   Size of receiver buffer
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Fail
 *  - (0x3FFFFFFF) : Success
 */
static void bsp_serial_rx_evt_handler(UART_HandleTypeDef *uart, uint16_t size);
/* Function definitions ----------------------------------------------- */
uint32_t bsp_serial_init(UART_HandleTypeDef *uart)
{
  __ASSERT(uart != NULL, BSP_SERIAL_ERROR);

  b_serial.uart = uart;
  b_serial.dma_buf = dma_buffer;
  b_serial.reception_buf = swap_buffer_a;
  b_serial.handle_buf = swap_buffer_b;
  b_serial.size = DMA_BUFFER_SIZE;
  b_serial.reader = 0;
  b_serial.received_bytes = 0;

  uint32_t ret = BSP_UART_OK;
  ret = bsp_uart_start_receive_to_idle_dma(b_serial.uart, b_serial.dma_buf, b_serial.size);
  __ASSERT(ret == BSP_UART_OK, BSP_SERIAL_FAILED);

  ret = bsp_uart_register_cb_function(bsp_serial_rx_evt_handler);
  __ASSERT(ret == BSP_UART_OK, BSP_SERIAL_FAILED);

  return BSP_SERIAL_OK;
}

uint32_t bsp_serial_transmit(uint8_t *tx_buf, uint16_t tx_size)
{
  __ASSERT(tx_buf != NULL, BSP_SERIAL_ERROR);

  uint32_t ret = BSP_UART_OK;
  ret = bsp_uart_transmit(b_serial.uart, tx_buf, tx_size);
  __ASSERT(ret == BSP_UART_OK, BSP_SERIAL_FAILED);

  return BSP_SERIAL_OK;
}

uint32_t bsp_serial_receive(uint8_t *rx_buf)
{
  __ASSERT(rx_buf != NULL, BSP_SERIAL_ERROR);

  for (uint8_t i = 0; i < b_serial.received_bytes; i++)
  {
    rx_buf[i] = b_serial.handle_buf[i];
  }

  return BSP_SERIAL_OK;
}

uint32_t bsp_serial_register_cb_function(bsp_evt_cb_t new_rx_data_cb)
{
  __ASSERT(new_rx_data_cb != NULL, BSP_SERIAL_ERROR);

  b_new_rx_data_cb = new_rx_data_cb;

  return BSP_SERIAL_OK;
}

/* Private definitions ------------------------------------------------ */
static void bsp_serial_rx_evt_handler(UART_HandleTypeDef *uart, uint16_t size)
{
  static bool is_start_packet = false;
  uint8_t *temp;
  if (uart->Instance == b_serial.uart->Instance)
  {
    if (size != b_serial.reader)
    {
      if (size > b_serial.reader)
      {
        b_serial.received_bytes = size - b_serial.reader;

        for (uint32_t i = 0; i < b_serial.received_bytes; i++)
        {
          b_serial.reception_buf[i] = b_serial.dma_buf[b_serial.reader + i];
        }
      }
      else
      {
        b_serial.received_bytes = b_serial.size - b_serial.reader;
        for (uint8_t i = 0; i < b_serial.received_bytes; i++)
        {
          b_serial.reception_buf[i] = b_serial.dma_buf[b_serial.reader + i];
        }

        if (size > 0)
        {
          for (uint8_t i = 0; i < size; i++)
          {
            b_serial.reception_buf[b_serial.received_bytes + i] = b_serial.dma_buf[i];
          }
          b_serial.received_bytes += size;
        }
      }
      temp = b_serial.reception_buf;
      b_serial.reception_buf = b_serial.handle_buf;
      b_serial.handle_buf = temp;

      if (strchr((const char *)b_serial.handle_buf, START_BYTE) != NULL)
      {
        is_start_packet = true;
      }

      if (is_start_packet)
      {
        __CALLBACK(b_new_rx_data_cb, b_serial.received_bytes);
      }

      if (strchr((const char *)b_serial.handle_buf, STOP_BYTE) != NULL)
      {
        is_start_packet = false;
      }
    }
    b_serial.reader = size;
  }
}
/* End of file -------------------------------------------------------- */
