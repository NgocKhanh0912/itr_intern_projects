/**
 * @file       sys_button.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       07/07/2024
 * @author     Giang Phan Truong
 *             Khanh Nguyen Ngoc
 *             Viet Hoang Xuan
 *
 * @brief      APIs definition of sys_button.h
 */
/* Includes ----------------------------------------------------------- */
#include "system/sys_button.h"
/* Private defines ---------------------------------------------------- */
#define BUTTON_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_0
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

/* Private function prototypes ---------------------------------------- */
static sys_button_status_t sys_button_init();
/* Function definitions ----------------------------------------------- */
sys_button_status_t sys_button_start()
{
  sys_button_status_t error_handler = SYS_BUTTON_STATUS_OK;

  error_handler = sys_button_init();
  __ASSERT((error_handler == SYS_BUTTON_STATUS_OK), SYS_BUTTON_STATUS_ERROR);

  return SYS_BUTTON_STATUS_OK;
}

sys_button_evt_t sys_button_single_click()
{
  return SYS_BUTTON_EVT_SINGLE_CLICK;
}

sys_button_evt_t sys_button_double_click()
{
  return SYS_BUTTON_EVT_DOUBLE_CLICK;
}

sys_button_evt_t sys_button_hold()
{
  return SYS_BUTTON_EVT_HOLD;
}

sys_button_evt_t sys_button_release()
{
  return SYS_BUTTON_EVT_RELEASE;
}

/* Private function definitions --------------------------------------- */
static sys_button_status_t sys_button_init()
{
  button_t sbutton;

  // Depends on connection button to board GPIO
  sbutton.port = BUTTON_PORT;
  sbutton.pin = BUTTON_PIN;
  sbutton.state = 0;

  button_status_t error_handler = BUTTON_STATUS_OK;
  error_handler = button_init(sbutton);
  __ASSERT((error_handler == BUTTON_STATUS_OK), SYS_BUTTON_STATUS_ERROR);

  return SYS_BUTTON_STATUS_OK;
}
/* End of file -------------------------------------------------------- */
