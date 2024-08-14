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
#include "bsp/bsp_uart.h"

/* Private defines ---------------------------------------------------- */
#define TIME_OUT_TRANSMIT_UART (1000)

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */
#ifdef DEBUG
#define __ASSERT(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)
#else
#define __ASSERT(_EXPR_, _RET_VAL_) ((void)0)
#endif

#define __RETURN(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)

/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_uart_status_t bsp_uart_init(UART_HandleTypeDef *uart, UART_InitTypeDef *uart_init)
{
  __ASSERT((uart != NULL), BSP_UART_ERROR);
  __ASSERT((uart_init != NULL), BSP_UART_ERROR);

  uart->Init.BaudRate = uart_init->BaudRate;
  uart->Init.WordLength = uart_init->WordLength;
  uart->Init.StopBits = uart_init->StopBits;
  uart->Init.Parity = uart_init->Parity;
  uart->Init.Mode = uart_init->Mode;
  uart->Init.HwFlowCtl = uart_init->HwFlowCtl;
  uart->Init.OverSampling = uart_init->OverSampling;

  if (HAL_UART_Init(uart) != HAL_OK)
  {
    return BSP_UART_ERROR;
  }

  return BSP_UART_OK;
}

bsp_uart_status_t bsp_uart_start_read_to_idle_it(UART_HandleTypeDef *uart,
                                                 uint8_t *rx_data, uint32_t bytes)
{
  __ASSERT((uart != NULL), BSP_UART_ERROR);
  __ASSERT((rx_data != NULL), BSP_UART_ERROR);

  bsp_uart_status_t error_status = BSP_UART_OK;
  error_status = (bsp_uart_status_t)HAL_UARTEx_ReceiveToIdle_IT(uart, rx_data, bytes);
  __RETURN((error_status == BSP_UART_OK), error_status);

  return BSP_UART_OK;
}

bsp_uart_status_t bsp_uart_stop_read_to_idle_it(UART_HandleTypeDef *uart)
{
  __ASSERT((uart != NULL), BSP_UART_ERROR);

  bsp_uart_status_t error_status = BSP_UART_OK;
  error_status = (bsp_uart_status_t)HAL_UART_AbortReceive_IT(uart);
  __RETURN((error_status == BSP_UART_OK), error_status);

  return BSP_UART_OK;
}

bsp_uart_status_t bsp_uart_print(UART_HandleTypeDef *uart,
                                 uint8_t *tx_data)
{
  __ASSERT((uart != NULL), BSP_UART_ERROR);
  __ASSERT((tx_data != NULL), BSP_UART_ERROR);

  bsp_uart_status_t error_status = BSP_UART_OK;
  error_status = (bsp_uart_status_t)HAL_UART_Transmit(uart, tx_data, strlen((char *)tx_data),
                                                      TIME_OUT_TRANSMIT_UART);
  __RETURN((error_status == BSP_UART_OK), error_status);

  return BSP_UART_OK;
}

bsp_uart_status_t bsp_uart_print_length(UART_HandleTypeDef *uart,
                                        uint8_t *tx_data, uint32_t data_len)
{
  __ASSERT((uart != NULL), BSP_UART_ERROR);
  __ASSERT((tx_data != NULL), BSP_UART_ERROR);

  bsp_uart_status_t error_status = BSP_UART_OK;
  error_status = (bsp_uart_status_t)HAL_UART_Transmit(uart, tx_data, data_len,
                                                      TIME_OUT_TRANSMIT_UART);
  __RETURN((error_status == BSP_UART_OK), error_status);

  return BSP_UART_OK;
}

/* Private function definitions --------------------------------------- */
/* End of file -------------------------------------------------------- */


