/**
 * @file       list_of_sound_effects.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    v1.0.0
 * @date       2024-08-03
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      List of sound effects for buzzer
 *
 * @note
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __USER_MIDDLEWARE_LIST_OF_SOUND_EFFECTS_H
#define __USER_MIDDLEWARE_LIST_OF_SOUND_EFFECTS_H

/* Includes ----------------------------------------------------------- */
#include "sound_effect.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

sound_effect_t win_11_startup[] =
    {
        {NOTE_FS5, 50},
        {NOTE_CS6, 100},
        {NOTE_GS7, 200},
        {NOTE_C5, 500}};

sound_effect_t system_alert[] =
    {
        {NOTE_AS7, 20}};

/* Public function prototypes ----------------------------------------- */

#endif // __USER_MIDDLEWARE_LIST_OF_SOUND_EFFECTS_H

/* End of file -------------------------------------------------------- */
