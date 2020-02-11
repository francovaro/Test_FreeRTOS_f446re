/*
 *  @file  : uart.c
 *	
 *  @brief : 
 *
 *  @author: franc
 *  @date  : 05 oct 2019
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_usart.h"

#define USART_MAX_BUFFER (255u)

__IO uint8_t usart_rxBuffer[USART_MAX_BUFFER];

__IO FlagStatus usart_serialReceived;
__IO uint16_t usart_nrOfByte;

extern void vUSART2_config(uint8_t irqEnabled);
extern void vUSART2_SendData(const char * strToSend, uint16_t byteToSend);

extern uint8_t vUSART2_PutC(int c);

#endif /* UART_H_ */
