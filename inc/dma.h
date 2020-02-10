/*
 *  @file  : dma.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 feb 2020
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_

#define BUFFER_SIZE	(100u)

extern void vDMA_UART_Configuration( void );

uint8_t dma_uart_TX_buffer[BUFFER_SIZE];
uint8_t dma_uart_RX_buffer[BUFFER_SIZE];

#endif /* INC_DMA_H_ */
