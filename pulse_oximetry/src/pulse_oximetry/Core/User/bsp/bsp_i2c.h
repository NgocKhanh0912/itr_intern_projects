/**
 * @file       bsp_i2c.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-07-20
 * @authors    Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Board Support Packages for I2C
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_I2C_H
#define __BSP_I2C_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
/* Public defines ----------------------------------------------------- */
typedef I2C_HandleTypeDef bsp_i2c_handle_t;
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BSP_I2C_ERROR = 0xFFFFFFFF,
  BSP_I2C_FAILED = 0x7FFFFFFF,
  BSP_I2C_OK = 0x3FFFFFFF
} bsp_i2c_status_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/**
 * @brief         Transmit an amount of data over I2C from Master
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 * @param[in]     time_out            Time to wait before retrying transmitting
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_master_transmit(bsp_i2c_handle_t *hi2c,
                                         uint16_t device_address,
                                         uint8_t *data_buffer,
                                         uint16_t size,
                                         uint32_t time_out);

/**
 * @brief         Receive an amount of data over I2C from Master
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[out]    data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to receive
 * @param[in]     time_out            Time to wait before retrying transmitting
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_master_receive(bsp_i2c_handle_t *hi2c,
                                        uint16_t device_address,
                                        uint8_t *data_buffer,
                                        uint16_t size,
                                        uint32_t time_out);

/**
 * @brief         Transmit an amount of data over I2C from Master with Interrupt
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_master_transmit_it(bsp_i2c_handle_t *hi2c,
                                            uint16_t device_address,
                                            uint8_t *data_buffer,
                                            uint16_t size);

/**
 * @brief         Receive an amount of data over I2C from Master with Interrupt
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to receive
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_master_receive_it(bsp_i2c_handle_t *hi2c,
                                           uint16_t device_address,
                                           uint8_t *data_buffer,
                                           uint16_t size);

/**
 * @brief         Write an amount of data into a specific memory over I2C
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     mem_address         Internal memory address
 * @param[in]     mem_address_size    Size of internal memory address
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 * @param[in]     time_out            Time to wait before retrying writing
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_mem_write(bsp_i2c_handle_t *hi2c,
                                   uint16_t device_address,
                                   uint16_t mem_address,
                                   uint16_t mem_address_size,
                                   uint8_t *data_buffer,
                                   uint16_t size,
                                   uint32_t time_out);

/**
 * @brief         Read an amount of data from a specific memory over I2C
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     mem_address         Internal memory address
 * @param[in]     mem_address_size    Size of internal memory address
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 * @param[in]     time_out            Time to wait before retrying reading
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_mem_read(bsp_i2c_handle_t *hi2c,
                                  uint16_t device_address,
                                  uint16_t mem_address,
                                  uint16_t mem_address_size,
                                  uint8_t *data_buffer,
                                  uint16_t size,
                                  uint32_t time_out);

/**
 * @brief         Write an amount of data into a specific memory over I2C with Interrupt
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     mem_address         Internal memory address
 * @param[in]     mem_address_size    Size of internal memory address
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_mem_write_it(bsp_i2c_handle_t *hi2c,
                                      uint16_t device_address,
                                      uint16_t mem_address,
                                      uint16_t mem_address_size,
                                      uint8_t *data_buffer,
                                      uint16_t size);

/**
 * @brief         Read an amount of data from a specific memory over I2C withn Interrupt
 *
 * @param[in]     hi2c                I2C Handler
 * @param[in]     device_address      Device address. Shift left 1 bit
 *                                    before calling this API
 * @param[in]     mem_address         Internal memory address
 * @param[in]     mem_address_size    Size of internal memory address
 * @param[in]     data_buffer         Pointer to data buffer
 * @param[in]     size                Amount of data to transfer
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
bsp_i2c_status_t bsp_i2c_mem_read_it(bsp_i2c_handle_t *hi2c,
                                     uint16_t device_address,
                                     uint16_t mem_address,
                                     uint16_t mem_address_size,
                                     uint8_t *data_buffer,
                                     uint16_t size);
#endif // __BSP_I2C_H
/* End of file -------------------------------------------------------- */
