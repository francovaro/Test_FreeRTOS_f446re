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

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "semphr.h"

#include "stm32f4xx_dma.h"
#include "stdint.h"

#define BUFFER_SIZE	(100u)

extern void vDMA_USART2_Configuration( BaseType_t dma_tx, BaseType_t dma_rx );
extern void vDMA_USART2_SendData(char* pString, uint8_t n_byte);
extern void vDMA_USART2_Set_Sem(SemaphoreHandle_t *pSem);
extern void vDMA_USART2_Clr_Index(void);
extern uint8_t uiDMA_USART2_Get_Index(void);
extern void vDMA_USART2_Get_Buffer(char *buf, uint8_t nrBytes);
extern void vDMA_USART2_signal_idle(void);

#endif /* INC_DMA_H_ */
