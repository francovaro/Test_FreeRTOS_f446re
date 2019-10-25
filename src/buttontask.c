/**
  ******************************************************************************
  * @file    buttontask.c
  * @author  Francesco Varani
  * @version V1.0
  * @date    24 ott 2019
  * @brief   Task button stuff.
  ******************************************************************************
*/

#include "FreeRTOS.h"
#include "task.h"


#include "buttontask.h"
//#include "buttonhardware.h"

extern volatile uint8_t gButtonHwPressed;
static SemaphoreHandle_t gSemButton;

void vButtonTask( void *pvParameters )
{
	gSemButton = xSemaphoreCreateBinary();
	while(1)
	{
		BaseType_t retVal;
		retVal = xSemaphoreTake( gSemButton, portMAX_DELAY);
		if (retVal == pdTRUE)
		{
			if (gButtonHwPressed == SET)
			{
				gButtonHwPressed = RESET;
			}
		}
		else
		{
			// vTaskDelay( pdMS_TO_TICKS( 250 ) );
		}
	}
}

SemaphoreHandle_t * sem_ButtonTask_GetSemHandler(void)
{
	return &gSemButton;
}
