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

/* tasks include */
#include "taskhandler.h"
#include "taskcommon.h"
#include "ledtask.h"
#include "buttontask.h"
#include "uart_task.h"
#include "hc_sr04_task.h"

#define TOTAL_TASK 	(5u)

static TaskHandle_t * taskArray[TOTAL_TASK];

uint8_t uiTaskhandler_CreateAllTasks(void)
{
	uint8_t retVal = 0;

	vTaskcommon_InitQueue();

	xTaskCreate( vLedTask,	/* function*/
			"Led Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			3, 				/* prio */
			taskArray[0] );			/* handler */

	xTaskCreate( vButtonTask,	/* function*/
			"Button Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			2, 				/* prio */
			taskArray[1] );			/* handler */


	xTaskCreate( vUart_rx_Task,	/* function*/
			"Uart RX Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			1, 				/* prio */
			taskArray[2] );			/* handler */

	xTaskCreate( vUart_tx_Task,	/* function*/
			"Uart TX Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			1, 				/* prio */
			taskArray[3] );			/* handler */

	xTaskCreate( vHC_SR04_Task,	/* function*/
			"HC-SR04 Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			1, 				/* prio */
			taskArray[4] );			/* handler */

	return retVal;
}

