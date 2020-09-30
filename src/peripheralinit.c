/**
  ******************************************************************************
  * @file    peripheralinit.c
  * @author  franc
  * @version V1.0
  * @date    15 ott 2019
  * @brief   Interface to call all peripheral initialisation
  ******************************************************************************
*/

#include "peripheralinit.h"
#include "ledhardware.h"
#include "buttonhw.h"
#include "dma.h"
#include "inc\lib_uart.h"

/**
 * @brief Calls all the peripheral initialisation
 * 
 * @return uint8_t 1 is all good, 0 if not
 */
uint8_t uiPeripheralInit_Init( void )
{
	uint8_t retVal = SET;

	vLedHardware_InitLed();
	vButtonHardware_Init();

	vDMA_USART2_Configuration(ENABLE, ENABLE);
	UART_lib_config(e_UART_2, ENABLE, USART_IT_IDLE, USART_DMAReq_Rx | USART_DMAReq_Tx);

	return retVal;
}


