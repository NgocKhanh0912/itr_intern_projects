/**
 * @file       button.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       06/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs definition of button.h
 */
/* Includes ----------------------------------------------------------- */
#include "drv/button.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
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

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static button_t button;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
button_status_t button_init(button_t sys_button)
{
  __ASSERT((sys_button.port != NULL) ||
          (sys_button.pin >= 0) ||
          (sys_button.pin <= 15), BUTTON_STATUS_ERROR);

  button = sys_button;

  return BUTTON_STATUS_OK;
}

button_status_t button_get_state(GPIO_PinState *button_state)
{
  __ASSERT((button_state != NULL), BUTTON_STATUS_ERROR);

  __ASSERT((button.port != NULL) ||
          (button.pin >= 0) ||
          (button.pin <= 15), BUTTON_STATUS_ERROR);
  button.state = HAL_GPIO_ReadPin(button.port, button.pin);
  *button_state = button.state;

  return BUTTON_STATUS_OK;
}

uint32_t button_get_tick()
{
  return HAL_GetTick();
}
/* Private function definitions --------------------------------------- */

/* End of file -------------------------------------------------------- */
