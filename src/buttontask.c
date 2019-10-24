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

void vButtonTask( void *pvParameters )
{
	while(1)
	{
		if (gButtonHwPressed == SET)
		{
			gButtonHwPressed = RESET;
		}
		vTaskDelay( pdMS_TO_TICKS( 200 ) );
		/*
		 *
		 */
	}
}
