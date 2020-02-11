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

#include "uart_task.h"

static SemaphoreHandle_t *pUart_TX_Sem;

static void vDMA_UART_NVIC_Configuration(void);

/**
 * @brief 
 * 
 */
void vDMA_USART2_Configuration( void )
{
	DMA_InitTypeDef DMA_InitStructure;

	//pUart_TX_Sem = sem_UartTask_GetSemHandler();

	//if (*pUart_TX_Sem != NULL)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

		DMA_DeInit(DMA1_Stream5);

		DMA_StructInit(&DMA_InitStructure);
		/* UART2_TX DMA1_Stream5 channel4*/
		DMA_InitStructure.DMA_Channel = DMA_Channel_4;  				
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;          
		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_RX_buffer[0];
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
		DMA_InitStructure.DMA_BufferSize = 2;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;		/* half full ? */
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(DMA1_Stream5, &DMA_InitStructure);

		/* interrupt a trasferimento completo */
		DMA_ITConfig(DMA1_Stream5, DMA_IT_TC,  ENABLE);	/* enable interrupt */

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
		DMA_ITConfig(DMA1_Stream6, DMA_IT_TC,  ENABLE);
	}
}

/**
 * @brief DMA1_Stream5 handles RX of UART2
 */
void DMA1_Stream5_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
	if (*pUart_TX_Sem != NULL)
	{
		//while(!(USART2->SR & USART_SR_TC));
		xSemaphoreGive( *pUart_TX_Sem );
	}
}

/**
 * @brief DMA1_Stream6 handles TX of UART2
 */
void DMA1_Stream6_IRQHandler(void)
{
	// if(DMA1 -> HISR & (DMA_HISR_TCIF6))
	//DMA1 -> HIFCR |= DMA_HISR_TCIF6;
	//while(!(USART2->SR & USART_SR_TC));	/* */
	DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
	DMA_Cmd(DMA1_Stream6, DISABLE);	/* needed ? */
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
	uint8_t i;

	for (i = 0 ; i < n_byte ; i++)
	{
		dma_uart_TX_buffer[i] = pString[i];
	}

	DMA_SetCurrDataCounter(DMA1_Stream6, n_byte);
	DMA_Cmd(DMA1_Stream6, ENABLE);
}

/**
 * @brief 
 * 
 * @param pSem 
 */
void vDMA_USART2_Set_Sem(SemaphoreHandle_t *pSem)
{
	pUart_TX_Sem = pSem;
}
