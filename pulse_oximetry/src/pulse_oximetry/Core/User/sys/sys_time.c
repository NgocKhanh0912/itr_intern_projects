/**
 * @file       sys_time.C
 * @copyright
 * @license
 * @version    1.0.0
 * @date       21/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs of system for manage time, alarm from RTC DS1307
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "sys_time.h"
#include "common.h"
#include <stdint.h>
#include <time.h>

/* Private defines ---------------------------------------------------- */
#define GMT0_TO_GMT7_SECOND (25200)
#define MAX_NUMBER_OF_ALARM (5)

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
sys_alarm_evt_cb_t alarm_evt_cb_internal;
sys_used_alarm_evt_cb_t used_alarm_evt_cb_internal;

// Internal variable to get date to compare with s_alarm_internal
drv_ds1307_t *s_alarm_ds1307_internal = NULL;

// Internal pointer array to store alarm time when user pass to sys_time_set_alarm
sys_time_alarm_t *s_alarm_time_internal[MAX_NUMBER_OF_ALARM] = {NULL};

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Convert GMT0 epoch time GMT0 to GMT7 date time.
 *
 * @param[in]       epoch_time    GMT0 epoch time for converting
 *                                  to GMT7 date time.
 * @param[in]       date_time     Pointer to drv_ds1307_t structure
 *                                  to store date time.
 *
 * @return          The status of sys_time operation.
 */
static sys_time_status_t sys_time_convert_epoch_time(uint32_t epoch_time,
                                                     drv_ds1307_t *date_time);

