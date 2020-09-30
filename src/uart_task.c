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
#include "inc\lib_uart.h"
#include "stddef.h"
#include "dma.h"

typedef enum
{
	e_Uart_command_val,
	e_Uart_command_max
}	t_uart_command;

const uint8_t command[e_Uart_command_max][5u] = { "c01#" };

static SemaphoreHandle_t pUart_TX_Sem;

/**
 * @brief Task for UART. It blocks on RX with a sempahore.
 * 
 * @param pvParameters 
 */
void vUartTask( void *pvParameters )
{
	static int8_t _internal_RX_buffer[BUFFER_SIZE] = {0};
    static int8_t _internal_TX_buffer[BUFFER_SIZE] = {0};

    static uint8_t _internal_RX_index = 0;
    static uint8_t _internal_TX_index = 0;

    int8_t pStart[] = "Hello\n";

    BaseType_t retVal;

    pUart_TX_Sem = xSemaphoreCreateBinary();

    if (pUart_TX_Sem != NULL)
    {
    	vDMA_USART2_Set_Sem(&pUart_TX_Sem);

    	UART_lib_sendData(pStart, strlen(pStart));

    	while(1)
    	{
    		retVal = xSemaphoreTake( pUart_TX_Sem, portMAX_DELAY);
    		if (retVal == pdTRUE)
    		{
				/* 
				 * What we do ?
				 */
    			_internal_RX_index = uiDMA_USART2_Get_Index();
    			vDMA_USART2_Get_Buffer(_internal_RX_buffer, _internal_RX_index);

    			UART_lib_sendData(_internal_RX_buffer, _internal_RX_index);

    			vDMA_USART2_Clr_Index();
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

void USART2_IRQHandler(void)
{
	volatile uint32_t tmp;
	/* */
	if( USART_GetITStatus(USART2, USART_IT_IDLE) == SET)
	{
		tmp = USART2->SR;
		tmp = USART2->DR;
		(void)tmp;

		DMA1_Stream5->CR &= ~DMA_SxCR_EN;            /* Stop DMA transfer - TC is triggered  */
		//vDMA_USART2_signal_idle();
	}
}
