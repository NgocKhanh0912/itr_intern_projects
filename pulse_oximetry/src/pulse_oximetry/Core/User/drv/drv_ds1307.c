/**
 * @file       drv_ds1307.c
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

/* Includes ----------------------------------------------------------- */
#include "drv_ds1307.h"
#include "common.h"
#include <stdbool.h>
#include <stdint.h>

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief       Convert a BCD 8-bit number to a two digits decimal number.
 *
 * @param[in]   bcd           BCD 8-bit number you want to convert.
 *
 * @attention   No.
 *
 * @return      The decimal number.
 */
static uint8_t convert_bcd_to_decimal(uint8_t bcd);

/**
 * @brief       Convert a two digits decimal number to a BCD 8-bit number.
 *
 * @param[in]   decimal       Two digits decimal number you want to convert.
 *
 * @attention   No.
 *
 * @return      The BCD number.
 */
static uint8_t convert_decimal_to_bcd(uint8_t decimal);

/* Function definitions ----------------------------------------------- */
drv_ds1307_status_t drv_ds1307_init(I2C_HandleTypeDef *i2c,
                                    drv_ds1307_t *ds1307)
{
  __ASSERT((i2c != NULL), DRV_DS1307_ERROR);
  __ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  ds1307->i2c = i2c;

  return DRV_DS1307_OK;
}

drv_ds1307_status_t drv_ds1307_set_time(drv_ds1307_t *ds1307)
{
  __ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  __ASSERT((ds1307->second >= MINIMUM_SECOND) &&
               (ds1307->second <= MAXIMUM_SECOND),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->minute >= MINIMUM_MINUTE) &&
               (ds1307->minute <= MAXIMUM_MINUTE),
           DRV_DS1307_ERROR);

  uint8_t tx_time_buffer[DS1307_TIME_SIZE] = {0};

  *(tx_time_buffer) = convert_decimal_to_bcd(ds1307->second);
  *(tx_time_buffer + 1) = convert_decimal_to_bcd(ds1307->minute);
  *(tx_time_buffer + 2) = convert_decimal_to_bcd(ds1307->hour);

  if (ds1307->mode_hour == DS1307_MODE_12_HOUR)
  {
    __ASSERT((ds1307->hour >= MINIMUM_HOUR_MODE_12H) &&
                 (ds1307->hour <= MAXIMUM_HOUR_MODE_12H),
             DRV_DS1307_ERROR);

    *(tx_time_buffer + 2) |= (1 << HOUR_MODE_BIT); // Select mode 12h

    if (ds1307->am_pm == DS1307_SET_PM)
    {
      *(tx_time_buffer + 2) |= (1 << AM_PM_BIT); // Set PM
    }
    else if (ds1307->am_pm == DS1307_SET_AM)
    {
      *(tx_time_buffer + 2) &= ~(1 << AM_PM_BIT); // Set AM
    }
  }
  else if (ds1307->mode_hour == DS1307_MODE_24_HOUR)
  {
    __ASSERT((ds1307->hour >= MINIMUM_HOUR_MODE_24H) &&
                 (ds1307->hour <= MAXIMUM_HOUR_MODE_24H),
             DRV_DS1307_ERROR);

    *(tx_time_buffer + 2) &= ~(1 << HOUR_MODE_BIT); // Select mode 24h
  }

  drv_ds1307_status_t d_error_status = DRV_DS1307_OK;
  d_error_status = (drv_ds1307_status_t)bsp_i2c_mem_write(ds1307->i2c,
                                                          DS1307_I2C_ADDRESS,
                                                          DS1307_TIME_REGISTER_ADDRESS,
                                                          DS1307_REGISTER_ADDRESS_SIZE,
                                                          tx_time_buffer,
                                                          DS1307_TIME_SIZE,
                                                          DS1307_TIMEOUT);
  __ASSERT((d_error_status == DRV_DS1307_OK), DRV_DS1307_FAILED);

  return DRV_DS1307_OK;
}

