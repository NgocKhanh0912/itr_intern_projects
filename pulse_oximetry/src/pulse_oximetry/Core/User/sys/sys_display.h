/**
 * @file       sys_display.h
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
#ifndef __USER_SYS_DISPLAY_H
#define __USER_SYS_DISPLAY_H

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "drv_ssd1306.h"
#include "cbuffer.h"
/* Public defines ----------------------------------------------------- */
#define SSD1306_INCLUDE_FONT_6x8 true
/* Public enumerate/structure ----------------------------------------- */
enum sys_display_status_t
{
  SYS_DISPLAY_ERROR = 0xFFFFFFFF,
  SYS_DISPLAY_FAILED = 0x7FFFFFFF,
  SYS_DISPLAY_OK = 0x3FFFFFFF
};

typedef struct
{
  drv_ssd1306_t screen;
  uint8_t heart_rate;
  uint8_t *threshold_buf;
} sys_display_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief  Initialize the display and start UI
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 * @param[in]     i2c      pointer to I2C handler
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_init(sys_display_t *display, bsp_i2c_handle_t *i2c, uint8_t *dev_buffer);

/**
 * @brief  Update the heart rate on the display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 * @param[in]     heart_rate      measured heart rate
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_update_heart_rate(sys_display_t *display, uint8_t heart_rate);

/**
 * @brief  Graph the PPG signal on the display
 *
 * @param[in]     display         pointer to sys_display_t structure for manage the display in the system
 * @param[in]     signal_buf      amount of PPG data needed to graph
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_update_ppg_signal(sys_display_t *display, cbuffer_t *signal_buf);

/**
 * @brief  Update new threshold
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 * @param[in]     threshold      pointer to array contains upper and lower threshold
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_update_threshold(sys_display_t *display, uint8_t *threshold);

/**
 * @brief  Show the notification on the display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 * @param[in]     msg      pointer to the message array
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_show_noti(sys_display_t *display, char *msg);

/**
 * @brief  Clear all the contents of display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_clear_all(sys_display_t *display);

/**
 * @brief  Turn off the OLED display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_sleep(sys_display_t *display);

/**
 * @brief  Turn on the OLED display
 *
 * @param[in]     display  pointer to sys_display_t structure for manage the display in the system
 *
 * @return
 *  - (0xFFFFFFFF): Error
 *  - (0x7FFFFFFF): Failed
 *  - (0x3FFFFFFF) : Success
 */
uint32_t sys_display_wakeup(sys_display_t *display);

#endif // __USER_SYS_DISPLAY_H

/* End of file -------------------------------------------------------- */
