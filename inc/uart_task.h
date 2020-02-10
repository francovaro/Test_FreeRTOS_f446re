/*
 *  @file  : uart_task.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 feb 2020
 */

#ifndef INC_UART_TASK_H_
#define INC_UART_TASK_H_

#include "semphr.h"

extern void vUartTask( void *pvParameters );
extern SemaphoreHandle_t * sem_UartTask_GetSemHandler(void);

#endif /* INC_UART_TASK_H_ */
