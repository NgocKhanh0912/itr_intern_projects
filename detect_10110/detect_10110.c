/**
 * @file       detect_10110.c
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

/* Includes ----------------------------------------------------------- */
#include "detect_10110.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void string_detect_init(string_detect_t *str_dt)
{
  str_dt->state = STRING_DETECT_STATE_S0;
}

void string_detect_clear(string_detect_t *str_dt)
{
  str_dt->state = STRING_DETECT_STATE_S0;
}

uint8_t string_detect_mealy(string_detect_t *str_dt, uint8_t *input_arr, uint8_t size)
{
  uint8_t string_count = 0;
  uint8_t index = 0;
  while (index < size)
  {
    // Check whether input is valid or not
    CHECK(!((*input_arr != 0) && (*input_arr != 1)), DETECT_INVALID_INPUT);
    switch (str_dt->state) 
    {
      case STRING_DETECT_STATE_S0:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S0;
        break;
      case STRING_DETECT_STATE_S1:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S2;
        break;
      case STRING_DETECT_STATE_S2:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S3 : STRING_DETECT_STATE_S0;
        break;
      case STRING_DETECT_STATE_S3:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S4 : STRING_DETECT_STATE_S2;
        break;
      case STRING_DETECT_STATE_S4:
        if (*(input_arr) == 1) 
        {
          str_dt->state = STRING_DETECT_STATE_S1;
        } else 
        {
          str_dt->state = STRING_DETECT_STATE_S0;
          printf("Found at: %d \n", index - 4); // Starting index
          string_count++;
        }
        break;
    }
    input_arr++;
    index++;
  }
  string_detect_clear(str_dt);
  if (string_count) 
  {
    printf("Total string detect: %d \n", string_count);
    return DETECT_SUCCESS;
  } else 
  {
    printf("Not found!\n");
    return DETECT_FAILED;
  }
}

uint8_t string_detect_moore(string_detect_t *str_dt, uint8_t *input_arr, uint8_t size)
{
  uint8_t string_count = 0;
  uint8_t index = 0;
  while (index < size)
  {
    // Check whether input is valid or not
    CHECK(!((*input_arr != 0) && (*input_arr != 1)), DETECT_INVALID_INPUT);
    // State transition
    switch (str_dt->state) 
    {
      case STRING_DETECT_STATE_S0:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S0;
        break;
      case STRING_DETECT_STATE_S1:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S2;
        break;
      case STRING_DETECT_STATE_S2:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S3 : STRING_DETECT_STATE_S0;
        break;
      case STRING_DETECT_STATE_S3:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S4 : STRING_DETECT_STATE_S2;
        break;
      case STRING_DETECT_STATE_S4:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S5;
        break;
      case STRING_DETECT_STATE_S5:
        str_dt->state = (*(input_arr) == 1) ? STRING_DETECT_STATE_S1 : STRING_DETECT_STATE_S0;
        break;
    }
    // Output based on current state
    if (str_dt->state == STRING_DETECT_STATE_S5)
    {
      printf("Found at: %d \n", index - 4); // Starting index
      string_count++;
    }
    input_arr++;
    index++;
  }
  string_detect_clear(str_dt);
  if (string_count) 
  {
    printf("Total string detect: %d \n", string_count);
    return DETECT_SUCCESS;
  } else 
  {
    printf("Not found!\n");
    return DETECT_FAILED;
  }

}

/* Private definitions ------------------------------------------------ */
/* End of file -------------------------------------------------------- */
