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

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "queue.h"

#include "semphr.h"

#define UART_STRING_QUEUE_LEN	(15u)
#define UART_TASK_QUEUE_SIZE	(5u)

/**
 * @brief struct
 *
 */
typedef struct
{
	uint8_t senderId;
	char 	text[UART_STRING_QUEUE_LEN];
	uint8_t nr_byte;
} sUartTask_Queue;

extern void vUart_rx_Task( void *pvParameters );
extern void vUart_tx_Task( void *pvParameters );
extern SemaphoreHandle_t * sem_UartTask_GetSemHandler( void );
extern void vUart_task_init(void);
extern QueueHandle_t* UartTask_GetQueue(void);

#endif /* INC_UART_TASK_H_ */