drv_ds1307_status_t drv_ds1307_get_time(drv_ds1307_t *ds1307)
{
  __ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  uint8_t rx_time_buffer[DS1307_TIME_SIZE] = {0};

  drv_ds1307_status_t d_error_status = DRV_DS1307_OK;
  d_error_status = (drv_ds1307_status_t)bsp_i2c_mem_read(ds1307->i2c,
                                                         DS1307_I2C_ADDRESS,
                                                         DS1307_TIME_REGISTER_ADDRESS,
                                                         DS1307_REGISTER_ADDRESS_SIZE,
                                                         rx_time_buffer,
                                                         DS1307_TIME_SIZE,
                                                         DS1307_TIMEOUT);
  __ASSERT((d_error_status == DRV_DS1307_OK), DRV_DS1307_FAILED);

  ds1307->second = convert_bcd_to_decimal(*(rx_time_buffer));
  ds1307->minute = convert_bcd_to_decimal(*(rx_time_buffer + 1));

  __ASSERT((ds1307->second >= MINIMUM_SECOND) &&
               (ds1307->second <= MAXIMUM_SECOND),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->second >= MINIMUM_MINUTE) &&
               (ds1307->second <= MAXIMUM_MINUTE),
           DRV_DS1307_ERROR);

  if (((*(rx_time_buffer + 2) >> HOUR_MODE_BIT) & 0x01) == 1) // Mode 12h
  {
    if (((*(rx_time_buffer + 2) >> AM_PM_BIT) & 0x01) == 1) // Now is PM
    {
      ds1307->am_pm = DS1307_GET_PM;
    }
    else if (((*(rx_time_buffer + 2) >> AM_PM_BIT) & 0x01) == 0) // Now is AM
    {
      ds1307->am_pm = DS1307_GET_AM;
    }

    // Convert 5 bit from bit 0 to bit 4
    ds1307->hour = convert_bcd_to_decimal(*(rx_time_buffer + 2) & 0x1F);

    __ASSERT((ds1307->hour >= MINIMUM_HOUR_MODE_12H) &&
                 (ds1307->hour <= MAXIMUM_HOUR_MODE_12H),
             DRV_DS1307_ERROR);
  }
  else if (((*(rx_time_buffer + 2) >> HOUR_MODE_BIT) & 0x01) == 0) // Mode 24h
  {
    ds1307->hour = convert_bcd_to_decimal(*(rx_time_buffer + 2));

    __ASSERT((ds1307->hour >= MINIMUM_HOUR_MODE_24H) &&
                 (ds1307->hour <= MAXIMUM_HOUR_MODE_24H),
             DRV_DS1307_ERROR);
  }

  return DRV_DS1307_OK;
}

drv_ds1307_status_t drv_ds1307_set_date(drv_ds1307_t *ds1307)
{
  __ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  __ASSERT((ds1307->day >= MINIMUM_DAY) &&
               (ds1307->day <= MAXIMUM_DAY),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->date >= MINIMUM_DATE) &&
               (ds1307->date <= MAXIMUM_DATE),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->month >= MINIMUM_MONTH) &&
               (ds1307->month <= MAXIMUM_MONTH),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->year >= MINIMUM_YEAR) &&
               (ds1307->year <= MAXIMUM_YEAR),
           DRV_DS1307_ERROR);

  uint8_t tx_date_buffer[DS1307_DATE_SIZE] = {0};

  *(tx_date_buffer) = convert_decimal_to_bcd(ds1307->day);
  *(tx_date_buffer + 1) = convert_decimal_to_bcd(ds1307->date);
  *(tx_date_buffer + 2) = convert_decimal_to_bcd(ds1307->month);
  *(tx_date_buffer + 3) = convert_decimal_to_bcd(ds1307->year);

  drv_ds1307_status_t d_error_status = DRV_DS1307_OK;
  d_error_status = (drv_ds1307_status_t)bsp_i2c_mem_write(ds1307->i2c,
                                                          DS1307_I2C_ADDRESS,
                                                          DS1307_DATE_REGISTER_ADDRESS,
                                                          DS1307_REGISTER_ADDRESS_SIZE,
                                                          tx_date_buffer,
                                                          DS1307_DATE_SIZE,
                                                          DS1307_TIMEOUT);
  __ASSERT((d_error_status == DRV_DS1307_OK), DRV_DS1307_FAILED);

  return DRV_DS1307_OK;
}

drv_ds1307_status_t drv_ds1307_get_date(drv_ds1307_t *ds1307)
{
  __ASSERT((ds1307 != NULL), DRV_DS1307_ERROR);

  uint8_t rx_date_buffer[DS1307_DATE_SIZE] = {0};

  drv_ds1307_status_t d_error_status = DRV_DS1307_OK;
  d_error_status = (drv_ds1307_status_t)bsp_i2c_mem_read(ds1307->i2c,
                                                         DS1307_I2C_ADDRESS,
                                                         DS1307_DATE_REGISTER_ADDRESS,
                                                         DS1307_REGISTER_ADDRESS_SIZE,
                                                         rx_date_buffer,
                                                         DS1307_DATE_SIZE,
                                                         DS1307_TIMEOUT);
  __ASSERT((d_error_status == DRV_DS1307_OK), DRV_DS1307_FAILED);

  ds1307->day = convert_bcd_to_decimal(*(rx_date_buffer));
  ds1307->date = convert_bcd_to_decimal(*(rx_date_buffer + 1));
  ds1307->month = convert_bcd_to_decimal(*(rx_date_buffer + 2));
  ds1307->year = convert_bcd_to_decimal(*(rx_date_buffer + 3));

  __ASSERT((ds1307->day >= MINIMUM_DAY) &&
               (ds1307->day <= MAXIMUM_DAY),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->date >= MINIMUM_DATE) &&
               (ds1307->date <= MAXIMUM_DATE),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->month >= MINIMUM_MONTH) &&
               (ds1307->month <= MAXIMUM_MONTH),
           DRV_DS1307_ERROR);

  __ASSERT((ds1307->year >= MINIMUM_YEAR) &&
               (ds1307->year <= MAXIMUM_YEAR),
           DRV_DS1307_ERROR);

  return DRV_DS1307_OK;
}

/* Private definitions ------------------------------------------------ */
static uint8_t convert_bcd_to_decimal(uint8_t bcd)
{
  return (((bcd >> 4) * 10) + (bcd & 0x0F));
}

static uint8_t convert_decimal_to_bcd(uint8_t decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}

/* End of file -------------------------------------------------------- */
