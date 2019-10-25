/*
 * buttonhw.c
 *
 *  Created on: 24 ott 2019
 *      Author: franc
 */

#ifndef BUTTONHW_C_
#define BUTTONHW_C_

/* FreeRTOS include */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* STM include*/
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"

/* internl include */
#include "buttonhw.h"

static SemaphoreHandle_t* pgSemButton = 0;

void vButtonHardware_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	pgSemButton = sem_ButtonTask_GetSemHandler();


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

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	BaseType_t taskWoken = pdFALSE;
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		gButtonHwPressed = SET;
		if (pgSemButton != 0)
		{
			xSemaphoreGiveFromISR( *pgSemButton, &taskWoken );
		}
		/* Clear the EXTI line 13 pending bit */

		EXTI_ClearITPendingBit(EXTI_Line13);
		portYIELD_FROM_ISR( taskWoken );
	}
}

#endif /* BUTTONHW_C_ */