/* Function definitions ----------------------------------------------- */
sys_time_status_t sys_time_init(I2C_HandleTypeDef *i2c,
                                drv_ds1307_t *ds1307)
{
  sys_time_status_t ret = SYS_TIME_OK;

  ret = (sys_time_status_t)drv_ds1307_init(i2c, ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  s_alarm_ds1307_internal = ds1307;

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_set_epoch_time(uint32_t epoch_time,
                                          drv_ds1307_t *ds1307)
{
  sys_time_status_t ret = SYS_TIME_OK;

  ret = sys_time_convert_epoch_time(epoch_time, ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  ret = (sys_time_status_t)drv_ds1307_set_time(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  ret = (sys_time_status_t)drv_ds1307_set_date(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_set_date_time(drv_ds1307_t *ds1307)
{
  sys_time_status_t ret = SYS_TIME_OK;

  ret = (sys_time_status_t)drv_ds1307_set_time(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  ret = (sys_time_status_t)drv_ds1307_set_date(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_get_date_time(drv_ds1307_t *ds1307)
{
  sys_time_status_t ret = SYS_TIME_OK;

  ret = (sys_time_status_t)drv_ds1307_get_time(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  ret = (sys_time_status_t)drv_ds1307_get_date(ds1307);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  return SYS_TIME_OK;
}

uint32_t sys_time_get_epoch_time(drv_ds1307_t *ds1307)
{
  // Check parameters
  __ASSERT((ds1307 != NULL), SYS_TIME_ERROR);
  // Operation
  sys_time_get_date_time(ds1307);

  struct tm t;
  time_t t_of_day;
  t.tm_year = (ds1307->year + 2000) - 1900;
  t.tm_mon = (ds1307->month) - 1;
  t.tm_mday = (ds1307->date);
  t.tm_hour = (ds1307->hour);
  t.tm_min = (ds1307->minute);
  t.tm_sec = (ds1307->second);
  t.tm_isdst = (-1);
  t_of_day = mktime(&t);
  // Return
  return (uint32_t)t_of_day;
}

sys_time_status_t sys_time_set_alarm(sys_time_alarm_t *alarm_time,
                                     uint8_t alarm_id)
{
  if (s_alarm_time_internal[alarm_id] != NULL)
  {
    __CALLBACK(used_alarm_evt_cb_internal);
  }

  __ASSERT((alarm_time != NULL), SYS_TIME_ERROR);

  __ASSERT(((alarm_time->alarm_second) >= MINIMUM_SECOND) &&
               ((alarm_time->alarm_second) <= MAXIMUM_SECOND),
           SYS_TIME_ERROR);

  __ASSERT(((alarm_time->alarm_minute) >= MINIMUM_MINUTE) &&
               ((alarm_time->alarm_minute) <= MAXIMUM_MINUTE),
           SYS_TIME_ERROR);

  if (alarm_time->alarm_mode_hour == DS1307_MODE_12_HOUR)
  {
    __ASSERT(((alarm_time->alarm_hour) >= MINIMUM_HOUR_MODE_12H) &&
                 ((alarm_time->alarm_hour) <= MAXIMUM_HOUR_MODE_12H),
             SYS_TIME_ERROR);
  }
  else if (alarm_time->alarm_mode_hour == DS1307_MODE_24_HOUR)
  {
    __ASSERT(((alarm_time->alarm_hour) >= MINIMUM_HOUR_MODE_24H) &&
                 ((alarm_time->alarm_hour) <= MAXIMUM_HOUR_MODE_24H),
             SYS_TIME_ERROR);
  }

  s_alarm_time_internal[alarm_id] = alarm_time;

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_get_alarm()
{
  __ASSERT((s_alarm_time_internal != NULL), SYS_TIME_ERROR);

  sys_time_status_t ret = SYS_TIME_OK;

  ret = (sys_time_status_t)drv_ds1307_get_time(s_alarm_ds1307_internal);
  __ASSERT((ret == SYS_TIME_OK), SYS_TIME_FAILED);

  for (int i = 0; i < MAX_NUMBER_OF_ALARM; i++)
  {
    if (s_alarm_ds1307_internal->hour == s_alarm_time_internal[i]->alarm_hour)
    {
      if (s_alarm_ds1307_internal->minute == s_alarm_time_internal[i]->alarm_minute)
      {
        if (s_alarm_ds1307_internal->mode_hour == s_alarm_time_internal[i]->alarm_mode_hour)
        {
          __CALLBACK(alarm_evt_cb_internal);
        }
      }
    }
  }

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_cancel_alarm(uint8_t alarm_id)
{
  __ASSERT((s_alarm_time_internal[alarm_id] != NULL), SYS_TIME_ERROR);

  s_alarm_time_internal[alarm_id] = NULL;

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_register_alarm_cb(sys_alarm_evt_cb_t alarm_evt_cb)
{
  __ASSERT((alarm_evt_cb != NULL), SYS_TIME_ERROR);

  alarm_evt_cb_internal = alarm_evt_cb;

  return SYS_TIME_OK;
}

sys_time_status_t sys_time_register_used_alarm_cb(sys_used_alarm_evt_cb_t used_alarm_evt_cb)
{
  __ASSERT((used_alarm_evt_cb != NULL), SYS_TIME_ERROR);

  used_alarm_evt_cb_internal = used_alarm_evt_cb;

  return SYS_TIME_OK;
}

/* Private definitions ------------------------------------------------ */
static sys_time_status_t sys_time_convert_epoch_time(uint32_t epoch_time,
                                                     drv_ds1307_t *date_time)
{
  __ASSERT((date_time != NULL), SYS_TIME_ERROR);

  // Declare a tm structure to hold the result of localtime
  struct tm *current_date_time;

  // // change epoch time from GMT0 to GMT7
  // epoch_time += GMT0_TO_GMT7_SECOND;

  time_t epoch_time_temp = (time_t)epoch_time;

  // Convert epoch time to tm structure
  current_date_time = localtime(&epoch_time_temp);

  // Check if localtime returns NULL
  __ASSERT((current_date_time != NULL), SYS_TIME_FAILED);

  // Extract individual components: year, month, day, date, hour, minute, second

  // tm_year is the number of years since 1900
  // -100 to get number of years since 2000
  date_time->year = (current_date_time->tm_year) - 100;

  // tm_mon is the number of months since January (0 = January)
  // +1 to fix with RTC DS1307 (Jan to Dec is 1 to 12)
  date_time->month = (current_date_time->tm_mon) + 1;

  date_time->date = current_date_time->tm_mday;

  // tm_wday: Sunday is 0, Monday to Saturday is 1 to 6
  // +1 to convert (0->6) to (1->7) to fix with RTC DS1307
  date_time->day = (current_date_time->tm_wday) + 1;

  date_time->hour = current_date_time->tm_hour;
  date_time->minute = current_date_time->tm_min;
  date_time->second = current_date_time->tm_sec;

  return SYS_TIME_OK;
}

/* End of file -------------------------------------------------------- */
