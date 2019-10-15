/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* application includes */
#include "taskhandler.h"
#include "peripheralinit.h"


unsigned long ulRunTimeStatsClock;

int main(void)
{

	/*
	 * TODO
	 * hw setup
	 */

	/*
	 * TODO
	 * create all task
	 */
	(void)uiTaskhandler_CreateAllTasks();

	/* Start the scheduler. */
	vTaskStartScheduler();

	return 0;
}
