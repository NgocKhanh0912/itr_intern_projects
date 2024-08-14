/**
 * @file       drv_ds1307.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       20/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs of driver for RTC DS1307
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_DRIVER_DRV_DS1307_H
#define __USER_DRIVER_DRV_DS1307_H

/* Includes ----------------------------------------------------------- */
#include "bsp_i2c.h"

/* Public defines ----------------------------------------------------- */
#define DS1307_I2C_ADDRESS (0x68 << 1)

#define DS1307_TIMEOUT (1000) // Timeout 1 second

#define DS1307_TIME_REGISTER_ADDRESS (0x00)
#define DS1307_DATE_REGISTER_ADDRESS (0x03)

#define DS1307_REGISTER_ADDRESS_SIZE (I2C_MEMADD_SIZE_8BIT)

#define DS1307_TIME_SIZE (3) // Time size is 3 for second, minute and hour
#define DS1307_DATE_SIZE (4) // Date size is 4 for date, day, month and year

#define AM_PM_BIT (5)
#define HOUR_MODE_BIT (6)

#define MAXIMUM_DAY (7) // 2 to 7 are Monday to Saturday
#define MINIMUM_DAY (1) // 1 is Sunday

#define MAXIMUM_DATE (31)
#define MINIMUM_DATE (1)

#define MAXIMUM_MONTH (12)
#define MINIMUM_MONTH (1)

#define MAXIMUM_YEAR (99)
#define MINIMUM_YEAR (0)

#define MAXIMUM_HOUR_MODE_12H (12)
#define MINIMUM_HOUR_MODE_12H (1)

#define MAXIMUM_HOUR_MODE_24H (23)
#define MINIMUM_HOUR_MODE_24H (0)

#define MAXIMUM_MINUTE (59)
#define MINIMUM_MINUTE (0)

#define MAXIMUM_SECOND (59)
#define MINIMUM_SECOND (0)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Status of DS1307
 */
typedef enum
{
  DRV_DS1307_ERROR = 0xFFFFFFFF,
  DRV_DS1307_FAILED = 0x7FFFFFFF,
  DRV_DS1307_OK = 0x3FFFFFFF
} drv_ds1307_status_t;

/**
 * @brief Enum for select mode 12/24h
 */
typedef enum
{
  DS1307_MODE_24_HOUR = 0,
  DS1307_MODE_12_HOUR
} drv_ds1307_mode_hour_t;

/**
 * @brief Enum for mode 12h to set and get AM/PM
 */
typedef enum
{
  DS1307_SET_AM = 0,
  DS1307_SET_PM,
  DS1307_GET_AM,
  DS1307_GET_PM
} drv_ds1307_am_pm_t;

/**
 * @brief DS1307 data type
 */
typedef struct __attribute__((__packed__))
{
  I2C_HandleTypeDef *i2c;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t date;
  uint8_t day;
  uint8_t month;
  uint8_t year;
  drv_ds1307_mode_hour_t mode_hour;
  drv_ds1307_am_pm_t am_pm;
} drv_ds1307_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief       Initialize RTC DS1307.
 *
 * @param[in]   i2c       Pointer to the I2C handle structure in driver.
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in driver.
 *
 * @attention   This function should be called first.
 *              Only one RTC DS1307 is allowed to run at a time.
 *              If you initialize another DS1307,
 *              it means you have deinitialized the previous DS1307.
 *
 * @return      The status of the DS1307 driver operation.
 */
drv_ds1307_status_t drv_ds1307_init(I2C_HandleTypeDef *i2c,
                                    drv_ds1307_t *ds1307);

/**
 * @brief       Set time to RTC DS1307.
 *
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in driver.
 *
 * @attention   No.
 *
 * @return      The status of the DS1307 driver operation.
 */
drv_ds1307_status_t drv_ds1307_set_time(drv_ds1307_t *ds1307);

/**
 * @brief       Get time from RTC DS1307.
 *
 * @param[out]  ds1307    Pointer to the drv_ds1307_t variable in driver.
 *
 * @attention   No.
 *
 * @return      The status of the DS1307 driver operation.
 */
drv_ds1307_status_t drv_ds1307_get_time(drv_ds1307_t *ds1307);

/**
 * @brief       Set date to RTC DS1307.
 *
 * @param[in]   ds1307    Pointer to the drv_ds1307_t variable in driver.
 *
 * @attention   No.
 *
 * @return      The status of the DS1307 driver operation.
 */
drv_ds1307_status_t drv_ds1307_set_date(drv_ds1307_t *ds1307);

/**
 * @brief       Get date from RTC DS1307.
 *
 * @param[out]  ds1307    Pointer to the drv_ds1307_t variable in driver.
 *
 * @attention   No.
 *
 * @return      The status of the DS1307 driver operation.
 */
drv_ds1307_status_t drv_ds1307_get_date(drv_ds1307_t *ds1307);

#endif // __USER_DRIVER_DRV_DS1307_H

/* End of file -------------------------------------------------------- */
