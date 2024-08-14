/**
 * @file       sys_manage.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-08-06
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Service manage all tasks of system
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_MANAGE_H
#define __USER_SYS_MANAGE_H

/* Includes ----------------------------------------------------------- */
#include "sys_button.h"
#include "sys_display.h"
#include "sys_time.h"
#include "sys_measure.h"
#include "sys_protocol.h"
#include "sys_storage.h"
#include "drv_buzzer.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

enum sys_manage_status_t
{
  SYS_MANAGE_ERROR = 0xFFFFFFFF,
  SYS_MANAGE_FAILED = 0x7FFFFFFF,
  SYS_MANAGE_OK = 0x3FFFFFFF
};

typedef enum
{
  SYS_MANAGE_CMD_CHECK_UART = 0x00,
  SYS_MANAGE_CMD_GET_RECORDS = 0x01,
  SYS_MANAGE_CMD_GET_RAW_PPG = 0x11,
  SYS_MANAGE_CMD_GET_FILTERED_PPG = 0x21,
  SYS_MANAGE_CMD_SET_THRESHOLD = 0x02,
  SYS_MANAGE_CMD_SET_INTERVAL = 0x03,
  SYS_MANAGE_CMD_TIME = 0x04,
  SYS_MANAGE_CMD_CLEAR_RECORDS = 0x05
} sys_manage_cmd_t;

typedef enum
{
  SYS_MANAGE_STREAM_OLED = 0,
  SYS_MANAGE_STREAM_GUI
} sys_manage_stream_select_t;

typedef enum
{
  SYS_MAMAGE_STATE_SLEEP = 0,
  SYS_MANAGE_WAIT_WAKEUP,
  SYS_MANAGE_STATE_IDLE,
  SYS_MANAGE_STATE_NORMAL,
  SYS_MANAGE_STATE_HEART_RATE_WARNING,
  SYS_MANAGE_STATE_CHECK_UART,
  SYS_MANAGE_STATE_SET_THRESHOLD,
  SYS_MANAGE_STATE_SET_INTERVAL,
  SYS_MAMAGE_STATE_SET_TIME,
  SYS_MANAGE_STATE_RECORD,
  SYS_MANAGE_STATE_SEND_RECORDS,
  SYS_MAMAGE_STATE_CLEAR_RECORDS,
  SYS_MANAGE_STATE_ERROR

} sys_manage_state_t;

typedef struct
{
  sys_manage_state_t current_state;
  bool active;
  uint8_t cmd;
  sys_manage_stream_select_t stream;
  uint32_t interval;
  uint8_t lower_threshold;
  uint8_t upper_threshold;
} sys_manage_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief  Start the service control display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 * @param[in]     i2c      pointer to I2C handler
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0X7FFFFFFF: Failed
 *  - 0X3FFFFFFF: Success
 */
uint32_t sys_manage_start_display(bsp_i2c_handle_t *i2c, uint8_t *dev_buffer);

/**
 * @brief  Start the service to collect and process signal
 *
 * @param[in]     adc           Channel attaches to sensor
 * @param[in]     tim           Timer to trigger ADC Conversion
 * @param[in]     prescaler     Prescale the clock timer source
 * @param[in]     autoreload    Set the top of counter
 * @param[in]     data_buf      Pointer to buffer that store processed data.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_manage_start_measure(bsp_adc_typedef_t *adc,
                                  bsp_tim_typedef_t *tim,
                                  uint32_t prescaler,
                                  uint32_t autoreload,
                                  double *data_buf);

/**
 * @brief       Start the serivce handle the user button
 *
 * @param[in]   gpio  Pointer point to GPIO port
 * @param[in]   pin   pin of that port
 * @param[in]   button_active_level Determine the active high or active low button
 *
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_manage_start_button(GPIO_TypeDef *gpio, uint16_t pin, uint32_t button_active_level);

/**
 * @brief                 Start service to manage the UART protocol
 *
 * @param[in]     uart    Hardware UART handler
 *
 * @return
 * -  (0xFFFFFFFF)  : Error
 * -  (0x7FFFFFFF)  : Failed
 * -  (0x3FFFFFFF)  : Success
 */
uint32_t sys_manage_start_protocol(UART_HandleTypeDef *uart);

/**
 * @brief       Initialize the buzzer.
 *
 * @param[in]   buzzer         Pointer to buzzer handler.
 * @param[in]   tim            Pointer of timer buzzer handler.
 * @param[in]   pwm_channel    Channel PWM connect to buzzer.
 *
 * @attention   the valid buzzer period and duty cycle.
 * @note        Module buzzer low level trigger.
 *
 * @return
 * -  0xFFFFFFFF: Error
 * -  0x7FFFFFFF: Failed
 * -  0x3FFFFFFF: Success
 */
uint32_t sys_manage_start_buzzer(bsp_tim_typedef_t *tim, uint32_t pwm_channel);

/**
 * @brief       Initialize service for managing RTC DS1307.
 *
 * @param[in]   i2c       Pointer to the I2C handle structure in sys_time.
 *
 * @attention   Only one RTC DS1307 is allowed to run at a time.
 *              If you initialize another DS1307,
 *              it means you have deinitialized the previous DS1307.
 *
 * @return
 * -  0xFFFFFFFF: Error
 * -  0x7FFFFFFF: Failed
 * -  0x3FFFFFFF: Success
 */
uint32_t sys_manage_start_rtc(bsp_i2c_handle_t *i2c);

/**
 * @brief       Initialize service for stroing heart rate
 *
 * @return
 * -  0xFFFFFFFF: Error
 * -  0x7FFFFFFF: Failed
 * -  0x3FFFFFFF: Success
 */
uint32_t sys_manage_start_storage();

/**
 * @brief       Initialize service for managing RTC DS1307.
 *
 * @param[in]   i2c       Pointer to the I2C handle structure in sys_time.
 * @param[in]   tim       Pointer of timer handler event sending heart rate per period.
 *
 * @attention   Only one RTC DS1307 is allowed to run at a time.
 *              If you initialize another DS1307,
 *              it means you have deinitialized the previous DS1307.
 *
 * @return
 * -  0xFFFFFFFF: Error
 * -  0x7FFFFFFF: Failed
 * -  0x3FFFFFFF: Success
 */
uint32_t sys_manage_start(bsp_tim_typedef_t *tim);
/**
 * @brief       Manage all services in system.
 *
 * @attention   Services need to be started before use this function.
 *
 * @return
 * -  0xFFFFFFFF: Error
 * -  0x7FFFFFFF: Failed
 * -  0x3FFFFFFF: Success
 */
uint32_t sys_manage_loop();
#endif // __USER_SYS_MANAGE_H

/* End of file -------------------------------------------------------- */
