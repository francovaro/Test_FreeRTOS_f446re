/**
  ******************************************************************************
  * @file    dma.c.c
  * @author  Francesco Varani
  * @version V1.0
  * @date    10 feb 2020
  * @brief   Task button stuff.
  ******************************************************************************
*/

#include "dma.h"
#include "task.h"
#include "uart_task.h"
#include "string.h"

#define TX_BUFFER_SIZE	100
#define RX_BUFFER_SIZE	100

static SemaphoreHandle_t *pDMA_Uart_TX_Sem;
volatile static int8_t dma_uart_TX_buffer[TX_BUFFER_SIZE] = {0};
volatile static int8_t dma_uart_RX_buffer[RX_BUFFER_SIZE] = {0};	/* this acts only as the receiveing buffer */

static int8_t dma_local_read_buffer[BUFFER_SIZE];

volatile static uint8_t dma_uart_TX_byte;
volatile static uint16_t dma_uart_RX_byte;

static void vDMA_UART_NVIC_Configuration(uint8_t dma_channel);

/**
 * @brief 
 * 
 */
void vDMA_USART2_Configuration( BaseType_t dma_tx, BaseType_t dma_rx )
{
	DMA_InitTypeDef DMA_InitStructure;

	dma_uart_TX_byte   = 0;
	dma_uart_RX_byte = 0;

	pDMA_Uart_TX_Sem = sem_UartTask_GetSemHandler();

	//if (*pDMA_Uart_TX_Sem != NULL)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

		DMA_DeInit(DMA1_Stream5);

		if (dma_rx == pdTRUE)
		{
			/* UART2_TX DMA1_Stream5 channel4*/

			DMA_StructInit(&DMA_InitStructure);

			DMA_InitStructure.DMA_Channel = DMA_Channel_4;

			DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
			DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_RX_buffer[0];

			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
			DMA_InitStructure.DMA_BufferSize = RX_BUFFER_SIZE;
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
			DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
			DMA_InitStructure.DMA_Priority = DMA_Priority_High;
			DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
			DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;		/* half full ? */
			DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
			DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

			DMA_Init(DMA1_Stream5, &DMA_InitStructure);

			vDMA_UART_NVIC_Configuration(DMA1_Stream5_IRQn);
			DMA_ITConfig(DMA1_Stream5, DMA_IT_TC | DMA_IT_HT,  ENABLE);

			/* DMA1_Stream5 enable */
			//DMA_Cmd(DMA1_Stream5, ENABLE);
			DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
		}

		DMA_DeInit(DMA1_Stream6);
		if (dma_tx == pdTRUE)
		{
			/* UART2_TX DMA1_Stream6 channel4*/
			DMA_StructInit(&DMA_InitStructure);
			DMA_InitStructure.DMA_Channel = DMA_Channel_4;
			DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
			DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_TX_buffer[0];
			DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
			DMA_InitStructure.DMA_BufferSize = TX_BUFFER_SIZE;
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
			DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
			DMA_InitStructure.DMA_Priority = DMA_Priority_High;
			DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
			DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
			DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
			DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
			DMA_Init(DMA1_Stream6, &DMA_InitStructure);

			DMA_Cmd(DMA1_Stream6, ENABLE);
			vDMA_UART_NVIC_Configuration(DMA1_Stream6_IRQn);

			/* DMA1_Stream6 enable */
			DMA_ITConfig(DMA1_Stream6, DMA_IT_TC,  ENABLE);			/* transfer complete  */
		}
	}
}

/**
 * @brief DMA1_Stream5 handles RX of UART2
 */
