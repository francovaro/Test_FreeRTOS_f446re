/**
  ******************************************************************************
  * @file    taskcommon.h
  * @author  franc
  * @version V1.0
  * @date    26 ott 2019
  * @brief   Common task stuff
  ******************************************************************************
*/

#ifndef TASKCOMMON_H_
#define TASKCOMMON_H_

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "queue.h"

#include <stdint.h>

#define TASKCOMMON_QUEUE_SIZE	(5u)

/**
 * @brief struct
 * 
 */
typedef struct
{
	uint8_t senderId;
	uint8_t data;
} sTaskCommon;

QueueHandle_t taskcommon_Queue;

extern void vTaskcommon_InitQueue(void);
extern QueueHandle_t* vTaskcommon_GetQueue(void);

#endif /* TASKCOMMON_H_ */
