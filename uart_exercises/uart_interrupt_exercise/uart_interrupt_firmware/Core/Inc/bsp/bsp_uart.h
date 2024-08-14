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
#include <string.h>

/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BSP_UART_OK = 0U,
  BSP_UART_ERROR,
  BSP_UART_BUSY,
  BSP_UART_TIMEOUT,
} bsp_uart_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Init uart.
 *
 * @param[in]   uart        Pointer to the UART handle structure.
 * @param[in]   uart_init   Pointer to the UART init structure.
 *
 * @return      The status of the UART init operation.
 */
bsp_uart_status_t bsp_uart_init(UART_HandleTypeDef *uart, UART_InitTypeDef *uart_init);

/**
 * @brief       Start read data from UART using interrupt until an idle line is detected.
 *
 * @param[in]   uart        Pointer to the UART handle structure.
 * @param[out]  rx_data     Pointer to the buffer to store received data.
 * @param[in]   bytes       Number of bytes to read until an idle line is detected.
 *
 * @return      The status of the UART read operation.
 */
bsp_uart_status_t bsp_uart_start_read_to_idle_it(UART_HandleTypeDef *uart,
                                                 uint8_t *rx_data, uint32_t bytes);

/**
 * @brief       Stop read data from UART using interrupt until an idle line is detected.
 *
 * @param[in]   uart        Pointer to the UART handle structure.
 * @param[out]  rx_data     Pointer to the buffer to store received data.
 * @param[in]   bytes       Number of bytes to read until an idle line is detected.
 *
 * @return      The status of the UART read operation.
 */
bsp_uart_status_t bsp_uart_stop_read_to_idle_it(UART_HandleTypeDef *uart);

/**
 * @brief       Print data over UART.
 *
 * @param[in]   uart        Pointer to the UART handle structure.
 * @param[in]   tx_data     Pointer to the data to be transmitted.
 *
 * @return      The status of the UART transmission operation.
 */
bsp_uart_status_t bsp_uart_print(UART_HandleTypeDef *uart, uint8_t *tx_data);

/**
 * @brief       Print data of specified length over UART.
 *
 * @param[in]   uart        Pointer to the UART handle structure.
 * @param[in]   tx_data     Pointer to the data to be transmitted.
 * @param[in]   data_len    Length of the data to be transmitted.
 *
 * @return      The status of the UART transmission operation.
 */
bsp_uart_status_t bsp_uart_print_length(UART_HandleTypeDef *uart,
                                        uint8_t *tx_data, uint32_t data_len);

#endif /* INC_BSP_BSP_UART_H_ */
/* End of file -------------------------------------------------------- */
