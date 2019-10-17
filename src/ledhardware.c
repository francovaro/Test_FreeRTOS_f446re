/*
 * ledhardware.c
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */

#include "ledhardware.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void vLedHardware_InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_5 );
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
}

void vLedHardware_Toggle(void)
{
	GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
}
