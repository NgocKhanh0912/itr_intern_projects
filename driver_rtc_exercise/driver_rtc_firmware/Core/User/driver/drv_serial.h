/**
 * @file       drv_serial.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_DRV_SERIAL_H
#define __USER_DRV_SERIAL_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
#include "bsp_uart.h"
/* Public enumerate/structure ----------------------------------------- */
enum drv_serial_status_t
{
  DRV_SERIAL_ERROR = -2,
  DRV_SERIAL_FAILED,
  DRV_SERIAL_OK
};

typedef struct __attribute((__packed__))
{
  UART_HandleTypeDef *uart;
  uint8_t *dma_buf;
  uint8_t *reception_buf;
  uint8_t *handle_buf;
  uint8_t size;
  uint8_t reader;
  uint8_t received_bytes;
} drv_serial_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */
typedef void (*drv_evt_cb_t)(uint16_t);

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize the serial comunication driver
 *
 * @param[in]     uart      Hardware UART handler
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
uint32_t drv_serial_init(UART_HandleTypeDef *uart);

/**
 * @brief         Transmit data viaserial comunication
 *
 * @param[in]     tx_buf    Buffer store data that will be transmitted
 * @param[in]     tx_size   Size of transmitter buffer
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
uint32_t drv_serial_transmit(uint8_t *tx_buf, uint16_t tx_size);

/**
 * @brief         Transmit data viaserial comunication
 *
 * @param[in]     rx_buf    Buffer store data that will be received
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
uint32_t drv_serial_receive(uint8_t *rx_buf);

/**
 * @brief         Transmit data viaserial comunication
 *
 * @param[in]     rx_buf    Buffer store data that will be received
 *
 * @return
 *  - (-2): Error
 *  - (-1): Fail
 *  - (0) : Success
 */
uint32_t drv_serial_register_cb_function(drv_evt_cb_t new_rx_data_cb);

#endif // __USER_DRV_SERIAL_H

/* End of file -------------------------------------------------------- */
