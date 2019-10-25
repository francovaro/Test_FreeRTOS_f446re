/**
  ******************************************************************************
  * @file    buttontask.c
  * @author  Francesco Varani
  * @version V1.0
  * @date    24 ott 2019
  * @brief   Task button stuff.
  ******************************************************************************
*/

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "task.h"

/* own task include */
#include "buttontask.h"
#include "taskcommon.h"


extern volatile uint8_t gButtonHwPressed;
static SemaphoreHandle_t gSemButton;

void vButtonTask( void *pvParameters )
{
	sTaskCommon element = {.senderId = 0, .data = 0};
	QueueHandle_t* ptaskcommon_Queue;

	gSemButton = xSemaphoreCreateBinary();
	ptaskcommon_Queue = vTaskcommon_GetQueue();

	while(1)
	{
		BaseType_t retVal;
		retVal = xSemaphoreTake( gSemButton, portMAX_DELAY);
		if (retVal == pdTRUE)
		{
			if (gButtonHwPressed == SET)
			{
				gButtonHwPressed = RESET;
				retVal =  xQueueSendToBack(*ptaskcommon_Queue , &element, 0);
			}
		}
		else
		{

		}
	}
}

SemaphoreHandle_t * sem_ButtonTask_GetSemHandler(void)
{
	return &gSemButton;
}
