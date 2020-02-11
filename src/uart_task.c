/**
  ******************************************************************************
  * @file    uart_task.c
  * @author  franc
  * @version V1.0
  * @date    24 ott 2019
  * @brief   Uart task
  ******************************************************************************
*/

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "task.h"

#include <string.h>

#include "uart_task.h"
#include "uart.h"
#include "dma.h"

typedef enum
{
	e_Uart_command_val,
	e_Uart_command_max
}	t_uart_command;

const uint8_t command[e_Uart_command_max][5u] = { "c01#" };

extern __IO  uint8_t dma_uart_TX_buffer[];
extern __IO  uint8_t dma_uart_RX_buffer[];

extern __IO  uint8_t dma_uart_TX_byte;
extern __IO  uint8_t dma_uart_RX_byte;

static SemaphoreHandle_t pUart_TX_Sem;

/**
 * @brief Task for UART. It blocks on RX with a sempahore.
 * 
 * @param pvParameters 
 */
void vUartTask( void *pvParameters )
{
	static uint8_t _internal_RX_buffer[BUFFER_SIZE] = {0};
    static uint8_t _internal_TX_buffer[BUFFER_SIZE] = {0};

    static uint8_t _internal_RX_index = 0;
    static uint8_t _internal_TX_index = 0;

    const char *pStart = "Hello\n";

    BaseType_t retVal;

    pUart_TX_Sem = xSemaphoreCreateBinary();

    if (pUart_TX_Sem != NULL)
    {
    	vDMA_USART2_Set_Sem(&pUart_TX_Sem);

        //vUSART2_SendData(pStart, strlen(pStart));
        vDMA_USART2_SendData(pStart, strlen(pStart));

    	while(1)
    	{
    		retVal = xSemaphoreTake( pUart_TX_Sem, portMAX_DELAY);
    		if (retVal == pdTRUE)
    		{
				/* 
				 * What we do ?
				 */
    		}
    	}
    }


}

/**
 * @brief Returns private semaphore pointer
 * 
 * @return SemaphoreHandle_t* pointer to the private semaphore
 */
SemaphoreHandle_t * sem_UartTask_GetSemHandler(void)
{
	return &pUart_TX_Sem;
}
