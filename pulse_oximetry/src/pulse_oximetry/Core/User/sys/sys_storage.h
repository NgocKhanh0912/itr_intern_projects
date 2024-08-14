/**
 * @file       sys_storage.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-08-05
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      System sevice take responsibility for storing and managing data in FLASH memory
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_SYS_STORAGE_H
#define __USER_SYS_STORAGE_H

/* Includes ----------------------------------------------------------- */
#include "bsp_flash.h"

/* Public defines ----------------------------------------------------- */
#ifndef SYS_STORAGE_FLASH_SECTOR
#define SYS_STORAGE_FLASH_SECTOR (FLASH_SECTOR_7)
#endif

#ifndef SYS_STORAGE_FLASH_SECTOR_SIZE
#define SYS_STORAGE_FLASH_SECTOR_SIZE (BSP_FLASH_SECTOR_7_SIZE)
#endif

#ifndef SYS_STORAGE_FLASH_SECTOR_ADDRESS
#define SYS_STORAGE_FLASH_SECTOR_ADDRESS (BSP_FLASH_SECTOR_7_ADDRESS)
#endif

#ifndef SYS_STORAGE_BACKUP_FLASH_SECTOR
#define SYS_STORAGE_BACKUP_FLASH_SECTOR (FLASH_SECTOR_6)
#endif

#ifndef SYS_STORAGE_BACKUP_FLASH_SECTOR_SIZE
#define SYS_STORAGE_BACKUP_FLASH_SECTOR_SIZE (BSP_FLASH_SECTOR_6_SIZE)
#endif

#ifndef SYS_STORAGE_BACKUP_FLASH_SECTOR_ADDRESS
#define SYS_STORAGE_BACKUP_FLASH_SECTOR_ADDRESS (BSP_FLASH_SECTOR_6_ADDRESS)
#endif

/* Public enumerate/structure ----------------------------------------- */
enum sys_storage_status_t
{
  SYS_STORAGE_ERROR = 0xFFFFFFFF,
  SYS_STORAGE_FAILED = 0x7FFFFFFF,
  SYS_STORAGE_OK = 0x3FFFFFFF
};

/**
 * @brief Struct type of each segment
 */
typedef struct __attribute__((__packed__))
{
  uint8_t id;
  uint32_t address;
  uint32_t size;
  uint32_t pointer;
  uint32_t space_left;
} sys_storage_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief  Initialize the segment in flash to store data.
 *
 * @param[in]     storage       pointer to structure mangage the data segment.
 * @param[in]     start_address the start address of segment in Flash
 * @param[in]     size          Size of the segment
 *
 * @attention  Please read Flash module organization before use.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_storage_init(sys_storage_t *storage, uint32_t start_address, uint32_t size);

/**
 * @brief  Write data in "storage" segment if possible.
 *
 * @param[in]     storage       pointer to structure mangage the data segment.
 * @param[in]     data          data that want to stored.
 * @param[in]     size          Number of bytes of data.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_storage_import(sys_storage_t *storage, void *data, uint32_t size);

/**
 * @brief  Read data in "storage" segment if available.
 *
 * @param[in]     storage       pointer to structure mangage the data segment.
 * @param[in]     data          buffer stored the read data.
 * @param[in]     size          Number of bytes of data.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_storage_export(sys_storage_t *storage, void *data, uint32_t size);

/**
 * @brief  Fully clean data in "storage" segment.
 *
 * @param[in]     storage       pointer to structure mangage the data segment.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_storage_fully_clean(sys_storage_t *storage);

/**
 * @brief  Deinitialize the segment in flash to store data and free this segment.
 *
 * @param[in]     storage       pointer to structure mangage the data segment.
 *
 * @attention  Please read Flash module organization before use.
 *
 * @return
 *  - 0xFFFFFFFF: Error
 *  - 0x7FFFFFFF: Failed
 *  - 0x3FFFFFFF: Success
 */
uint32_t sys_storage_deinit(sys_storage_t *storage);

#endif // __USER_SYS_STORAGE_H

/* End of file -------------------------------------------------------- */
