/**
 * @file       bsp_flash.c
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

/* Includes ----------------------------------------------------------- */
#include "bsp_flash.h"
#include "common.h"
/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_flash_unlock(void)
{
  uint32_t ret = HAL_OK;
  ret = HAL_FLASH_Unlock();
  __ASSERT(ret == HAL_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_lock(void)
{
  uint32_t ret = HAL_OK;
  ret = HAL_FLASH_Lock();
  __ASSERT(ret == HAL_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_write(uint32_t address, void *data_buf, uint32_t nbytes)
{
  __ASSERT(nbytes > 0, BSP_FLASH_ERROR);
  // Check valid address in range 0x08000000 - 0x0807FFFF
  __ASSERT((address >= BSP_FLASH_SECTOR_0_ADDRESS) &&
           (address <= (BSP_FLASH_SECTOR_7_ADDRESS + BSP_FLASH_SECTOR_7_SIZE - nbytes)),
           BSP_FLASH_ERROR);
  __ASSERT(data_buf != NULL, BSP_FLASH_ERROR);

  // Unlock the FLASH for next operations
  uint32_t ret = BSP_FLASH_OK;
  ret = bsp_flash_unlock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  // Write data in byte to FLASH
  for (uint32_t i = 0; i < nbytes; i++)
  {
    ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, address + i, *((uint8_t *)data_buf + i));
    __ASSERT(ret == HAL_OK, BSP_FLASH_FAILED);
  }
  // Lock FLASH for safety
  ret = bsp_flash_lock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_read(uint32_t address, void *data_buf, uint32_t nbytes)
{
  __ASSERT(nbytes > 0, BSP_FLASH_ERROR);
  // Check valid address in range 0x08000000 - 0x0807FFFF
  __ASSERT((address >= BSP_FLASH_SECTOR_0_ADDRESS) &&
           (address <= (BSP_FLASH_SECTOR_7_ADDRESS + BSP_FLASH_SECTOR_7_SIZE - nbytes)),
           BSP_FLASH_ERROR);
  __ASSERT(data_buf != NULL, BSP_FLASH_ERROR);

  // Don't need to unlock for reading operation
  for (uint32_t i = 0; i < nbytes; i++)
  {
    *((uint8_t *)data_buf + i) = *((__IO uint8_t *)address + i);
  }

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_erase_sector(uint32_t sector_num)
{
  __ASSERT((sector_num >= FLASH_SECTOR_0) && (sector_num <= FLASH_SECTOR_7), BSP_FLASH_ERROR);

  uint32_t ret = BSP_FLASH_OK;
  // Unlock the Flash for erasing
  ret = bsp_flash_unlock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  // Erase all data in sector, power supply is 3V
  FLASH_Erase_Sector(sector_num, FLASH_VOLTAGE_RANGE_3);

  // Lock FLASH for safety
  ret = bsp_flash_lock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_copy_sector(uint32_t src_sector_addr, uint32_t src_sector_size,
                               uint32_t dest_sector_addr, uint32_t dest_sector_size)
{
  __ASSERT((src_sector_addr >= BSP_FLASH_SECTOR_0_ADDRESS) && (src_sector_addr <= BSP_FLASH_SECTOR_7_ADDRESS), BSP_FLASH_ERROR);
  __ASSERT((dest_sector_addr >= BSP_FLASH_SECTOR_0_ADDRESS) && (dest_sector_addr <= BSP_FLASH_SECTOR_7_ADDRESS), BSP_FLASH_ERROR);
  __ASSERT((dest_sector_size >= src_sector_size), BSP_FLASH_ERROR);

  uint32_t ret = BSP_FLASH_OK;
  // Unlock the Flash
  ret = bsp_flash_unlock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  for (uint32_t i = 0; i < src_sector_size / 4; i++) 
  {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dest_sector_addr, *((__IO uint32_t *)src_sector_addr));
    src_sector_addr++;
    dest_sector_addr++;
  }

  // Lock FLASH for safety
  ret = bsp_flash_lock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

uint32_t bsp_flash_copy_address(uint32_t src_sector_addr, uint32_t src_sector_size,
                                uint32_t dest_sector_addr, uint32_t dest_sector_size,
                                uint32_t src_start_address, uint32_t size)
{
  __ASSERT((src_sector_addr >= BSP_FLASH_SECTOR_0_ADDRESS) && (src_sector_addr <= BSP_FLASH_SECTOR_7_ADDRESS), BSP_FLASH_ERROR);
  __ASSERT((dest_sector_addr >= BSP_FLASH_SECTOR_0_ADDRESS) && (dest_sector_addr <= BSP_FLASH_SECTOR_7_ADDRESS), BSP_FLASH_ERROR);
  __ASSERT((dest_sector_size >= src_sector_size), BSP_FLASH_ERROR);

  uint32_t ret = BSP_FLASH_OK;
  // Unlock the Flash
  ret = bsp_flash_unlock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  for (uint32_t i = 0; i < src_sector_size / 4; i++) 
  {
    if ((src_sector_addr >= src_start_address) && (src_sector_addr < (src_start_address + size)))
    {
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dest_sector_addr, *((__IO uint32_t *)src_sector_addr));
    }

    src_sector_addr++;
    dest_sector_addr++;
  }

  // Lock FLASH for safety
  ret = bsp_flash_lock();
  __ASSERT(ret == BSP_FLASH_OK, BSP_FLASH_FAILED);

  return BSP_FLASH_OK;
}

/* Private definitions ------------------------------------------------ */

/* End of file -------------------------------------------------------- */
