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

#include "stm32f4xx_dma.h"
#include "stdint.h"

#define BUFFER_SIZE	(100u)

extern void vDMA_UART_Configuration( void );

__IO uint8_t dma_uart_TX_buffer[BUFFER_SIZE];
__IO uint8_t dma_uart_RX_buffer[BUFFER_SIZE];

__IO uint8_t dma_uart_TX_byte;
__IO uint8_t dma_uart_RX_byte;

#endif /* INC_DMA_H_ */
