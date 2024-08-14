/**
 * @file       common.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       10/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      Common-used macros
 *
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef USER_COMMON_COMMON_H_
#define USER_COMMON_COMMON_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */
#ifdef DEBUG
#define __ASSERT(_EXPR_, _RET_VAL_) \
  do                                \
  {                                 \
    if (!(_EXPR_))                  \
      return _RET_VAL_;             \
  } while (0)
#else
#define __ASSERT(_EXPR_, _RET_VAL_) ((void)0)
#endif

#define __CALLBACK(_CB_FUNC_, ...) \
  do                               \
  {                                \
    if ((_CB_FUNC_) != NULL)       \
      _CB_FUNC_(__VA_ARGS__);      \
  } while (0)

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */


#endif /* USER_COMMON_COMMON_H_ */
