/**
 * @file       main.c
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
int main()
{
  uint8_t bit_array_0[10] = {1, 0, 15, 20, 25};
  uint8_t bit_array_1[10] = {0, 1, 0, 1, 1, 0, 0, 1, 1, 1};
  uint8_t bit_array_2[10] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 1};
  string_detect_t str_dt;
  string_detect_init(&str_dt);
  // Mealy
  string_detect_mealy(&str_dt, bit_array_0, 5);
  string_detect_mealy(&str_dt, bit_array_1, 10);
  string_detect_mealy(&str_dt, bit_array_2, 10);
  // Moore
  string_detect_moore(&str_dt, bit_array_0, 5);
  string_detect_moore(&str_dt ,bit_array_1, 10);
  string_detect_moore(&str_dt ,bit_array_2, 10);
  return 0;
}

/* Private definitions ------------------------------------------------ */
/* End of file -------------------------------------------------------- */