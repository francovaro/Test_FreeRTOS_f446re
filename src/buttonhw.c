/*
 * buttonhw.c
 *
 *  Created on: 24 ott 2019
 *      Author: franc
 */

#ifndef BUTTONHW_C_
#define BUTTONHW_C_

#include "buttonhw.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"

void vButtonHardware_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/* init clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);	/* useful ? */

	/* init GPIO as input */
	GPIO_InitStructure.GPIO_Pin = ( PUSH_BUTTON_PIN );
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(PUSH_BUTTON_GPIO , &GPIO_InitStructure);


	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	/* set ext  13 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	EXTI_Init(&EXTI_InitStructure);
}

#endif /* BUTTONHW_C_ */
