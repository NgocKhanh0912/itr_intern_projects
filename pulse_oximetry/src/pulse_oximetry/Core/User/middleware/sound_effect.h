/**
 * @file       sound_effect.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-08-02
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 * @brief      List of sound effects in frequencies.
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_MIDDLEWARE_SOUND_EFFECT_H
#define __USER_MIDDLEWARE_SOUND_EFFECT_H

/* Includes ----------------------------------------------------------- */
#include "music_notes.h"
#include "stdint.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

typedef struct
{
  uint32_t note;
  uint32_t duration;
} sound_effect_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __USER_MIDDLEWARE_SOUND_EFFECT_H

/* End of file -------------------------------------------------------- */
