/*
 * ledtask.c
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */



/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "ledtask.h"
#include "taskcommon.h"
#include "ledhardware.h"

const uint16_t delayTask[] = {25, 50, 75, 100, 150, 200, 300, 500};

void vLedTask( void *pvParameters )
{
	QueueHandle_t* ptaskcommon_Queue;
	sTaskCommon element = {.senderId = 0, .data = 0};
	uint8_t index = 0;
	const uint8_t maxIndex = sizeof(delayTask)/sizeof(uint16_t);

	ptaskcommon_Queue = vTaskcommon_GetQueue();

	while(1)
	{
		if( xQueueReceive( *ptaskcommon_Queue,
				&element,
				0) == pdTRUE)
		{
			index = (index + 1)%maxIndex;
		}

		vLedHardware_Toggle();
		vTaskDelay( pdMS_TO_TICKS( delayTask[index] ) );
	}
}
