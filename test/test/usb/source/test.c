#include <stdio.h>

#include "types.h"
#include "log.h"
#include "board.h"
#include "gpio.h"
#include "usb_device.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

typedef FW_BOOLEAN (* TestFunction_t)(void);

/* -------------------------------------------------------------------------- */

static FW_BOOLEAN Test_SomeCase(void)
{
  FW_BOOLEAN result = FW_TRUE;

  LOG("*** Some Case Test ***\r\n");

  return result;
}

/* --- Test Start Up Function (mandatory, called before RTOS starts) -------- */

void vTestStartUpFunction(void)
{
  LOG_ClearScreen();
  LOG("*** Start Up Test ***\r\n");
}

/* --- Test Prepare Function (mandatory, called before RTOS starts) --------- */

void vTestPrepareFunction (void)
{
  LOG("*** Prepare Test ***\r\n");
}

/* --- Helper Task Main Function (mandatory) -------------------------------- */

void vTestHelpTaskFunction(void * pvParameters)
{
  //LOG("LED Task Started\r\n");

  /* Init PB2 to OD Hi-Z - Switch-off 1k5 PullUp from USB D+ */
  GPIO_Init(USB_PUP_PORT, USB_PUP_PIN, GPIO_TYPE_OUT_OD_2MHZ, 1);

  /* Delay */
  vTaskDelay(200);

  /* Init USB. Switch-on 1k5 PullUp to USB D+ - connect USB device */
  USBD_Init();
  GPIO_Lo(USB_PUP_PORT, USB_PUP_PIN);

  vTaskDelay(5000);


  while (FW_TRUE)
  {
      //LOG("LED Hi\r\n");
      vTaskDelay(50);
      //LOG("LED Lo\r\n");
      vTaskDelay(50);
  }
  //vTaskDelete(NULL);
}

/* --- Test Cases List (mandatory) ------------------------------------------ */

const TestFunction_t gTests[] =
{
    Test_SomeCase,
};

U32 uiTestsGetCount(void)
{
    return (sizeof(gTests) / sizeof(TestFunction_t));
}

/* --- Error callback function (mandatory) ---------------------------------- */

void on_error(S32 parameter)
{
  while (FW_TRUE) {};
}

/* -------------------------------------------------------------------------- */
