/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* */
#include "stm32f4xx.h"

/* application includes */
#include "taskhandler.h"
#include "peripheralinit.h"

unsigned long ulRunTimeStatsClock;

int main(void)
{
	/* init peripheral*/
	(void)uiPeripheralInit_Init();

	/* init task */
	(void)uiTaskhandler_CreateAllTasks();

	/* Start the scheduler. */
	vTaskStartScheduler();

  while(1)
  {

  }

	return 0;
}