void DMA1_Stream5_IRQHandler(void)
{
	//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#if 0
	 if(DMA1 -> HISR & (DMA_HISR_HTIF5))
	 {
		DMA1 -> HIFCR |= DMA_HISR_HTIF5;
		if (*pDMA_Uart_TX_Sem != NULL)
		{
			dma_uart_RX_byte++;
			xSemaphoreGiveFromISR( *pDMA_Uart_TX_Sem, &xHigherPriorityTaskWoken);
		}
	}
	 else
#endif
	 if (DMA1 -> HISR & (DMA_HISR_TCIF5))
	 {
		DMA1 -> HIFCR |= DMA_HISR_TCIF5;
		if (*pDMA_Uart_TX_Sem != NULL)
		{
			// DMA1_Stream5->M0AR = (uint32_t)&dma_uart_RX_buffer_1[dma_uart_RX_byte_1];
			vDMA_USART2_signal_idle();
		}
	}
	else if (DMA1 -> HISR & (DMA_HISR_HTIF5))
	{
		DMA1 -> HIFCR |= DMA_HISR_HTIF5;
		if (*pDMA_Uart_TX_Sem != NULL)
		{
			vDMA_USART2_signal_idle();
		}
	}
	//portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/**
 * @brief DMA1_Stream6 handles TX of UART2
 */
void DMA1_Stream6_IRQHandler(void)
{
	if(DMA1 -> HISR & (DMA_HISR_TCIF6))
	DMA1 -> HIFCR |= DMA_HISR_TCIF6;
	while(!(USART2->SR & USART_SR_TC));	/* */
	dma_uart_TX_byte++;
}

/**
 * 
 * @param dma_channel
 */
static void vDMA_UART_NVIC_Configuration(uint8_t dma_channel)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = dma_channel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 
 * 
 * @param pString 
 * @param n_byte 
 */
void vDMA_USART2_SendData(int8_t* pString, uint8_t n_byte)
{
	uint8_t 	i;
	uint32_t 	primask;

	for (i = 0 ; i < n_byte ; i++)
	{
		dma_uart_TX_buffer[i] = pString[i];
	}
    primask = __get_PRIMASK();
    __disable_irq();

    /* Prepare DMA for next transfer */
    /* Important! DMA stream won't start if all flags are not cleared first */
    DMA1->HIFCR = DMA_FLAG_FEIF6 | DMA_FLAG_DMEIF6 | DMA_FLAG_TEIF6 | DMA_FLAG_HTIF6 | DMA_FLAG_TCIF6;
    DMA1_Stream6->M0AR = (uint32_t)dma_uart_TX_buffer;   /* Set memory address for DMA again */
    DMA1_Stream6->NDTR = n_byte;    /* Set number of bytes to send */
    DMA1_Stream6->CR |= DMA_SxCR_EN;            /* Start DMA transfer */

	__set_PRIMASK(primask);
}

/**
 * @brief 
 * 
 * @param pSem 
 */
void vDMA_USART2_Set_Sem(SemaphoreHandle_t *pSem)
{
	pDMA_Uart_TX_Sem = pSem;
}

/**
 *
 */
void vDMA_USART2_Clr_Index(void)
{
//	DMA1_Stream5->CR &= ~DMA_SxCR_EN;            /* Start DMA transfer */
	dma_uart_RX_byte = 0;
	memset(dma_uart_RX_buffer, "0", BUFFER_SIZE);
//	DMA1_Stream5->M0AR = (uint32_t)&dma_uart_RX_buffer[0];
//	DMA1_Stream5->NDTR = RX_BUFFER_SIZE;
//
//	DMA1 -> HIFCR |= DMA_HISR_TCIF5;
//	DMA1 -> HIFCR |= DMA_HISR_HTIF5;
//
//	DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
}

/**
 *
 * @return
 */
uint8_t uiDMA_USART2_Get_Index(void)
{
	uint32_t	configMem 	= DMA_GetCurrentMemoryTarget(DMA1_Stream5);
	uint8_t		retval  	= 0;

	switch (configMem)
	{
		case DMA_Memory_0:
		{
			retval = dma_uart_RX_byte;
		}
		break;
#if 0
		case DMA_Memory_1:
		{
			retval = dma_uart_RX_byte_2;
		}
		break;
#endif
	}

	return retval;
}

/**
 *
 * @param buf
 * @param nrBytes
 */
void vDMA_USART2_Get_Buffer(int8_t *buf, uint8_t nrBytes)
{
	uint8_t i;
	for ( i=0; i< nrBytes ; i++)
	{
		buf[i] = dma_uart_RX_buffer[i];
	}
}

/**
 *
 * @param is_idle
 */
void vDMA_USART2_signal_idle(void)
{
	BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
	uint16_t	temp_byte;

	temp_byte = RX_BUFFER_SIZE - DMA1_Stream5->NDTR;

	if (temp_byte != 0)
	{
		memcpy(&dma_local_read_buffer[dma_uart_RX_byte], dma_uart_RX_buffer, temp_byte);
		dma_uart_RX_byte += temp_byte;
		xSemaphoreGiveFromISR( *pDMA_Uart_TX_Sem, &xHigherPriorityTaskWoken);
	}

	DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
