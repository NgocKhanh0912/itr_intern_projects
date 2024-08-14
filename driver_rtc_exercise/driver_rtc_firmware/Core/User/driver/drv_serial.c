/**
 * @file       drv_cp2102.c
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
#include "drv_serial.h"
#include "common.h"
#include <string.h>
#include <stdbool.h>
/* Private defines ---------------------------------------------------- */
#define DMA_BUFFER_SIZE (20)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static drv_serial_t d_serial;
static drv_evt_cb_t d_new_rx_data_cb;

const uint8_t start_byte[] = "@@";
const uint8_t stop_bytes[] = "&&";

static uint8_t dma_buffer[DMA_BUFFER_SIZE] = {0};
static uint8_t swap_buffer_a[DMA_BUFFER_SIZE] = {0};
static uint8_t swap_buffer_b[DMA_BUFFER_SIZE] = {0};

const uint8_t drv_start_msg[] = "\r\nStart driver Serial finished SUCCESSFULLY!\r\n";
/* Private function prototypes ---------------------------------------- */
/**
 * @brief         Handle the trigger of data receive event
 *
 * @param[in]     uart   Hardware UART handler
 * @param[in]     size   Size of receiver buffer
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
static void drv_serial_rx_evt_handler(UART_HandleTypeDef *uart, uint16_t size);
/* Function definitions ----------------------------------------------- */
uint32_t drv_serial_init(UART_HandleTypeDef *uart)
{
  __ASSERT(uart != NULL, DRV_SERIAL_ERROR);

  d_serial.uart = uart;
  d_serial.dma_buf = dma_buffer;
  d_serial.reception_buf = swap_buffer_a;
  d_serial.handle_buf = swap_buffer_b;
  d_serial.size = DMA_BUFFER_SIZE;
  d_serial.reader = 0;
  d_serial.received_bytes = 0;

  uint32_t ret = BSP_UART_OK;
  ret = bsp_uart_start_receive_to_idle_dma(d_serial.uart, d_serial.dma_buf, d_serial.size);
  __ASSERT(ret == BSP_UART_OK, DRV_SERIAL_FAILED);

  ret = bsp_uart_register_cb_function(drv_serial_rx_evt_handler);
  __ASSERT(ret == BSP_UART_OK, DRV_SERIAL_FAILED);

  ret = bsp_uart_transmit(d_serial.uart, (uint8_t *)drv_start_msg, __SIZE_OF(drv_start_msg));
  __ASSERT(ret == BSP_UART_OK, DRV_SERIAL_FAILED);

  return DRV_SERIAL_OK;
}

uint32_t drv_serial_transmit(uint8_t *tx_buf, uint16_t tx_size)
{
  __ASSERT(tx_buf != NULL, DRV_SERIAL_ERROR);

  uint32_t ret = BSP_UART_OK;
  ret = bsp_uart_transmit(d_serial.uart, tx_buf, tx_size);
  __ASSERT(ret == BSP_UART_OK, DRV_SERIAL_FAILED);

  return DRV_SERIAL_OK;
}

uint32_t drv_serial_receive(uint8_t *rx_buf)
{
  __ASSERT(rx_buf != NULL, DRV_SERIAL_ERROR);

  for (uint8_t i = 0; i < d_serial.received_bytes; i++)
  {
    rx_buf[i] = d_serial.handle_buf[i];
  }

  return DRV_SERIAL_OK;
}

uint32_t drv_serial_register_cb_function(drv_evt_cb_t new_rx_data_cb)
{
  __ASSERT(new_rx_data_cb != NULL, DRV_SERIAL_ERROR);

  d_new_rx_data_cb = new_rx_data_cb;

  return DRV_SERIAL_OK;
}

/* Private definitions ------------------------------------------------ */
static void drv_serial_rx_evt_handler(UART_HandleTypeDef *uart, uint16_t size)
{
  static bool is_start_packet = false;
  uint8_t *temp;
  if (uart->Instance == d_serial.uart->Instance)
  {
    if (size != d_serial.reader)
    {
      if (size > d_serial.reader)
      {
        d_serial.received_bytes = size - d_serial.reader;

        for (uint32_t i = 0; i < d_serial.received_bytes; i++)
        {
          d_serial.reception_buf[i] = d_serial.dma_buf[d_serial.reader + i];
        }
      }
      else
      {
        d_serial.received_bytes = d_serial.size - d_serial.reader;
        for (uint8_t i = 0; i < d_serial.received_bytes; i++)
        {
          d_serial.reception_buf[i] = d_serial.dma_buf[d_serial.reader + i];
        }

        if (size > 0)
        {
          for (uint8_t i = 0; i < size; i++)
          {
            d_serial.reception_buf[d_serial.received_bytes + i] = d_serial.dma_buf[i];
          }
          d_serial.received_bytes += size;
        }
      }
      temp = d_serial.reception_buf;
      d_serial.reception_buf = d_serial.handle_buf;
      d_serial.handle_buf = temp;

      if (strchr((const char *)d_serial.handle_buf, '@') != NULL)
      {
        is_start_packet = true;
      }

      if (is_start_packet)
      {
        __CALLBACK(d_new_rx_data_cb, d_serial.received_bytes);
      }

      if (strchr((const char *)d_serial.handle_buf, '&') != NULL)
      {
        is_start_packet = false;
      }
    }
    d_serial.reader = size;
  }
}
/* End of file -------------------------------------------------------- */
