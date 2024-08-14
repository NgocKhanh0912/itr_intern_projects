/**
 * @file       detect_10110.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2024-07-03
 * @author     Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *             Giang Phan Truong
 *
 * @brief      Detect '10110' in a bit array
 *
 * @note       none
 * @example    none
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DETECT_10110_H
#define __DETECT_10110_H

/* Includes ----------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <conio.h>

/* Public defines ----------------------------------------------------- */
#define DETECT_SUCCESS 0x0000
#define DETECT_FAILED 0x0001
#define DETECT_INVALID_INPUT 0x0002

/* Public enumerate/structure ----------------------------------------- */
enum states 
{
  STRING_DETECT_STATE_S0 = 0, // Wait for '1'
  STRING_DETECT_STATE_S1 = 1, // Received '1' state
  STRING_DETECT_STATE_S2 = 2, // Received '10' state
  STRING_DETECT_STATE_S3 = 3, // Received '101' state
  STRING_DETECT_STATE_S4 = 4, // Received '1011' state
  STRING_DETECT_STATE_S5 = 5  // Received '10110' state
};

typedef struct string_detect 
{
  enum states state;
} string_detect_t;

/* Public macros ------------------------------------------------------ */
#define CHECK(condition, ret) \
  if (!condition) {            \
    printf("Error code: %d \n", ret); \
    return ret;               \
  } while(0)

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
void string_detect_init(string_detect_t *str_dt);
void string_detect_clear(string_detect_t *str_dt);
uint8_t string_detect_mealy(string_detect_t *str_dt, uint8_t *input_arr, uint8_t size);
uint8_t string_detect_moore(string_detect_t *str_dt, uint8_t *input_arr, uint8_t size);

#endif // __DETECT_10110_H
/* End of file -------------------------------------------------------- */