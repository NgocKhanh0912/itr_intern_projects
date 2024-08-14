/**
 * @file       drv_ssd1306.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-07-28
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      None
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_DRV_SSD1306_H
#define __USER_DRV_SSD1306_H

/* Includes ----------------------------------------------------------- */
#include "bsp_i2c.h"
#include <stdbool.h>
#include "ssd1306_fonts.h"
/* Public defines ----------------------------------------------------- */
#define SSD1306_I2C_ADDRESS (0x3C << 1)
#define SSD1306_WIDTH (128)
#define SSD1306_HEIGHT (64)
/* Public enumerate/structure ----------------------------------------- */
enum drv_ssd1306_status_t
{
  DRV_SSD1306_ERROR = 0xFFFFFFFF,
  DRV_SSD1306_FAILED = 0x7FFFFFFF,
  DRV_SSD1306_OK = 0x3FFFFFFF
};

typedef enum
{
  DRV_SSD1306_DISPLAY_OFF = 0,
  DRV_SSD1306_DISPLAY_ON
} drv_ssd1306_display_t;

typedef struct
{
  uint8_t width;
  uint8_t height;
} drv_ssd1306_size_t;

typedef struct
{
  uint8_t x;
  uint8_t y;
} drv_ssd1306_cursor_position_t;
typedef struct
{
  bsp_i2c_handle_t *i2c;
  uint16_t address;
  uint8_t *buffer;
  drv_ssd1306_size_t size;
  drv_ssd1306_cursor_position_t cursor;
  bool active;
} drv_ssd1306_t;

typedef enum
{
  DRV_SSD1306_COLOR_BLACK = 0x00, // Turn off all pixel
  DRV_SSD1306_COLOR_WHITE = 0x01  // Turn on all pixel, color depends on device
} drv_ssd1306_color_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Initialize the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     dev_i2c         Pointer to device I2C_HandleTypeDef
 * @param[in]     dev_address     Device address. Shift left 1 bit before calling this API
 * @param[in]     dev_buffer      Buffer contains the screen data.
 * @param[in]     dev_width,dev_height  Display size of the display
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_init(drv_ssd1306_t *dev,
                          bsp_i2c_handle_t *dev_i2c,
                          uint16_t dev_address,
                          uint8_t *dev_buffer,
                          uint8_t dev_width,
                          uint8_t dev_height);

/**
 * @brief         Set state of the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     state           The state of display: ON or OFF
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_set_display(drv_ssd1306_t *dev, drv_ssd1306_display_t state);

/**
 * @brief         Set the cursor on the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     pos_x, pos_y    Position of the pixel on the display by vertical
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_set_cursor(drv_ssd1306_t *dev, uint8_t pos_x, uint8_t pos_y);

/**
 * @brief         Set the contrast on the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     value           The contrast level of the screen
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_set_contrast(drv_ssd1306_t *dev, uint8_t value);

/**
 * @brief         Initialize the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     color           Colors list in drv_ssd1306_color_t
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_fill_screen(drv_ssd1306_t *dev, uint32_t color);

/**
 * @brief         Set the pixel on the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     pos_x, pos_y    Position of pixel on the device
 * @param[in]     color           Colors list in drv_ssd1306_color_t
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_draw_pixel(drv_ssd1306_t *dev, uint8_t pos_x, uint8_t pos_y, drv_ssd1306_color_t color);

/**
 * @brief         Write the character on the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     ch              The character that want to display
 * @param[in]     font            The defined font of device
 * @param[in]     color           Colors list in drv_ssd1306_color_t
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_write_char(drv_ssd1306_t *dev, char ch, ssd1306_font_t font, drv_ssd1306_color_t color);

/**
 * @brief         Write the message on the SSD1306 OLED screen
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     str             The message that want to display
 * @param[in]     font            The defined font of device
 * @param[in]     color           Colors list in drv_ssd1306_color_t
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_write_string(drv_ssd1306_t *dev, char *str, ssd1306_font_t font, drv_ssd1306_color_t color);

/**
 * @brief         Update screen on the SSD1306 OLED
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_update_screen(drv_ssd1306_t *dev);

/**
 * @brief         Draw bitmap on OLED
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     bitmap          Pointer to bitmap array to draw
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_draw_bitmap(drv_ssd1306_t *dev,
                                 uint8_t pos_x,
                                 uint8_t pos_y,
                                 const uint8_t *bitmap,
                                 uint8_t bitmap_width,
                                 uint8_t bitmap_height,
                                 drv_ssd1306_color_t color);

/**
 * @brief         Draw a line on OLED
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     pos_x1, pos_y1  Starting point of the line
 * @param[in]     pos_x2, pos_y2  Ending point of the line
 * @param[in]     color           Color of the line
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_draw_line(drv_ssd1306_t *dev,
                               uint8_t pos_x1,
                               uint8_t pos_y1,
                               uint8_t pos_x2,
                               uint8_t pos_y2,
                               drv_ssd1306_color_t color);

/**
 * @brief         Draw a rectangle on OLED
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t struct to manage device
 * @param[in]     pos_x1, pos_y1  Starting point
 * @param[in]     pos_x2, pos_y2  Ending point
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_draw_rectangle(drv_ssd1306_t *dev,
                                    uint8_t pos_x1,
                                    uint8_t pos_y1,
                                    uint8_t pos_x2,
                                    uint8_t pos_y2,
                                    drv_ssd1306_color_t color);

/**
 * @brief         Fill a rectangle with selected color
 *
 * @param[in]     dev             Pointer to drv_ssd1306_t to manage device
 * @param[in]     pos_x1, pox_y1  Starting point
 * @param[in]     pos_x2, pos_y2  Ending point
 * @param[in]     color           Color to fill the rectangle
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t drv_ssd1306_fill_rectangle(drv_ssd1306_t *dev,
                                    uint8_t pos_x1,
                                    uint8_t pos_y1,
                                    uint8_t pos_x2,
                                    uint8_t pos_y2,
                                    drv_ssd1306_color_t color);
#endif // __USER_DRV_SSD1306_H

/* End of file -------------------------------------------------------- */
