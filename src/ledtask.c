/*
 * ledtask.c
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */



/* Scheduler includes. */
//#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"

#include "ledtask.h"
#include "ledhardware.h"

void vLedTask( void *pvParameters )
{
	while(1)
	{
		vLedHardware_Toggle();
		vTaskDelay( pdMS_TO_TICKS( 100 ) );
	}
}
