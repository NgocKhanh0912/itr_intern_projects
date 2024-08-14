/**
 * @file       drv_ssd1306_fonts.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.1
 * @date       2024-08-01
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_SSD1306_FONTS_H
#define __DRV_SSD1306_FONTS_H

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
/* Public defines ----------------------------------------------------- */
#define SSD1306_INCLUDE_FONT_6x8 true
/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  const uint8_t width;
  const uint8_t height;
  const uint16_t *const data_font;
  const uint8_t *const char_width;
} ssd1306_font_t;
/* Public macros ------------------------------------------------------ */
#ifdef SSD1306_INCLUDE_FONT_6x8
extern const ssd1306_font_t Font_6x8;
#endif
#ifdef SSD1306_INCLUDE_FONT_7x10
extern const ssd1306_font_t Font_7x10;
#endif
#ifdef SSD1306_INCLUDE_FONT_11x18
extern const ssd1306_font_t Font_11x18;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x26
extern const ssd1306_font_t Font_16x26;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x24
extern const ssd1306_font_t Font_16x24;
#endif
#ifdef SSD1306_INCLUDE_FONT_16x15
/** Generated Roboto Thin 15
 * @copyright Google https://github.com/googlefonts/roboto
 * @license This font is licensed under the Apache License, Version 2.0.
 */
extern const ssd1306_font_t Font_16x15;
#endif
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __DRV_SSD1306_FONTS_H

/* End of file -------------------------------------------------------- */
