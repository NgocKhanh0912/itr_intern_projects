/**
 * @file       sys_manage.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-07-22
 * @authors    Viet Hoang Xuan
 *             Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "sys_manage.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
/* Private defines ---------------------------------------------------- */
#define SYS_MANAGE_DATA_BUFFER_MAX_SIZE 100
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t s_cbuffer;
static char s_data_buffer[SYS_MANAGE_DATA_BUFFER_MAX_SIZE] = {0};
static char s_data_receive[SYS_MANAGE_DATA_BUFFER_MAX_SIZE] = {0};
static sys_manage_cmd_t s_cmd_type = SYS_MANAGE_IDLE;
static uint8_t s_data_length = 0;
static uint8_t s_alarm_id = 0;
static drv_ds1307_t s_ds_1307;
/* Private function prototypes ---------------------------------------- */
static sys_manage_status_t sys_manage_check(cbuffer_t *data_buffer);
static sys_manage_status_t sys_manage_set_time_12h(drv_ds1307_t *ds1307);
static sys_manage_status_t sys_manage_set_time_24h(drv_ds1307_t *ds1307);
static sys_manage_status_t sys_manage_set_epoch_time(drv_ds1307_t *ds1307);
static sys_manage_status_t sys_manage_get_time(drv_ds1307_t *ds1307);
static sys_manage_status_t sys_manage_set_alarm_mode_12h();
static sys_manage_status_t sys_manage_set_alarm_mode_24h();
static sys_manage_status_t sys_manage_cancel_alarm(uint8_t alarm_id);
static uint8_t sys_manage_convert_day_of_week(char day_of_week[]);
/* Function definitions ----------------------------------------------- */
sys_manage_status_t sys_manage_start(UART_HandleTypeDef *uart,
                                     I2C_HandleTypeDef *i2c)
{
  // Check parameters
  __ASSERT((uart != NULL), SYS_MANAGE_ERROR);
  __ASSERT((i2c != NULL), SYS_MANAGE_ERROR);
  // Initialize
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_protocol_init(uart);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  ret = (sys_manage_status_t)sys_time_init(i2c, &s_ds_1307);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  // Init circular buffer
  cb_init(&s_cbuffer, s_data_buffer, SYS_MANAGE_DATA_BUFFER_MAX_SIZE);
  sys_protocol_register_node_to_send(SYS_PROTOCOL_NODE_MNG, &s_cbuffer);
  // Return
  return SYS_MANAGE_OK;
}
sys_manage_status_t sys_manage_loop()
{
  sys_manage_check(&s_cbuffer);
  switch (s_cmd_type)
  {
  case SYS_MANAGE_IDLE:
    sys_time_get_alarm();
    break;
  case SYS_MANAGE_SET_TIME_24H:
    sys_manage_set_time_24h(&s_ds_1307);
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_SET_TIME_12H:
    sys_manage_set_time_12h(&s_ds_1307);
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_SET_EPOCH_TIME:
    sys_manage_set_epoch_time(&s_ds_1307);
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_GET_TIME:
    sys_manage_get_time(&s_ds_1307);
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_SET_ALARM_MODE_12H:
    sys_manage_set_alarm_mode_12h();
    s_alarm_id++;
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_SET_ALARM_MODE_24H:
    sys_manage_set_alarm_mode_24h();
    s_alarm_id++;
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  case SYS_MANAGE_CANCEL_ALARM:
    sys_manage_cancel_alarm(s_alarm_id);
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  default:
    // Do nothing
    s_cmd_type = SYS_MANAGE_IDLE;
    break;
  }
  return SYS_MANAGE_OK;
}
/* Private definitions ----------------------------------------------- */
static sys_manage_status_t sys_manage_check(cbuffer_t *data_buffer)
{
  // Check parameters
  __ASSERT((data_buffer != NULL), SYS_MANAGE_ERROR);
  __ASSERT((data_buffer->active == 1), SYS_MANAGE_ERROR);
  // Do some stuff
  if (cb_data_count(data_buffer) != 0)
  {
    char temp_storage[3];
    char temp_cmd_type[2];
    char temp_data_length[3];
    cb_read(data_buffer, temp_storage, 3);
    sscanf(temp_storage, "%1s%2s", temp_cmd_type, temp_data_length);
    s_cmd_type = (uint8_t)atoi(temp_cmd_type);
    s_data_length = (uint8_t)atoi(temp_data_length);
    cb_read(data_buffer, s_data_receive, s_data_length);
  }
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_set_time_24h(drv_ds1307_t *ds1307)
{
  char hour[3],
      minute[3],
      second[3],
      date[3],
      month[3],
      year[5],
      day_of_week[4];
  sscanf(s_data_receive,
         "%2sh%2sp%2ss%2sd%2sm%4sy%3s",
         hour,
         minute,
         second,
         date,
         month,
         year,
         day_of_week);
  // Update value
  ds1307->mode_hour = DS1307_MODE_24_HOUR;
  ds1307->hour = (uint8_t)atoi(hour);
  ds1307->minute = (uint8_t)atoi(minute);
  ds1307->second = (uint8_t)atoi(second);
  ds1307->date = (uint8_t)atoi(date);
  ds1307->month = (uint8_t)atoi(month);
  ds1307->year = (uint8_t)(atoi(year) % 100); // Modulo 100 to get last two digits
  ds1307->day = sys_manage_convert_day_of_week(day_of_week);
  // Set time for RTC
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_time_set_date_time(ds1307);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_set_time_12h(drv_ds1307_t *ds1307)
{
  char am_pm[3],
      hour[3],
      minute[3],
      second[3],
      date[3],
      month[3],
      year[5],
      day_of_week[4];
  sscanf(s_data_receive,
         "%2s%2sh%2sp%2ss%2sd%2sm%4sy%3s",
         am_pm,
         hour,
         minute,
         second,
         date,
         month,
         year,
         day_of_week);
  // Update value
  ds1307->mode_hour = DS1307_MODE_12_HOUR;
  ds1307->am_pm = (uint8_t)atoi(am_pm);
  ds1307->hour = (uint8_t)atoi(hour);
  ds1307->minute = (uint8_t)atoi(minute);
  ds1307->second = (uint8_t)atoi(second);
  ds1307->date = (uint8_t)atoi(date);
  ds1307->month = (uint8_t)atoi(month);
  ds1307->year = (uint8_t)atoi(year);
  ds1307->day = sys_manage_convert_day_of_week(day_of_week);
  // Set time for RTC
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_time_set_date_time(ds1307);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_set_epoch_time(drv_ds1307_t *ds1307)
{
  char epoch_time[100];
  sscanf(s_data_receive, "%s", epoch_time);
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = sys_time_set_epoch_time((uint32_t)atoi(epoch_time), ds1307);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_get_time(drv_ds1307_t *ds1307)
{
  // Get date time of RTC
  sys_time_get_date_time(ds1307);
  uint8_t temp_buffer_transmit[50];
  uint16_t pkt_len = 0;
  pkt_len = sprintf((char *)temp_buffer_transmit,
                    "%uh%up%us %udow %ud%um%uy",
                    ds1307->hour,
                    ds1307->minute,
                    ds1307->second,
                    ds1307->day,
                    ds1307->date,
                    ds1307->month,
                    ds1307->year);
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_protocol_send_packet_to_port(temp_buffer_transmit, pkt_len);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_set_alarm_mode_12h()
{
  char am_pm[3],
      hour[3],
      minute[3];
  sys_time_alarm_t alarm;
  sscanf(s_data_receive, "%2s%2sh%2sp", am_pm, hour, minute);
  // Update value
  alarm.alarm_am_pm = (uint8_t)atoi(am_pm);
  alarm.alarm_hour = (uint8_t)atoi(hour);
  alarm.alarm_minute = (uint8_t)atoi(minute);
  alarm.alarm_second = (uint8_t)0;
  alarm.alarm_mode_hour = DS1307_MODE_12_HOUR;
  // Set alarm for RTC
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_time_set_alarm(&alarm, s_alarm_id);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_set_alarm_mode_24h()
{
  char hour[3],
      minute[3];
  sys_time_alarm_t alarm;
  sscanf(s_data_receive, "%2sh%2sp", hour, minute);
  // Update value
  alarm.alarm_hour = (uint8_t)atoi(hour);
  alarm.alarm_minute = (uint8_t)atoi(minute);
  alarm.alarm_second = (uint8_t)0;
  alarm.alarm_mode_hour = DS1307_MODE_24_HOUR;
  // Set alarm for RTC
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_time_set_alarm(&alarm, s_alarm_id);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static sys_manage_status_t sys_manage_cancel_alarm(uint8_t alarm_id)
{
  // Cancel alarm with chosen ID
  sys_manage_status_t ret = SYS_MANAGE_OK;
  ret = (sys_manage_status_t)sys_time_cancel_alarm(alarm_id);
  __ASSERT((ret == SYS_MANAGE_OK), SYS_MANAGE_FAILED);
  return SYS_MANAGE_OK;
}
static uint8_t sys_manage_convert_day_of_week(char day_of_week[])
{
  uint8_t ret = -1;
  if (strcmp(day_of_week, "sun") == 0)
  {
    ret = 0; // Stand for Sunday
  }
  else if (strcmp(day_of_week, "mon") == 0)
  {
    ret = 1; // Stand for Monday
  }
  else if (strcmp(day_of_week, "tue") == 0)
  {
    ret = 2; // Stand for Tuesday
  }
  else if (strcmp(day_of_week, "wed") == 0)
  {
    ret = 3; // Stand for Wednesday
  }
  else if (strcmp(day_of_week, "thu") == 0)
  {
    ret = 4; // Stand for Thursday
  }
  else if (strcmp(day_of_week, "fri") == 0)
  {
    ret = 5; // Stand for Friday
  }
  else if (strcmp(day_of_week, "sat") == 0)
  {
    ret = 6; // Stand for Saturday
  }
  return ret;
}
/* End of file -------------------------------------------------------- */
