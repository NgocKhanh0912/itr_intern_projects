/**
 * @file       sys_led.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Khanh Nguyen Ngoc
 *             Giang Phan Truong
 *             Viet Hoang Xuan
 *
 * @brief      Control LEDs according to each states
 *
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "system/sys_led.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void sys_led_start()
{
	led_init();
}

void set_led_for_state_idle()
{
  for (uint8_t i = LED1_PB3_RED; i <= LED3_PB7_BLUE; i++)
  {
	  led_clear(i);
  }
}

void set_led_for_state_1(led_num_t led_num)
{
  switch(led_num)
  {
  case LED1_PB3_RED:
	  led_clear(LED2_PB5_GREEN);
	  led_clear(LED3_PB7_BLUE);
	  break;
  case LED2_PB5_GREEN:
	  led_clear(LED1_PB3_RED);
	  led_clear(LED3_PB7_BLUE);
	  break;
  case LED3_PB7_BLUE:
	  led_clear(LED1_PB3_RED);
	  led_clear(LED2_PB5_GREEN);
	  break;
  default:
	  set_led_for_state_idle();
	  break;
  }
  led_set(led_num);
}

void set_led_for_state_2(led_num_t led_num_1, led_num_t led_num_2)
{
  switch(led_num_1)
  {
  case LED1_PB3_RED:
	  if (led_num_2 == LED2_PB5_GREEN)
		  led_clear(LED3_PB7_BLUE);
	  if (led_num_2 == LED3_PB7_BLUE)
		  led_clear(LED2_PB5_GREEN);
	  break;
  case LED2_PB5_GREEN:
	  if (led_num_2 == LED1_PB3_RED)
		  led_clear(LED3_PB7_BLUE);
	  if (led_num_2 == LED3_PB7_BLUE)
		  led_clear(LED1_PB3_RED);
	  break;
  case LED3_PB7_BLUE:
	  if (led_num_2 == LED1_PB3_RED)
		  led_clear(LED2_PB5_GREEN);
	  if (led_num_2 == LED2_PB5_GREEN)
		  led_clear(LED1_PB3_RED);
	  break;
  default:
	  set_led_for_state_idle();
	  break;
  }
  led_set(led_num_1);
  led_set(led_num_2);
}

void set_led_for_state_3()
{
	for (uint16_t i = LED1_PB3_RED; i <= LED3_PB7_BLUE; i++)
	{
		  led_set(i);
	}
}

/* End of file -------------------------------------------------------- */
