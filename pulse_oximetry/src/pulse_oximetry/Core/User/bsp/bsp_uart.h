/**
 * @file       bsp_uart.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_BSP_BSP_UART_H_
#define INC_BSP_BSP_UART_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"

/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */

/* Public enumerate/structure ----------------------------------------- */
enum bsp_uart_status_t
{
  BSP_UART_ERROR = 0xFFFFFFFF,
  BSP_UART_FAIL = 0x7FFFFFFF,
  BSP_UART_OK = 0x3FFFFFFF
};

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
typedef void (*bsp_uart_cb_t)(UART_HandleTypeDef *huart, uint16_t size);
/* Public function prototypes ----------------------------------------- */

/**
 * @brief       Start to receive data from UART using interrupt until an idle line is detected.
 *
 * @param[in]   huart       Pointer to the UART handle structure.
 * @param[out]  rx_data     Pointer to the buffer to store received data.
 * @param[in]   bytes       Number of bytes to read until an idle line is detected.
 *
 * @return      The status of the UART read operation.
 */
uint32_t bsp_uart_start_receive_to_idle_it(UART_HandleTypeDef *huart,
                                           uint8_t *rx_data, uint16_t bytes);

/**
 * @brief       Start to receive data from UART using DMA until an events below is trigger:
 *              - DMA transmit half complete
 *              - DMA transmit complete
 *              - UART idle
 *
 * @param[in]   huart       Pointer to the UART handle structure.
 * @param[out]  rx_data     Pointer to the buffer to store received data.
 * @param[in]   bytes       Number of bytes to read until an idle line is detected.
 *
 * @return      The status of the UART read operation.
 */
uint32_t bsp_uart_start_receive_to_idle_dma(UART_HandleTypeDef *huart,
                                            uint8_t *rx_data, uint16_t bytes);

/**
 * @brief       Print data of specified length over UART.
 *
 * @param[in]   huart       Pointer to the UART handle structure.
 * @param[in]   tx_data     Pointer to the data to be transmitted.
 * @param[in]   data_len    Length of the data to be transmitted.
 *
 * @return      The status of the UART transmission operation.
 */
uint32_t bsp_uart_transmit(UART_HandleTypeDef *huart,
                           uint8_t *tx_data, uint16_t data_len);

/**
 * @brief       Register the callback function for UART event.
 *
 * @param[in]   rx_evt_cb       Function pointer to the UART receive event.
 *
 * @return      The status of the UART transmission operation.
 */
uint32_t bsp_uart_register_cb_function(bsp_uart_cb_t rx_evt_cb);

/**
 * @brief       Handle the callback function for UART event.
 *
 * @param[in]   uart       Pointer to the UART handle structure.
 * @param[in]   size       Number of bytes to read until an idle line is detected.
 *
 * @return      The status of the UART transmission operation.
 */
uint32_t bsp_uart_rx_cb_handler(UART_HandleTypeDef *uart, uint16_t size);
#endif /* INC_BSP_BSP_UART_H_ */

/* End of file -------------------------------------------------------- */