/**
 * @file       drv_ssd1306.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v0.0.1
 * @date       2024-07-30
 * @author     Viet Hoang Xuan
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
#include "drv_ssd1306.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
/* Private defines ---------------------------------------------------- */
#define SSD1306_CONTRAST_REGISTER (0x81)
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
static uint32_t drv_ssd1306_oled_init(drv_ssd1306_t *dev);
static uint32_t drv_ssd1306_write_command(drv_ssd1306_t *dev, uint8_t command);
static uint32_t drv_ssd1306_write_data(drv_ssd1306_t *dev, uint8_t *data, uint16_t size);
/* Function definitions ----------------------------------------------- */

uint32_t drv_ssd1306_init(drv_ssd1306_t *dev,
                          bsp_i2c_handle_t *dev_i2c,
                          uint16_t dev_address,
                          uint8_t *dev_buffer,
                          uint8_t dev_width,
                          uint8_t dev_height)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((dev_i2c != NULL), DRV_SSD1306_ERROR);
  __ASSERT((dev_address < 256), DRV_SSD1306_ERROR);
  __ASSERT((dev_buffer != NULL), DRV_SSD1306_ERROR);
  __ASSERT((dev_width <= 128), DRV_SSD1306_ERROR);
  __ASSERT((dev_height <= 64), DRV_SSD1306_ERROR);
  // Pass values
  dev->i2c = dev_i2c;
  dev->address = dev_address;
  dev->buffer = dev_buffer;
  dev->size.width = dev_width;
  dev->size.height = dev_height;
  // Init sequence
  uint32_t ret = DRV_SSD1306_OK;
  HAL_Delay(100);
  ret = drv_ssd1306_oled_init(dev);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_set_display(drv_ssd1306_t *dev,
                                 drv_ssd1306_display_t state)
{
  uint8_t value = 0x00;
  switch (state)
  {
  case DRV_SSD1306_DISPLAY_ON:
    value = 0xAF;
    break;
  case DRV_SSD1306_DISPLAY_OFF:
    value = 0xAE;
    break;
  default:
    // Do nothing
    break;
  }
  uint32_t ret = DRV_SSD1306_OK;
  ret = drv_ssd1306_write_command(dev, value);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_fill_screen(drv_ssd1306_t *dev,
                                 uint32_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_WHITE) || (color == DRV_SSD1306_COLOR_BLACK),
           DRV_SSD1306_ERROR);
  // Operation
  memset((dev->buffer), (color == DRV_SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, (dev->size.height * dev->size.width / 8));
  uint32_t ret = DRV_SSD1306_OK;
  ret = drv_ssd1306_update_screen(dev);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_set_contrast(drv_ssd1306_t *dev, uint8_t value)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  // Operations
  enum drv_ssd1306_status_t ret = DRV_SSD1306_OK;
  ret = drv_ssd1306_write_command(dev, SSD1306_CONTRAST_REGISTER);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  ret = drv_ssd1306_write_command(dev, value);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_set_cursor(drv_ssd1306_t *dev,
                                uint8_t pos_x,
                                uint8_t pos_y)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x < dev->size.width), DRV_SSD1306_ERROR);
  __ASSERT((pos_y < dev->size.height), DRV_SSD1306_OK);
  // Pass value
  dev->cursor.x = pos_x;
  dev->cursor.y = pos_y;
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_draw_pixel(drv_ssd1306_t *dev,
                                uint8_t pos_x,
                                uint8_t pos_y,
                                drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x < dev->size.width), DRV_SSD1306_ERROR);
  __ASSERT((pos_y < dev->size.height), DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Pass value
  switch (color)
  {
  case DRV_SSD1306_COLOR_WHITE:
    dev->buffer[pos_x + (pos_y / 8) * 128] |= (1 << (pos_y % 8));
    break;
  case DRV_SSD1306_COLOR_BLACK:
    dev->buffer[pos_x + (pos_y / 8) * 128] &= ~(1 << (pos_y % 8));
    break;
  default:
    // Do nothing
    break;
  }
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_write_char(drv_ssd1306_t *dev,
                                char ch,
                                ssd1306_font_t font,
                                drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((ch >= 32) && (ch <= 126), DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Check remaining space on current line
  __ASSERT(((dev->cursor.x + font.width) <= dev->size.width) && ((dev->cursor.y + font.height) <= dev->size.height),
           DRV_SSD1306_FAILED);
  // Writing operation
  for (uint8_t i = 0; i < font.height; i++)
  {
    uint16_t temp = font.data_font[(ch - 32) * font.height + i];
    for (uint8_t j = 0; j < font.width; j++)
    {
      if ((temp << j) & 0x8000)
      {
        drv_ssd1306_draw_pixel(dev, dev->cursor.x + j, dev->cursor.y + i, color);
      }
      else
      {
        drv_ssd1306_draw_pixel(dev, dev->cursor.x + j, dev->cursor.y + i, !color);
      }
    }
  }
  // Update space
  dev->cursor.x += font.char_width ? font.char_width[ch - 32] : font.width;
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_write_string(drv_ssd1306_t *dev,
                                  char *str,
                                  ssd1306_font_t font,
                                  drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((str != NULL), DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Writing operation
  while (*str)
  {
    if (drv_ssd1306_write_char(dev, *str, font, color) != DRV_SSD1306_OK)
    {
      return DRV_SSD1306_FAILED;
    }
    str++;
  }
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_update_screen(drv_ssd1306_t *dev)
{
  __ASSERT(dev != NULL, DRV_SSD1306_ERROR);

  for (uint8_t i = 0; i < (dev->size.height) / 8; i++)
  {
    drv_ssd1306_write_command(dev, 0xB0 + i); // Set the current RAM page address.
    drv_ssd1306_write_command(dev, 0x00);
    drv_ssd1306_write_command(dev, 0x10);
    drv_ssd1306_write_data(dev, &dev->buffer[(dev->size.width) * i], dev->size.width);
  }
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_draw_bitmap(drv_ssd1306_t *dev,
                                 uint8_t pos_x,
                                 uint8_t pos_y,
                                 const uint8_t *bitmap,
                                 uint8_t bitmap_width,
                                 uint8_t bitmap_height,
                                 drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x < dev->size.width) && (pos_y < dev->size.height),
           DRV_SSD1306_ERROR);
  __ASSERT((bitmap != NULL), DRV_SSD1306_ERROR);
  __ASSERT((bitmap_width <= dev->size.width) && (bitmap_height <= dev->size.height),
           DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Operation
  // Compute the number of bytes to store one row of the bitmap
  uint8_t byte_width = (bitmap_width + 7) / 8;
  uint8_t byte = 0;
  for (uint8_t j = 0; j < bitmap_height; j++, pos_y++)
  {
    for (uint8_t i = 0; i < bitmap_width; i++)
    {
      if (i & 7)
      {
        byte <<= 1;
      }
      else
      {
        byte = bitmap[j * byte_width + i / 8];
      }
      if (byte & 0x80)
      {
        drv_ssd1306_draw_pixel(dev,
                               pos_x + i,
                               pos_y,
                               color);
      }
    }
  }
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_draw_line(drv_ssd1306_t *dev,
                               uint8_t pos_x1,
                               uint8_t pos_y1,
                               uint8_t pos_x2,
                               uint8_t pos_y2,
                               drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x1 < dev->size.width) && (pos_x2 < dev->size.width),
           DRV_SSD1306_ERROR);
  __ASSERT((pos_y1 < dev->size.height) && (pos_y2 < dev->size.height),
           DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Operation
  uint16_t delta_x = abs(pos_x2 - pos_x1);
  uint16_t delta_y = abs(pos_y2 - pos_y1);
  int8_t sign_of_x = ((pos_x1 < pos_x2) ? 1 : -1);
  int8_t sign_of_y = ((pos_y1 < pos_y2) ? 1 : -1);
  int32_t error = delta_x - delta_y;
  int32_t error_2;

  drv_ssd1306_draw_pixel(dev, pos_x2, pos_y2, color);

  while ((pos_x1 != pos_x2) || (pos_y1 != pos_y2))
  {
    drv_ssd1306_draw_pixel(dev, pos_x1, pos_y1, color);
    error_2 = error * 2;
    if (error_2 > -delta_y)
    {
      error -= delta_y;
      pos_x1 += sign_of_x;
    }
    if (error_2 < delta_x)
    {
      error += delta_x;
      pos_y1 += sign_of_y;
    }
  }
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_draw_rectangle(drv_ssd1306_t *dev,
                                    uint8_t pos_x1,
                                    uint8_t pos_y1,
                                    uint8_t pos_x2,
                                    uint8_t pos_y2,
                                    drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x1 < dev->size.width) && (pos_x2 < dev->size.width),
           DRV_SSD1306_ERROR);
  __ASSERT((pos_y1 < dev->size.height) && (pos_y2 < dev->size.height),
           DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Operation
  drv_ssd1306_draw_line(dev, pos_x1, pos_y1, pos_x2, pos_y1, color);
  drv_ssd1306_draw_line(dev, pos_x2, pos_y1, pos_x2, pos_y2, color);
  drv_ssd1306_draw_line(dev, pos_x2, pos_y2, pos_x1, pos_y2, color);
  drv_ssd1306_draw_line(dev, pos_x1, pos_y2, pos_x1, pos_y1, color);
  // Return
  return DRV_SSD1306_OK;
}

uint32_t drv_ssd1306_fill_rectangle(drv_ssd1306_t *dev,
                                    uint8_t pos_x1,
                                    uint8_t pos_y1,
                                    uint8_t pos_x2,
                                    uint8_t pos_y2,
                                    drv_ssd1306_color_t color)
{
  // Check parameters
  __ASSERT((dev != NULL), DRV_SSD1306_ERROR);
  __ASSERT((pos_x1 < dev->size.width) && (pos_x2 < dev->size.width),
           DRV_SSD1306_ERROR);
  __ASSERT((pos_y1 < dev->size.height) && (pos_y2 < dev->size.height),
           DRV_SSD1306_ERROR);
  __ASSERT((color == DRV_SSD1306_COLOR_BLACK) || (color == DRV_SSD1306_COLOR_WHITE),
           DRV_SSD1306_ERROR);
  // Operation
  uint8_t starting_x = ((pos_x1 <= pos_x2) ? pos_x1 : pos_x2);
  uint8_t ending_x = ((pos_x1 <= pos_x2) ? pos_x2 : pos_x1);
  uint8_t starting_y = ((pos_y1 <= pos_y2) ? pos_y1 : pos_y2);
  uint8_t ending_y = ((pos_y1 <= pos_y2) ? pos_y2 : pos_y1);
  for (uint8_t y = starting_y; (y <= ending_y) && (y < SSD1306_HEIGHT); y++)
  {
    for (uint8_t x = starting_x; (x <= ending_x) && (x < SSD1306_WIDTH); x++)
    {
      drv_ssd1306_draw_pixel(dev, x, y, DRV_SSD1306_COLOR_BLACK);
    }
  }
  // Return
  return DRV_SSD1306_OK;
}
/* Private definitions ----------------------------------------------- */
static uint32_t drv_ssd1306_oled_init(drv_ssd1306_t *dev)
{
  // Set display off
  drv_ssd1306_set_display(dev, DRV_SSD1306_DISPLAY_OFF);
  // Memory mode
  drv_ssd1306_write_command(dev, 0x20);
  drv_ssd1306_write_command(dev, 0x00);
  // Set Page Start Address for Page Addressing Mode, 0-7
  drv_ssd1306_write_command(dev, 0xB0);
  // Set COM Output Scan Direction
  drv_ssd1306_write_command(dev, 0xC8);
  // Set low column address
  drv_ssd1306_write_command(dev, 0x00);
  // Set high column address
  drv_ssd1306_write_command(dev, 0x10);
  // Set start line address - CHECK
  drv_ssd1306_write_command(dev, 0x40);
  // Set contrast
  drv_ssd1306_set_contrast(dev, 0xFF);
  // Set segment re-map 0 to 127 - CHECK
  drv_ssd1306_write_command(dev, 0xA1);
  // Set normal color
  drv_ssd1306_write_command(dev, 0xA6);
  // Set multiplex ratio(1 to 64) - CHECK
  drv_ssd1306_write_command(dev, 0xA8);
  drv_ssd1306_write_command(dev, 0x3F);
  // 0xA4, Output follows RAM content
  // 0xA5, Output ignores RAM content
  drv_ssd1306_write_command(dev, 0xA4);
  // Set display offset - CHECK
  drv_ssd1306_write_command(dev, 0xD3);
  drv_ssd1306_write_command(dev, 0x00);
  // Set display clock divide ratio/oscillator frequency
  drv_ssd1306_write_command(dev, 0xD5);
  // Set divide ratio
  drv_ssd1306_write_command(dev, 0xF0);
  // Set pre-charge period
  drv_ssd1306_write_command(dev, 0xD9);
  drv_ssd1306_write_command(dev, 0x22);
  // Set com pins hardware configuration - CHECK
  drv_ssd1306_write_command(dev, 0xDA);
  drv_ssd1306_write_command(dev, 0x12);
  // Set VCOMH
  drv_ssd1306_write_command(dev, 0xDB);
  // 0x20, 0.77xVcc
  drv_ssd1306_write_command(dev, 0x20);
  // Set DC-DC enable
  drv_ssd1306_write_command(dev, 0x8D);
  drv_ssd1306_write_command(dev, 0x14);
  // Set display on
  drv_ssd1306_set_display(dev, DRV_SSD1306_DISPLAY_ON);
  // Clear screen
  drv_ssd1306_fill_screen(dev, DRV_SSD1306_COLOR_BLACK);
  // Flush buffer to screen
  drv_ssd1306_update_screen(dev);
  // Return
  return DRV_SSD1306_OK;
}
static uint32_t drv_ssd1306_write_command(drv_ssd1306_t *dev, uint8_t command)
{
  uint32_t ret = DRV_SSD1306_OK;
  ret = bsp_i2c_mem_write(dev->i2c,
                          dev->address,
                          0x00,
                          1,
                          &command,
                          1,
                          HAL_MAX_DELAY);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  return DRV_SSD1306_OK;
}

static uint32_t drv_ssd1306_write_data(drv_ssd1306_t *dev, uint8_t *data, uint16_t size)
{
  uint32_t ret = DRV_SSD1306_OK;
  ret = bsp_i2c_mem_write(dev->i2c,
                          dev->address,
                          0x40,
                          1,
                          data,
                          size,
                          HAL_MAX_DELAY);
  __ASSERT((ret == DRV_SSD1306_OK), DRV_SSD1306_FAILED);
  return DRV_SSD1306_OK;
}

/* End of file -------------------------------------------------------- */
