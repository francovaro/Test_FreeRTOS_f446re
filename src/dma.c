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

static SemaphoreHandle_t *pDMA_Uart_TX_Sem;

static void vDMA_UART_NVIC_Configuration(void);

/**
 * @brief 
 * 
 */
void vDMA_USART2_Configuration( void )
{
	DMA_InitTypeDef DMA_InitStructure;

	//pDMA_Uart_TX_Sem = sem_UartTask_GetSemHandler();

	//if (*pDMA_Uart_TX_Sem != NULL)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

		DMA_DeInit(DMA1_Stream5);

		DMA_StructInit(&DMA_InitStructure);
		/* UART2_TX DMA1_Stream5 channel4*/
		DMA_InitStructure.DMA_Channel = DMA_Channel_4;  				
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;          
		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_RX_buffer[0];
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
		DMA_InitStructure.DMA_BufferSize = 1;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;		/* half full ? */
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(DMA1_Stream5, &DMA_InitStructure);


		/* DMA1_Stream5 enable */
		DMA_Cmd(DMA1_Stream5, ENABLE);

		/* */
		DMA_DeInit(DMA1_Stream6);

		DMA_StructInit(&DMA_InitStructure);
		DMA_InitStructure.DMA_Channel = DMA_Channel_4;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_TX_buffer[0];
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		DMA_InitStructure.DMA_BufferSize = 10;
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

		//DMA_Cmd(DMA1_Stream6, ENABLE);

		/* interrupt a trasferimento completo */
		vDMA_UART_NVIC_Configuration();

		DMA_ITConfig(DMA1_Stream5, DMA_IT_TC,  ENABLE);
		//DMA_ITConfig(DMA1_Stream5, DMA_IT_HT,  ENABLE);
		DMA_ITConfig(DMA1_Stream6, DMA_IT_TC,  ENABLE);
	}
}

/**
 * @brief DMA1_Stream5 handles RX of UART2
 */
void DMA1_Stream5_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
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
	 if(DMA1 -> HISR & (DMA_HISR_TCIF5))
	 {
		DMA1 -> HIFCR |= DMA_HISR_TCIF5;
		if (*pDMA_Uart_TX_Sem != NULL)
		{
			dma_uart_RX_byte++;
			DMA1_Stream5->M0AR = (uint32_t)&dma_uart_RX_buffer[dma_uart_RX_byte];
			DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
			xSemaphoreGiveFromISR( *pDMA_Uart_TX_Sem, &xHigherPriorityTaskWoken);

		}
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
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
 * @brief 
 * 
 */
static void vDMA_UART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 
 * 
 * @param pString 
 * @param n_byte 
 */
void vDMA_USART2_SendData(uint8_t* pString, uint8_t n_byte)
{
	uint8_t 	i;
	uint32_t 	primask;

	for (i = 0 ; i < n_byte ; i++)
	{
		dma_uart_TX_buffer[i] = pString[i];
	}
    primask = __get_PRIMASK();
    __disable_irq();

    //DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
    //DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_HTIF6);
    //DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
    //DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);

    /* Prepare DMA for next transfer */
    /* Important! DMA stream won't start if all flags are not cleared first */
    DMA1->HIFCR = DMA_FLAG_FEIF6 | DMA_FLAG_DMEIF6 | DMA_FLAG_TEIF6 | DMA_FLAG_HTIF6 | DMA_FLAG_TCIF6;
    DMA1_Stream6->M0AR = (uint32_t)dma_uart_TX_buffer;   /* Set memory address for DMA again */
    DMA1_Stream6->NDTR = n_byte;    /* Set number of bytes to receive */
    DMA1_Stream6->CR |= DMA_SxCR_EN;            /* Start DMA transfer */

	// DMA_SetCurrDataCounter(DMA1_Stream6, n_byte);
	// DMA_Cmd(DMA1_Stream6, ENABLE);

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
	//DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
	//dma_uart_RX_byte = 0;
	//DMA1_Stream5->CR &= (~DMA_SxCR_EN);            /* Start DMA transfer */
	//DMA1_Stream5->M0AR = (uint32_t)&dma_uart_RX_buffer[0];
	//DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
}

/**
 *
 * @return
 */
uint8_t uiDMA_USART2_Get_Index(void)
{
	return dma_uart_RX_byte;
}

/**
 *
 * @param buf
 * @param nrBytes
 */
void vDMA_USART2_Get_Buffer(uint8_t *buf, uint8_t nrBytes)
{
	uint8_t i;
	for ( i=0; i< nrBytes ; i++)
	{
		buf[i] = dma_uart_RX_buffer[i];
	}
}
