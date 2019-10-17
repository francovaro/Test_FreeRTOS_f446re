/*
 * taskhandler.c
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "taskhandler.h"
#include "ledtask.h"

uint8_t uiTaskhandler_CreateAllTasks(void)
{
	uint8_t retVal = 0;

	xTaskCreate( vLedTask,	/* function*/
			"Led Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			1, 				/* prio */
			NULL );			/* handler */

	return retVal;
}

