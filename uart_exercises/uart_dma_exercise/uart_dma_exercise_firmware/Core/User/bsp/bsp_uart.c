/**
 * @file       bsp_uart.C
 * @copyright
 * @license
 * @version    1.0.0
 * @date       13/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs of BSP UART
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_uart.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define TIME_OUT_TRANSMIT_UART (1000)

const uint8_t b_uart_start_it_msg[] = "\r\nStart UART in INTERRUPT mode finished successfully!\r\n";
const uint8_t b_uart_start_dma_msg[] = "\r\nStart UART in DMA mode finished successfully!\r\n";
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static bsp_uart_cb_t b_uart_rx_evt_cb = NULL;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_uart_start_receive_to_idle_it(UART_HandleTypeDef *huart,
                                           uint8_t *rx_data, uint16_t bytes)
{
  __ASSERT(huart != NULL, BSP_UART_ERROR);
  __ASSERT(rx_data != NULL, BSP_UART_ERROR);
  __ASSERT(bytes > 0, BSP_UART_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_UARTEx_ReceiveToIdle_IT(huart, rx_data, bytes);
  __ASSERT(ret == HAL_OK, BSP_UART_FAIL);

  ret = HAL_UART_Transmit(huart,
                          b_uart_start_it_msg,
                          __SIZE_OF(b_uart_start_it_msg),
                          TIME_OUT_TRANSMIT_UART);

  __ASSERT(ret == HAL_OK, BSP_UART_FAIL);

  return BSP_UART_OK;
}

uint32_t bsp_uart_start_receive_to_idle_dma(UART_HandleTypeDef *huart,
                                            uint8_t *rx_data, uint16_t bytes)
{
  __ASSERT(huart != NULL, BSP_UART_ERROR);
  __ASSERT(rx_data != NULL, BSP_UART_ERROR);
  __ASSERT(bytes > 0, BSP_UART_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_data, bytes);
  __ASSERT(ret == HAL_OK, BSP_UART_FAIL);

  ret = HAL_UART_Transmit(huart,
                          b_uart_start_dma_msg,
                          __SIZE_OF(b_uart_start_dma_msg),
                          TIME_OUT_TRANSMIT_UART);

  __ASSERT(ret == HAL_OK, BSP_UART_FAIL);

  return BSP_UART_OK;
}

uint32_t bsp_uart_transmit(UART_HandleTypeDef *huart,
                           uint8_t *tx_data, uint16_t data_len)
{
  __ASSERT(huart != NULL, BSP_UART_ERROR);
  __ASSERT(tx_data != NULL, BSP_UART_ERROR);
  __ASSERT(data_len > 0, BSP_UART_ERROR);

  HAL_StatusTypeDef ret = HAL_OK;
  ret = HAL_UART_Transmit(huart, tx_data, data_len, TIME_OUT_TRANSMIT_UART);
  __ASSERT(ret == HAL_OK, BSP_UART_FAIL);

  return BSP_UART_OK;
}

uint32_t bsp_uart_register_cb_function(bsp_uart_cb_t rx_evt_cb)
{
  __ASSERT(rx_evt_cb != NULL, BSP_UART_ERROR);

  b_uart_rx_evt_cb = rx_evt_cb;

  return BSP_UART_OK;
}

uint32_t bsp_uart_rx_cb_handler(UART_HandleTypeDef *uart, uint16_t size)
{
  __ASSERT(b_uart_rx_evt_cb != NULL, BSP_UART_ERROR);

  __CALLBACK(b_uart_rx_evt_cb, uart, size);

  return BSP_UART_OK;
}

/* Private function definitions --------------------------------------- */
/* End of file -------------------------------------------------------- */
