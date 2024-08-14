/**
 * @file       bsp_flash.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-08-04
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      This BSP supports to interface and transfer data to FLASH easily.
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_BSP_FLASH_H
#define __USER_BSP_FLASH_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
/* Public defines ----------------------------------------------------- */

#define BSP_FLASH_SECTOR_0_ADDRESS (0x08000000U) /*!< Flash sector 0 start address */
#define BSP_FLASH_SECTOR_1_ADDRESS (0x08004000U) /*!< Flash sector 1 start address */
#define BSP_FLASH_SECTOR_2_ADDRESS (0x08008000U) /*!< Flash sector 2 start address */
#define BSP_FLASH_SECTOR_3_ADDRESS (0x0800C000U) /*!< Flash sector 3 start address */
#define BSP_FLASH_SECTOR_4_ADDRESS (0x08010000U) /*!< Flash sector 4 start address */
#define BSP_FLASH_SECTOR_5_ADDRESS (0x08020000U) /*!< Flash sector 5 start address */
#define BSP_FLASH_SECTOR_6_ADDRESS (0x08040000U) /*!< Flash sector 6 start address */
#define BSP_FLASH_SECTOR_7_ADDRESS (0x08060000U) /*!< Flash sector 7 start address */

#define BSP_FLASH_SECTOR_0_SIZE    (0x4000U)  /*!< Flash sector 0 size 16 KB */
#define BSP_FLASH_SECTOR_1_SIZE    (0x4000U)  /*!< Flash sector 1 size 16 KB */
#define BSP_FLASH_SECTOR_2_SIZE    (0x4000U)  /*!< Flash sector 2 size 16 KB */
#define BSP_FLASH_SECTOR_3_SIZE    (0x4000U)  /*!< Flash sector 3 size 16 KB */
#define BSP_FLASH_SECTOR_4_SIZE    (0x10000U) /*!< Flash sector 4 size 64 KB */
#define BSP_FLASH_SECTOR_5_SIZE    (0x20000U) /*!< Flash sector 5 size 128 KB */
#define BSP_FLASH_SECTOR_6_SIZE    (0x20000U) /*!< Flash sector 6 size 128 KB */
#define BSP_FLASH_SECTOR_7_SIZE    (0x20000U) /*!< Flash sector 7 size 128 KB */
/* Public enumerate/structure ----------------------------------------- */

enum bsp_flash_status_t
{
  BSP_FLASH_ERROR = 0xFFFFFFFF,
  BSP_FLASH_FAILED = 0x7FFFFFFF,
  BSP_FLASH_OK = 0x3FFFFFFF
};

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief  Unlock the FLASH memory
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_unlock(void);

/**
 * @brief  Lock the FLASH memory
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_lock(void);

/**
 * @brief  Erase whole data in selected sector
 *
 * @param[in]   sector_num   Sector want to be erased.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_erase_sector(uint32_t sector_num);

/**
 * @brief  Copy whole data from src_sector to dest_sector
 *
 * @param[in]    src_sector_addr    Source sector start address.
 * @param[in]    src_sector_size    Source sector full size.
 * @param[out]   dest_sector_addr   Destination sector start address.
 * @param[in]    dest_sector_size   Destination sector full size.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_copy_sector(uint32_t src_sector_addr, uint32_t src_sector_size,
                               uint32_t dest_sector_addr, uint32_t dest_sector_size);

/**
 * @brief  Copy a part of data from src_sector to dest_sector
 *
 * @param[in]    src_sector_addr      Source sector start address.
 * @param[in]    src_sector_size      Source sector full size.
 * @param[out]   dest_sector_addr     Destination sector start address.
 * @param[in]    dest_sector_size     Destination sector full size.
 * @param[in]    src_start_address    Start of address you want to copy.
 * @param[in]    size                 Size of memory you want to copy.
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_copy_address(uint32_t src_sector_addr, uint32_t src_sector_size,
                                uint32_t dest_sector_addr, uint32_t dest_sector_size,
                                uint32_t src_start_address, uint32_t size);

/**
 * @brief  Write data from address in FLASH
 *
 * @param[in]   address      Address that start the write operation.
 * @param[in]   data_buf     Pointer to data will be written.
 * @param[in]   nbytes       Size of written data in byte.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_write(uint32_t address, void *data_buf, uint32_t nbytes);

/**
 * @brief  Read data from address in FLASH
 *
 * @param[in]   address      Address that start the read operation.
 * @param[in]   data_buf     Pointer to data will be read.
 * @param[in]   nbytes       Size of read data in byte.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t bsp_flash_read(uint32_t address, void *data_buf, uint32_t nbytes);

#endif // __USER_BSP_FLASH_H

/* End of file -------------------------------------------------------- */
