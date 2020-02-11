/*
 *  @file  : uart.c
 *	
 *  @brief : 
 *
 *  @author: franc
 *  @date  : 05 oct 2019
 */

#include "uart.h"
#include "dma.h"

static void USART2_NVIC_Config(void);

/**
 * @brief Config for USART 2
 * @param irqEnabled 1 irq is enabled 0 no
 */
void vUSART2_config(uint8_t irqEnabled)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStructure;

	usart_serialReceived = 0;
	usart_nrOfByte = 0;

	/* Give the clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStruct);
	USART_StructInit(&USART_InitStructure);

	/* rx PA2 */
	/* tx PA3 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	/* PIN config */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA , &GPIO_InitStruct);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2 ,&USART_InitStructure);

	/* if irq is enabled, set it */
	if(irqEnabled == ENABLE)
	{
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); /* ENABLE INTERRUPT ON rx */
		USART2_NVIC_Config();
	}

	/* config DMA to work with UART2 */
	vDMA_USART2_Configuration();

	/* Enable USART DMA RX Requsts */
	USART_DMACmd(USART2, (USART_DMAReq_Rx | USART_DMAReq_Tx), ENABLE);

	/* Start UART2 */
	USART_Cmd(USART2 , ENABLE);
}

/**
 * @brief
 * 
 * @param strToSend pointer to string to be sent
 * @param byteToSend nr of byte to be sent
 */
void vUSART2_SendData(const char * strToSend, uint16_t byteToSend)
{
	uint16_t count;

	for(count = 0 ; count < byteToSend ; count++)
	{
		while (USART_GetFlagStatus(USART2, USART_SR_TXE) == RESET);
		USART_SendData(USART2, *strToSend++);

	}
}

/**
 * @brief 
 * 
 * @param c 
 * @return int 
 */
uint8_t vUSART2_PutC(int c)
{
  assert_param(IS_USART_123_PERIPH(USARTx));

  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
  USART2->DR =  (c & 0xff);

  return 0;
}

/**
 * @brief NVIC config for USART2 peripheral 
 */
static void USART2_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief IRQ handler for USART2 peripheral 
 */
void USART2_IRQHandler(void)
{
	/*
	 * TODO
	 * handle request from PC !
	 */

	if( USART_GetITStatus(USART2,USART_IT_RXNE ) != RESET)
	{
		//do{
			usart_rxBuffer[usart_nrOfByte] = USART_ReceiveData(USART2);
			usart_nrOfByte++;
		//}while();	/* check condition */
		
		usart_serialReceived = SET;
	 }
}
