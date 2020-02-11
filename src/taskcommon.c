/**
  ******************************************************************************
  * @file    taskcommon.c
  * @author  franc
  * @version V1.0
  * @date    26 ott 2019
  * @brief   Common task stuff
  ******************************************************************************
*/
#include "taskcommon.h"

/**
 * @brief Create the common queue
 */
void vTaskcommon_InitQueue(void)
{
	taskcommon_Queue = xQueueCreate(TASKCOMMON_QUEUE_SIZE, sizeof(sTaskCommon) );
}

/**
 * @brief Getter for task queue
 * @return QueueHandle_t* the pointer to the queue
 */
QueueHandle_t* vTaskcommon_GetQueue(void)
{
	return &taskcommon_Queue;
}
