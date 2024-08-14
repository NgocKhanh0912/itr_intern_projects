/**
 * @file       sys_manage.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs of the system
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "system/sys_manage.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */
#define __RETURN(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_fsm_state_t sys_current_state = SYS_STATE_IDLE;

/* Private function prototypes ---------------------------------------- */
/**
 * @brief       Check if sys_rx_buffer has a full command.
 *
 * @param[in]   sys_rx_buffer             Pointer to the buffer which store all received data.
 * @param[in]   sys_rx_buffer_index       Pointer to the index of sys_rx_buffer.
 *
 * @return      true/false.
 */
static bool sys_check_received_a_full_command(uint8_t *sys_rx_buffer,
                                              uint8_t *sys_rx_buffer_index);

/**
 * @brief       Check if sys_rx_buffer has a part of a full command.
 *
 * @param[in]   sys_rx_buffer             Pointer to the buffer which store all received data.
 * @param[in]   sys_rx_buffer_index       Pointer to the index of sys_rx_buffer.
 *
 * @return      true/false.
 */
static bool sys_check_not_received_a_full_command(uint8_t *sys_rx_buffer,
                                                  uint8_t *sys_rx_buffer_index);


/* Function definitions ----------------------------------------------- */
sys_status_t sys_init(UART_HandleTypeDef *sys_uart,
                      UART_InitTypeDef *sys_uart_init,
                      uint8_t *sys_rx_buffer,
                      uint8_t *sys_rx_buffer_index)
{
  sys_status_t error_status = SYS_STATUS_OK;

  error_status = (sys_status_t)bsp_uart_init(sys_uart, sys_uart_init);
  __RETURN((error_status == SYS_STATUS_OK), error_status);

  error_status = (sys_status_t)bsp_uart_start_read_to_idle_it(sys_uart, sys_rx_buffer, RX_BUFFER_SIZE);
  __RETURN((error_status == SYS_STATUS_OK), error_status);

  uint8_t adv_msg[] = "System initialize finished successfully!\r\n";
  bsp_uart_print(sys_uart, adv_msg);

  return SYS_STATUS_OK;
}

sys_status_t sys_manage_fsm(UART_HandleTypeDef *sys_uart,
                            uint8_t *sys_tx_buffer,
                            uint8_t *sys_rx_buffer,
                            uint8_t *sys_rx_buffer_index,
                            uint16_t *size,
                            uint8_t *sys_manage_handled_flag)
{
  switch (sys_current_state)
  {
    case (SYS_STATE_IDLE):
      if (*sys_rx_buffer_index == 0)
        {
          sys_current_state = SYS_STATE_IDLE;
        }
      else if (sys_check_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_RECEIVED_A_FULL_COMMAND;
        }
      else if (sys_check_not_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND;
        }
      else
        {
          sys_current_state = SYS_STATE_RECEIVED_WRONG_DATA;
        }
      break;

    case (SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND):
      if (sys_check_not_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND;
        }
      else if (sys_check_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_RECEIVED_A_FULL_COMMAND;
        }

      else
        {
          sys_current_state = SYS_STATE_RECEIVED_WRONG_DATA;
        }
      break;

    case (SYS_STATE_RECEIVED_A_FULL_COMMAND):
      if (*sys_rx_buffer_index == 0)
        {
          sys_current_state = SYS_STATE_IDLE;
        }
      else if (sys_check_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_RECEIVED_A_FULL_COMMAND;
        }
      else if (sys_check_not_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND;
        }
      else
        {
          sys_current_state = SYS_STATE_RECEIVED_WRONG_DATA;
        }
      break;

    case (SYS_STATE_RECEIVED_WRONG_DATA):
      if (*sys_rx_buffer_index == 0)
        {
          sys_current_state = SYS_STATE_IDLE;
        }
      else if (sys_check_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_RECEIVED_A_FULL_COMMAND;
        }
      else if (sys_check_not_received_a_full_command(sys_rx_buffer, sys_rx_buffer_index) == true)
        {
          sys_current_state = SYS_STATE_NOT_RECEIVED_A_FULL_COMMAND;
        }
      else
        {
          sys_current_state = SYS_STATE_RECEIVED_WRONG_DATA;
        }
      break;
  }

  switch (sys_current_state)
  {
    case (SYS_STATE_RECEIVED_A_FULL_COMMAND):
      memcpy(sys_tx_buffer, sys_rx_buffer, COMMAND_SIZE);
      memmove(sys_rx_buffer, sys_rx_buffer + COMMAND_SIZE, RX_BUFFER_SIZE - 4);
      *sys_rx_buffer_index -= 4;
      bsp_uart_print_length(sys_uart, sys_tx_buffer, COMMAND_SIZE);
      break;

    case (SYS_STATE_RECEIVED_WRONG_DATA):
      memmove(sys_rx_buffer, sys_rx_buffer + 1, RX_BUFFER_SIZE - 1);
      *sys_rx_buffer_index -= 1;
      break;

    default:
      *sys_manage_handled_flag = 1;
      break;
  }

  return SYS_STATUS_OK;
}

void sys_uart_rx_event_callback(uint8_t size,
                                uint8_t *sys_rx_buffer_index)
{
  *sys_rx_buffer_index += size;
}

/* Private function definitions --------------------------------------- */
static bool sys_check_received_a_full_command(uint8_t *sys_rx_buffer,
                                              uint8_t *sys_rx_buffer_index)
{
  if (*sys_rx_buffer_index >= 4)
    {
      if ((sys_rx_buffer[0] == 'C') &&
          (sys_rx_buffer[1] == 'M') &&
          (sys_rx_buffer[2] == 'D') &&
          (sys_rx_buffer[3] >= '0') &&
          (sys_rx_buffer[3] <= '9'))
        {
          return true;
        }
    }
  return false;
}

static bool sys_check_not_received_a_full_command(uint8_t *sys_rx_buffer,
                                                  uint8_t *sys_rx_buffer_index)
{
  switch (*sys_rx_buffer_index)
  {
    // Received 1 char correct
    case (1):
      if (sys_rx_buffer[0] == 'C')
        {
          return true;
        }
      break;

    // Received 2 chars correct
    case (2):
      if ((sys_rx_buffer[0] == 'C') &&
          (sys_rx_buffer[1] == 'M'))
        {
          return true;
        }
      break;

    // Received 3 chars correct
    case (3):
      if ((sys_rx_buffer[0] == 'C') &&
          (sys_rx_buffer[1] == 'M') &&
          (sys_rx_buffer[2] == 'D'))
        {
          return true;
        }
      break;

    // Wrong data
    default:
      return false;
      break;
  }

  return false;
}

/* End of file -------------------------------------------------------- */
