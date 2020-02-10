/*
 *  @file  : dma.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 feb 2020
 */

#include "stm32f4xx_dma.h"
#include "dma.h"

static void vDMA_UART_NVIC_Configuration(void);

void vDMA_UART_Configuration( void )
{
#if 1
	DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(DMA1_Stream3);
	DMA_DeInit(DMA1_Stream4);

	DMA_StructInit(&DMA_InitStructure);
	/* configurazione DMA2 Stream0 channel0*/
	//DMA_InitStructure.DMA_Channel = DMA_Channel_0;  /*pagina 8, AN4031 tabella: su stream0 ADC1 su channel0*/
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  /*pagina 8, AN4031 tabella: su stream0 ADC1 su channel0*/
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
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;        //4 posti
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;              //ogni 'burst' svuota il FIFO
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;      //in un colpo solo
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);

	/* interrupt a trasferimento completo */
	//DMA_ITConfig(DMA2_Stream0, DMA_IT_TC,  ENABLE);
	DMA_ITConfig(DMA1_Stream3, DMA_IT_TC,  ENABLE);	/* enable interrupt */

	/* DMA2_Stream0 enable */
	DMA_Cmd(DMA1_Stream3, ENABLE);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  /*pagina 8, AN4031 tabella: su stream0 ADC1 su channel0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;          //indirizzo registro ADC
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&dma_uart_RX_buffer[0];//indirizzo buffer
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                  //tipo trafsferimento
	DMA_InitStructure.DMA_BufferSize = 2;                           //dimesione buffer
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         //NON incrementa l'indirzzo la periferica
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  //MA il DMA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //16 bit sul ADC
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //16 bit in mem
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                          //Circolare: quando arrivo in fondo roiparto da 0
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                      //Priorit�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;                    //Uso il FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;        //4 posti
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;              //ogni 'burst' svuota il FIFO
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;      //in un colpo solo
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);

	DMA_Cmd(DMA1_Stream4, ENABLE);

	/* interrupt a trasferimento completo */
	vDMA_UART_NVIC_Configuration();
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC,  ENABLE);
	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC,  ENABLE);


#endif
}

/**
 *
 */
void DMA1_Stream3_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF0);
}

/**
 *
 */
static void vDMA_UART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
