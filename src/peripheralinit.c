/*
 * peripheralinit.c
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */

#include "peripheralinit.h"
#include "ledhardware.h"


uint8_t uiPeripheralInit_Init( void )
{
	uint8_t retVal = 0;

	vLedHardware_InitLed();

	return retVal;
}


