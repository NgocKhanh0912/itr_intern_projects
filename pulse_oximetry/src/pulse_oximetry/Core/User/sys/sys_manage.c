/**
 * @file       sys_manage.c
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

/* Includes ----------------------------------------------------------- */
#include "sys_manage.h"
#include "bsp_utils.h"
#include "list_of_sound_effects.h"
#include "common.h"
/* Private defines ---------------------------------------------------- */
#define SYS_MANAGE_TIMESTAMP (96000000U)

#define SYS_MANAGE_SEGMENT_HEART_RATE_RECORDS_SIZE (4096U)

#define SYS_MANAGE_FILTERED_DATA_OFFSET_PKT (1000.0)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_measure_t s_ppg_signal;
static sys_display_t s_oled_screen;
static drv_buzzer_t s_passive_buzzer;
static drv_ds1307_t s_rtc;
static bsp_tim_typedef_t *s_tim_interval;

static sys_storage_t s_heart_rate_records;

static cbuffer_t s_rx_pkt_cbuf;
static uint8_t s_rx_pkt_buf[100] = {0};

static sys_manage_t s_mng;
static sys_protocol_pkt_t s_check_pkt;
static const uint8_t s_success_noti[] = "Success!";
/* Private function prototypes ---------------------------------------- */

/**
 * @brief       Control the ON/OFF state of the system service.
 *
 * @return
 * -  None
 */
static void sys_manage_pwr_ctrl();

/**
 * @brief       Record the current heart rate.
 *
 * @return
 * -  None
 */
static void sys_manage_record_heart_rate();

/**
 * @brief       Switch display signal on OLED or stream on GUI application.
 *
 * @return
 * -  None
 */
static void sys_manage_select_stream();

/**
 * @brief       Trigger the recording heart rate event
 * .
 *
 * @return
 * -  None
 */
