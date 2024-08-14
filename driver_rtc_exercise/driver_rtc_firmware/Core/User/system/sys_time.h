/**
 * @file       sys_time.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYSTEM_SYS_TIME_H
#define __USER_SYSTEM_SYS_TIME_H

/* Includes ----------------------------------------------------------- */
#include "drv_ds1307.h"
#include "stdbool.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Status of sys_time operation
 */
typedef enum 
{
  SYS_TIME_ERROR = -2,
  SYS_TIME_FAILED,
  SYS_TIME_OK
} sys_time_status_t;

/**
 * @brief Alarm data type
 */
typedef struct __attribute__((__packed__))
{
  uint8_t alarm_hour;
  uint8_t alarm_minute;
  uint8_t alarm_second;
  drv_ds1307_mode_hour_t alarm_mode_hour;
  drv_ds1307_am_pm_t alarm_am_pm;
} sys_time_alarm_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */
typedef void (*sys_alarm_evt_cb_t)(void);
typedef void (*sys_used_alarm_evt_cb_t)(void);

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Initialize sys_time for managing RTC DS1307.
 *
 * @param[in]   i2c       Pointer to the I2C handle structure in sys_time.
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in sys_time.
 *
 * @attention   This function should be called first.
 *              Only one RTC DS1307 is allowed to run at a time. 
 *              If you initialize another DS1307,
 *              it means you have deinitialized the previous DS1307.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_init(I2C_HandleTypeDef *i2c, 
                                drv_ds1307_t *ds1307);

/**
 * @brief       Set epoch time to RTC DS1307.
 *
 * @param[in]   epoch_time    time_t type epoch time value.
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in sys_time.
 * 
 * @attention   GMT0 epoch time is required.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_set_epoch_time(uint32_t epoch_time, 
                                          drv_ds1307_t *ds1307);

/**
 * @brief       Set date time to RTC DS1307.
 *
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in sys_time.
 *
 * @attention   Date time is required (HH:MM:SS d:DD:MM:YY).
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_set_date_time(drv_ds1307_t *ds1307);

/**
 * @brief       Get date time from RTC DS1307.
 *
 * @param[out]  ds1307    Pointer to the drv_ds1307_t variable in sys_time.
 *
 * @attention   Get date time (HH:MM:SS d:DD:MM:YY).
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_get_date_time(drv_ds1307_t *ds1307);

/**
 * @brief       Set alarm.
 *
 * @param[in]   alarm       Pointer to the sys_time_alarm_t variable in sys_time.
 * @param[in]   alarm_id    Alarm ID (alarm number).
 * 
 * @attention   No.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_set_alarm(sys_time_alarm_t *alarm_time,
                                     uint8_t alarm_id);

/**
 * @brief       Get alarm.
 *
 * @param[out]  No.
 *
 * @attention   Callback to sys_manage if alarm event happened.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_get_alarm();

/**
 * @brief       Cancel alarm.
 *
 * @param[in]   alarm_id    Alarm ID (alarm number).
 *
 * @attention   Cancel the alarm corresponding to the alarm id.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_cancel_alarm(uint8_t alarm_id);

/**
 * @brief       Callback to sys_manage if alarm event happened.
 *
 * @param[in]   alarm_evt_cb           Function pointer to callback.
 *
 * @attention   No.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_register_alarm_cb(sys_alarm_evt_cb_t alarm_evt_cb);

/**
 * @brief       Callback to sys_manage if used alarm is set again event happened.
 *
 * @param[in]   used_alarm_evt_cb      Function pointer to callback.
 *
 * @attention   No.
 * 
 * @return      The status of sys_time operation.
 */
sys_time_status_t sys_time_register_used_alarm_cb(sys_used_alarm_evt_cb_t used_alarm_evt_cb);

#endif // __USER_SYSTEM_SYS_TIME_H

/* End of file -------------------------------------------------------- */
