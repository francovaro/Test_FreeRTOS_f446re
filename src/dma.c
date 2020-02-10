/*
 *  @file  : dma.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 feb 2020
 */

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "semphr.h"

#include "stm32f4xx_dma.h"
#include "dma.h"

#include "uart_task.h"

static SemaphoreHandle_t *gUart_TX_Button;

static void vDMA_UART_NVIC_Configuration(void);

void vDMA_UART_Configuration( void )
{
#if 1
	DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(DMA1_Stream5);

	DMA_StructInit(&DMA_InitStructure);
	/* DMA2 DMA1_Stream5 channel0*/
	DMA_InitStructure.DMA_Channel = DMA1_Stream5;  /*pagina 8, AN4031 tabella: su stream0 ADC1 su channel0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;;          //indirizzo registro ADC
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_TX_buffer[0];//indirizzo buffer
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                  //tipo trafsferimento
	DMA_InitStructure.DMA_BufferSize = 2;                           //dimesione buffer
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         //NON incrementa l'indirzzo la periferica
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  //MA il DMA
	// DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //16 bit sul ADC
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //16 bit in mem
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                          //Circolare: quando arrivo in fondo roiparto da 0
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                      //Priorit�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;                    //Uso il FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;        //4 posti
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;              //ogni 'burst' svuota il FIFO
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;      //in un colpo solo
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

	/* interrupt a trasferimento completo */
	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC,  ENABLE);	/* enable interrupt */

	/* */
	DMA_DeInit(DMA1_Stream6);
	/* DMA1_Stream5 enable */
	DMA_Cmd(DMA1_Stream5, ENABLE);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA1_Stream6;  /*pagina 8, AN4031 tabella: su stream0 ADC1 su channel0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;          //indirizzo registro ADC
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_RX_buffer[0];//indirizzo buffer
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                  //tipo trafsferimento
	DMA_InitStructure.DMA_BufferSize = 1;                           //dimesione buffer
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         //NON incrementa l'indirzzo la periferica
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  //MA il DMA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //16 bit sul ADC
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //16 bit in mem
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                          //Circolare: quando arrivo in fondo roiparto da 0
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                      //Priorit�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;                    //Uso il FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;        //4 posti
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;              //ogni 'burst' svuota il FIFO
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;      //in un colpo solo
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);

	DMA_Cmd(DMA1_Stream6, ENABLE);

	/* interrupt a trasferimento completo */
	vDMA_UART_NVIC_Configuration();
	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC,  ENABLE);
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC,  ENABLE);

	gUart_TX_Button = sem_UartTask_GetSemHandler();

#endif
}

/**
 * @brief DMA1_Stream5 handles RX of UART2
 */
void DMA1_Stream5_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
	xSemaphoreGive( &gUart_TX_Button );
}

/**
 * @brief DMA1_Stream6 handles TX of UART2
 */
void DMA1_Stream6_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
}

/**
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