static void sys_manage_interval_elapsed(bsp_tim_typedef_t *tim);
/* Function definitions ----------------------------------------------- */
uint32_t sys_manage_start_display(bsp_i2c_handle_t *i2c, uint8_t *dev_buffer)
{
  uint32_t ret = SYS_DISPLAY_OK;
  ret = sys_display_init(&s_oled_screen, i2c, dev_buffer);
  __ASSERT(ret == SYS_DISPLAY_OK, SYS_MANAGE_ERROR);
  ret = sys_display_show_noti(&s_oled_screen, s_success_noti);
  __ASSERT(ret == SYS_DISPLAY_OK, SYS_MANAGE_ERROR);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_measure(bsp_adc_typedef_t *adc,
                                  bsp_tim_typedef_t *tim,
                                  uint32_t prescaler,
                                  uint32_t autoreload,
                                  double *data_buf)
{
  uint32_t ret = SYS_MEASURE_OK;
  ret = sys_measure_init(&s_ppg_signal, adc, tim, prescaler, autoreload, data_buf);
  __ASSERT(ret == SYS_MEASURE_OK, SYS_MANAGE_FAILED);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_button(GPIO_TypeDef *gpio, uint16_t pin, uint32_t button_active_level)
{
  uint32_t ret = SYS_BUTTON_OK;
  ret = sys_button_init(gpio, pin, button_active_level);
  __ASSERT(ret == SYS_BUTTON_OK, SYS_MANAGE_ERROR);
  ret = sys_button_register_cb_function(sys_manage_record_heart_rate,
                                        sys_manage_select_stream,
                                        sys_manage_pwr_ctrl);
  __ASSERT(ret == SYS_BUTTON_OK, SYS_MANAGE_ERROR);
  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_protocol(UART_HandleTypeDef *uart)
{
  uint32_t ret = SYS_PROTOCOL_OK;
  ret = sys_protocol_init(uart);
  __ASSERT(ret == SYS_PROTOCOL_OK, SYS_MANAGE_ERROR);

  cb_init(&s_rx_pkt_cbuf, s_rx_pkt_buf, sizeof(s_rx_pkt_buf));
  ret = sys_protocol_register_node_to_send(SYS_PROTOCOL_SYS_MNG, &s_rx_pkt_cbuf);
  __ASSERT(ret == SYS_PROTOCOL_OK, SYS_MANAGE_ERROR);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_rtc(bsp_i2c_handle_t *i2c)
{
  uint32_t ret = SYS_TIME_OK;
  ret = sys_time_init(i2c, &s_rtc);
  __ASSERT(ret == SYS_TIME_OK, SYS_MANAGE_ERROR);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_buzzer(bsp_tim_typedef_t *tim, uint32_t pwm_channel)
{
  uint32_t ret = DRV_BUZZER_OK;
  ret = drv_buzzer_init(&s_passive_buzzer, tim, pwm_channel);
  __ASSERT(ret == DRV_BUTTON_OK, SYS_MANAGE_ERROR);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start_storage()
{
  uint32_t ret = SYS_STORAGE_OK;
  ret = sys_storage_init(&s_heart_rate_records, BSP_FLASH_SECTOR_7_ADDRESS, SYS_MANAGE_SEGMENT_HEART_RATE_RECORDS_SIZE);
  __ASSERT(ret == SYS_STORAGE_OK, SYS_MANAGE_FAILED);

  return SYS_MANAGE_OK;
}

uint32_t sys_manage_start(bsp_tim_typedef_t *tim)
{
  s_mng.current_state = SYS_MANAGE_STATE_IDLE;
  s_mng.cmd = 0xFF;
  s_mng.interval = 0;
  s_mng.lower_threshold = 60;
  s_mng.upper_threshold = 140;
  s_mng.active = true;
  s_mng.stream = SYS_MANAGE_STREAM_OLED;
  uint8_t threshold[] = {s_mng.lower_threshold, s_mng.upper_threshold};
  sys_display_update_threshold(&s_oled_screen, threshold);

  s_check_pkt.command = 0x00;
  s_check_pkt.data = 0xFFFFFFFF;
  s_check_pkt.threshold_level = 0xFF;

  uint8_t start_msg[] = "Init OK";
  sys_display_show_noti(&s_oled_screen, start_msg);
  s_tim_interval = tim;
  bsp_timer_set_autoreload(s_tim_interval, SYS_MANAGE_TIMESTAMP);
  bsp_timer_set_prescaler(s_tim_interval, 0);
  bsp_timer_register_callback(sys_manage_interval_elapsed);
}

uint32_t sys_manage_loop()
{
  sys_button_manage();

  if (s_mng.stream == SYS_MANAGE_STREAM_GUI)
  {
    if (cb_data_count(&s_ppg_signal.dev.adc_conv) > 0)
    {
      cbuffer_t raw_data_cbuf = s_ppg_signal.dev.adc_conv;

      while (cb_data_count(&raw_data_cbuf) > 0)
      {
        uint16_t adc_val = 0;
        cb_read(&raw_data_cbuf, &adc_val, sizeof(adc_val));
        sys_protocol_pkt_t raw_data_pkt = {SYS_MANAGE_CMD_GET_RAW_PPG, (uint32_t)adc_val, 0xFF};
        sys_protocol_send_pkt_to_port(raw_data_pkt);
      }
    }
  }
  sys_measure_process_data(&s_ppg_signal);

  if (bsp_utils_get_tick() > 5000)
  {
    if (s_mng.stream == SYS_MANAGE_STREAM_OLED)
    {
      sys_display_update_ppg_signal(&s_oled_screen, &(s_ppg_signal.filtered_data));
    }
  }

  if (s_mng.stream == SYS_MANAGE_STREAM_GUI)
  {
    while (cb_data_count(&s_ppg_signal.filtered_data) > 0)
    {
      double temp = 0;
      cb_read(&s_ppg_signal.filtered_data, &temp, sizeof(temp));
      temp += SYS_MANAGE_FILTERED_DATA_OFFSET_PKT;
      sys_protocol_pkt_t filtered_data_pkt = {SYS_MANAGE_CMD_GET_FILTERED_PPG, (uint32_t)temp, 0xFF};
      sys_protocol_send_pkt_to_port(filtered_data_pkt);
    }
  }

  sys_display_update_heart_rate(&s_oled_screen, s_ppg_signal.heart_rate);

  if (cb_data_count(&s_rx_pkt_cbuf) > 0)
  {
    cb_read(&s_rx_pkt_cbuf, &s_mng.cmd, CMD_PKT_SIZE);

    switch (s_mng.cmd)
    {
    case SYS_MANAGE_CMD_CHECK_UART:
    {
      cb_clear(&s_rx_pkt_cbuf);
      s_mng.current_state = SYS_MANAGE_STATE_CHECK_UART;
      break;
    }
    case SYS_MANAGE_CMD_GET_RECORDS:
    {
      // Check UART
      sys_protocol_send_pkt_to_port(s_check_pkt);
      cb_clear(&s_rx_pkt_cbuf);
      s_mng.current_state = SYS_MANAGE_STATE_SEND_RECORDS;
      break;
    }
    case SYS_MANAGE_CMD_SET_THRESHOLD:
    {
      // Check UART
      sys_protocol_send_pkt_to_port(s_check_pkt);
      s_mng.current_state = SYS_MANAGE_STATE_SET_THRESHOLD;
      break;
    }
    case SYS_MANAGE_CMD_SET_INTERVAL:
    {
      // Check UART
      sys_protocol_send_pkt_to_port(s_check_pkt);
      s_mng.current_state = SYS_MANAGE_STATE_SET_INTERVAL;
      break;
    }
    case SYS_MANAGE_CMD_TIME:
    {
      // Check UART
      sys_protocol_send_pkt_to_port(s_check_pkt);
      s_mng.current_state = SYS_MAMAGE_STATE_SET_TIME;
      break;
    }
    case SYS_MANAGE_CMD_CLEAR_RECORDS:
    {
      // Check UART
      sys_protocol_send_pkt_to_port(s_check_pkt);
      s_mng.current_state = SYS_MAMAGE_STATE_CLEAR_RECORDS;
      break;
    }
    default:
      break;
    }
  }

  switch (s_mng.current_state)
  {
  case SYS_MAMAGE_STATE_SLEEP:
  {
    drv_hr_sleep(&(s_ppg_signal.dev));
    sys_display_sleep(&s_oled_screen);
    s_mng.current_state = SYS_MANAGE_WAIT_WAKEUP;
    break;
  }
  case SYS_MANAGE_WAIT_WAKEUP:
  {
    break;
  }
  case SYS_MANAGE_STATE_IDLE:
  {
    drv_hr_wakeup(&(s_ppg_signal.dev));
    sys_display_wakeup(&s_oled_screen);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MANAGE_STATE_NORMAL:
  {
    if ((s_ppg_signal.heart_rate < s_mng.lower_threshold) || (s_ppg_signal.heart_rate > s_mng.upper_threshold))
    {
      s_mng.current_state = SYS_MANAGE_STATE_HEART_RATE_WARNING;
    }
    uint8_t msg[] = "          ";
    sys_display_show_noti(&s_oled_screen, msg);
    break;
  }

  case SYS_MANAGE_STATE_HEART_RATE_WARNING:
  {
    uint8_t msg[] = "Warning";
    if ((s_ppg_signal.heart_rate > s_mng.lower_threshold) && (s_ppg_signal.heart_rate < s_mng.upper_threshold))
    {
      s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    }
    break;
  }

  case SYS_MANAGE_STATE_CHECK_UART:
  {
    sys_protocol_send_pkt_to_port(s_check_pkt);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MANAGE_STATE_SET_THRESHOLD:
  {
    // Get threshold from packet
    uint32_t temp_data = 0;
    cb_read(&s_rx_pkt_cbuf, &temp_data, DATA_PKT_SIZE);
    // Set threshold
    s_mng.lower_threshold = temp_data & (0x000000FF);
    s_mng.upper_threshold = (temp_data >> 8) & (0x000000FF);
    uint8_t threshold[] = {s_mng.lower_threshold, s_mng.upper_threshold};
    sys_display_update_threshold(&s_oled_screen, threshold);
    // Notification
    cb_clear(&s_rx_pkt_cbuf);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MANAGE_STATE_SET_INTERVAL:
  {
    uint32_t temp_prescaler;
    cb_read(&s_rx_pkt_cbuf, &temp_prescaler, DATA_PKT_SIZE);
    bsp_timer_set_prescaler(s_tim_interval, temp_prescaler - 1);
    bsp_timer_start_it(s_tim_interval);
    cb_clear(&s_rx_pkt_cbuf);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MAMAGE_STATE_SET_TIME:
  {
    uint8_t msg[] = "Setting";
    sys_display_show_noti(&s_oled_screen, msg);
    // Get epoch time from packet
    uint32_t temp_ept = 0;
    uint32_t ret = SYS_TIME_OK;
    cb_read(&s_rx_pkt_cbuf, &temp_ept, DATA_PKT_SIZE);
    // Set time for system RTC
    ret = sys_time_set_epoch_time(temp_ept, &s_rtc);
    __ASSERT(ret = SYS_TIME_OK, SYS_MANAGE_ERROR);
    // Notification
    cb_clear(&s_rx_pkt_cbuf);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MANAGE_STATE_RECORD:
  {
    uint8_t msg[] = "Recording";
    sys_display_show_noti(&s_oled_screen, msg);
    uint32_t record_time = sys_time_get_epoch_time(&s_rtc);
    sys_storage_import(&s_heart_rate_records, &record_time, 4);
    sys_storage_import(&s_heart_rate_records, &(s_ppg_signal.heart_rate), 1);
    sprintf(msg, "          ");
    sys_display_show_noti(&s_oled_screen, msg);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MANAGE_STATE_SEND_RECORDS:
  {
    uint32_t time = 0;
    uint8_t heart_rate = 0;
    uint8_t msg[] = "Sending";
    sys_display_show_noti(&s_oled_screen, msg);
    uint32_t ret = 0;
    do
    {
      ret = sys_storage_export(&s_heart_rate_records, &time, 4);
      if (ret != SYS_STORAGE_OK)
      {
        break;
      }
      ret = sys_storage_export(&s_heart_rate_records, &heart_rate, 1);
      if (ret != SYS_STORAGE_OK)
      {
        break;
      }
      if ((s_ppg_signal.heart_rate < s_mng.upper_threshold) && (s_ppg_signal.heart_rate > s_mng.lower_threshold))
      {
        sys_protocol_pkt_t record_time = {SYS_MANAGE_CMD_TIME, time, 0xFF};
        sys_protocol_pkt_t record_value = {SYS_MANAGE_CMD_GET_RECORDS, heart_rate, 0xFF};
        sys_protocol_send_pkt_to_port(record_time);
        sys_protocol_send_pkt_to_port(record_value);
      }
      else if (s_ppg_signal.heart_rate > s_mng.upper_threshold)
      {
        sys_protocol_pkt_t record_time = {SYS_MANAGE_CMD_TIME, time, 0x0F};
        sys_protocol_pkt_t record_value = {SYS_MANAGE_CMD_GET_RECORDS, heart_rate, 0x0F};
        sys_protocol_send_pkt_to_port(record_time);
        sys_protocol_send_pkt_to_port(record_value);
      }
      else
      {
        sys_protocol_pkt_t record_time = {SYS_MANAGE_CMD_TIME, time, 0xF0};
        sys_protocol_pkt_t record_value = {SYS_MANAGE_CMD_GET_RECORDS, heart_rate, 0xF0};
        sys_protocol_send_pkt_to_port(record_time);
        sys_protocol_send_pkt_to_port(record_value);
      }
    } while (ret == SYS_STORAGE_OK);

    sprintf(msg, "          ");
    sys_display_show_noti(&s_oled_screen, msg);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }

  case SYS_MAMAGE_STATE_CLEAR_RECORDS:
  {
    uint8_t msg[] = "Cleaning";
    sys_display_show_noti(&s_oled_screen, msg);
    sys_storage_fully_clean(&s_heart_rate_records);
    cb_clear(&s_rx_pkt_cbuf);
    sprintf(msg, "          ");
    sys_display_show_noti(&s_oled_screen, msg);
    s_mng.current_state = SYS_MANAGE_STATE_NORMAL;
    break;
  }
  default:
    break;
  }
}
/* Private definitions ------------------------------------------------ */
static void sys_manage_select_stream()
{
  if (s_mng.stream == SYS_MANAGE_STREAM_OLED)
  {
    s_mng.stream = SYS_MANAGE_STREAM_GUI;
  }
  else
  {
    s_mng.stream = SYS_MANAGE_STREAM_OLED;
  }
}

static void sys_manage_pwr_ctrl()
{
  s_mng.active ^= 1;
  if (s_mng.active)
  {
    s_mng.current_state = SYS_MANAGE_STATE_IDLE;
  }
  else
  {
    s_mng.current_state = SYS_MAMAGE_STATE_SLEEP;
  }
}

static void sys_manage_record_heart_rate()
{
  if (s_mng.current_state == SYS_MANAGE_STATE_NORMAL)
  {
    s_mng.current_state = SYS_MANAGE_STATE_RECORD;
  }
}

static void sys_manage_interval_elapsed(bsp_tim_typedef_t *tim)
{
  if (tim->Instance == s_tim_interval->Instance)
  {
    s_mng.current_state = SYS_MANAGE_STATE_RECORD;
  }
}
/* End of file -------------------------------------------------------- */
