/*
 *  @file  : uart_task.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 feb 2020
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

static SemaphoreHandle_t gUart_TX_Button;

/**
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

    gUart_TX_Button = xSemaphoreCreateBinary();



    if (gUart_TX_Button != NULL)
    {
    	UART_DMA_set_sem(&gUart_TX_Button);

        //UART_fv_SendData(pStart, strlen(pStart));
        UART_DMA_SendData(pStart, strlen(pStart));

    	while(1)
    	{
    		retVal = xSemaphoreTake( gUart_TX_Button, portMAX_DELAY);
    		if (retVal == pdTRUE)
    		{

    		}
    	}
    }


}

/**
 *
 * @return
 */
SemaphoreHandle_t * sem_UartTask_GetSemHandler(void)
{
	return &gUart_TX_Button;
}
