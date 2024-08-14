/**
 * @file       sys_manage.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       13/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs of the system
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_SYSTEM_SYS_MANAGE_H_
#define INC_SYSTEM_SYS_MANAGE_H_

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp_uart.h"
#include <stdbool.h>
#include <string.h>

/* Public defines ----------------------------------------------------- */
#define RX_BUFFER_SIZE 50
#define COMMAND_SIZE 4

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_STATE_IDLE = 0U,
  SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND, // State that sys_rx_buffer has a part of a full command
  SYS_STATE_RECEIVED_A_FULL_COMMAND,
  SYS_STATE_RECEIVED_WRONG_DATA,
} sys_fsm_state_t;

typedef enum
{
  SYS_STATUS_OK = 0,
  SYS_STATUS_ERROR,
} sys_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       System init: init uart,
 *              enable uart interrupt received to idle
 *              and send init success message.
 *
 * @param[in]   sys_uart              Pointer to the UART handle structure.
 * @param[in]   sys_uart_init         Pointer to the UART init structure.
 * @param[in]   sys_rx_buffer_index   Pointer to the index of sys_rx_buffer.
 * @param[in]   sys_rx_buffer         Pointer to the buffer which store all received data.
 *
 * @return      The status of the system init operation.
 */
sys_status_t sys_init(UART_HandleTypeDef *sys_uart,
                      UART_InitTypeDef *sys_uart_init,
                      uint8_t *sys_rx_buffer,
                      uint8_t *sys_rx_buffer_index);

/**
 * @brief       Manage system fsm, process raw data in sys_rx_buffer,
 *              store a full command in sys_tx_buffer,
 *              transmit a command in sys_tx_buffer out to user.
 *
 * @param[in]   sys_uart                  Pointer to the UART handle structure.
 * @param[in]   sys_rx_buffer             Pointer to the buffer which store all received data.
 * @param[in]   sys_rx_buffer_index       Pointer to the index of sys_rx_buffer.
 * @param[in]   size                      Pointer to the data that uart received to idle.
 * @param[in]   sys_manage_handled_flag   Pointer to the system manage finished handle flag.
 * @param[out]  sys_tx_buffer             Pointer to the buffer which store a command transmittted to user.
 *
 * @return      The status of the system manage operation.
 */
sys_status_t sys_manage_fsm(UART_HandleTypeDef *sys_uart,
                            uint8_t *sys_tx_buffer,
                            uint8_t *sys_rx_buffer,
                            uint8_t *sys_rx_buffer_index,
                            uint16_t *size,
                            uint8_t *sys_manage_handled_flag);

/**
 * @brief       Callback event when UART receive to idle
 *
 * @param[in]   size                    Size of data that UART received to idle.
 * @param[in]   sys_rx_buffer_index     Pointer to the index of sys_rx_buffer.
 *
 * @return      None.
 */
void sys_uart_rx_event_callback(uint8_t size,
                                uint8_t *sys_rx_buffer_index);

#endif /* INC_SYSTEM_SYS_MANAGE_H_ */
/* End of file -------------------------------------------------------- */
