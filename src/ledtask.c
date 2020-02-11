/**
  ******************************************************************************
  * @file    ledtask.c
  * @author  franc
  * @version V1.0
  * @date    15 ott 2019
  * @brief   Led task
  ******************************************************************************
*/


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "ledtask.h"
#include "taskcommon.h"
#include "ledhardware.h"

const uint16_t delayTask[] = {25, 50, 75, 100, 150, 200, 300, 500};

/**
 * @brief Led task. When receives something in the queue, change the period of the led
 * 
 * @param pvParameters 
 */
void vLedTask( void *pvParameters )
{
	QueueHandle_t* ptaskcommon_Queue;
	sTaskCommon element = {.senderId = 0, .data = 0};
	uint8_t index = 0;
	const uint8_t maxIndex = sizeof(delayTask)/sizeof(uint16_t);

	ptaskcommon_Queue = vTaskcommon_GetQueue();

	if (ptaskcommon_Queue != NULL)
	{
		while(1)
		{
			if( xQueueReceive( *ptaskcommon_Queue,	/* if element received */
					&element,
					0) == pdTRUE)	/* 0, do not block */
			{
				index = (index + 1)%maxIndex;		/* change sleep time */
			}

			vLedHardware_Toggle();								/* toggles the LED */
			vTaskDelay( pdMS_TO_TICKS( delayTask[index] ) );	/* sleep */
		}
	}

}
