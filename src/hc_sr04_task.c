/*
 *  @file  : hc_sr04_task.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 02 ott 2020
 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include <stdio.h>

#include "hc_sr04_task.h"
#include "uart_task.h"
#include "stm32f4xx.h"

#define HC_TRIGGER_PIN		GPIO_Pin_10
#define HC_TRIGGER_PIN_SRC	GPIO_PinSource10
#define HC_TRIGGER_PORT		GPIOB
#define HC_TRIGGER_CLOCK	RCC_AHB1Periph_GPIOB

#define HC_ECHO_PIN			GPIO_Pin_0
#define HC_ECHO_PIN_SRC		GPIO_PinSource0
#define HC_ECHO_PORT		GPIOA
#define HC_ECHO_CLOCK		RCC_AHB1Periph_GPIOA

static 			uint32_t hc_sr_timeRead;
static 			SemaphoreHandle_t pHC_sem;
QueueHandle_t	*local_uart_task_queue;

static void HC_SR04_Init_Pin(void);
static void HC_SR04_Init_Timer(void);
static void HC_SR04_StartInterrupt(void);

/**
 *
 */
void HC_SR04_Init (void)
{
	pHC_sem = xSemaphoreCreateBinary();

	hc_sr_timeRead = 0;

	HC_SR04_Init_Pin();
	HC_SR04_Init_Timer();
}

/**
 *
 * @param pvParameters
 */
void vHC_SR04_Task (void *pvParameters)
{
	BaseType_t retVal;
	sUartTask_Queue element_to_write = {.senderId = 0, .text = "", .nr_byte = 0 };

	if (pHC_sem != NULL)
	{
		HC_SR04_StartInterrupt();
		local_uart_task_queue = UartTask_GetQueue();

		while(1)
		{
			retVal = xSemaphoreTake( pHC_sem, portMAX_DELAY);
			if (retVal == pdTRUE)
			{
				/*
				 * write the val to uart*0.17
				 */
				snprintf(element_to_write.text, 15u, "%.2f",( hc_sr_timeRead*0.17) );
				xQueueSend(*local_uart_task_queue, &element_to_write, 0);
			}
		}
	}

}
/* ------------------------------- Private function implementation -------------------------------*/

/**
 * @brief Initialize 2 timer:
 * 	- TIM2 channel 3 is used as output compare to generate the 10uS pulse.
 * 	- TIM5 is used as input compare to read the length of the echo pulse output.
 */
static void HC_SR04_Init_Timer(void)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	RCC_ClocksTypeDef RCC_ClocksStatus;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_GetClocksFreq(&RCC_ClocksStatus);
	uint16_t prescaler = ((RCC_ClocksStatus.HCLK_Frequency/2)) / 1000000 - 1; //1 tick = 1us (1 tick = 0.165mm resolution)

	/*
	 * not sure about the calc of the prescaler
	 * shouldn t be HCLK/2 ?
	 * */

	/* -------------------------- TIM 2 setting -------------------------- */
	/* TIM 2 is used as output compare
	 * to generate the desired pulse of 10 us
	 */
	//TIM_DeInit(TIM2);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

	TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;						/* period ? */
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);	/* TIM 2 */
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);	/* TIM 5 */


	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;	/* why pwm1 and not TIM_OCMode_Active */
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 15u; //us
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);	/* write CCMR2 */
	TIM_ARRPreloadConfig(TIM2, DISABLE);	/* set ARPE Auto Pre Load */

	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* -------------------------- TIM 5 setting -------------------------- */
	/* TIM 5 is used as input compare
	 * to read the incoming pulse
	 */
	//TIM_DeInit(TIM5);


	/* set TIM5 channel 1 for input compare on RISING edge */
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);

	/* set TIM5 channel 2 for input compare on FALLING edge */
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);

	//TIM_PWMIConfig(TIM5, &TIM_ICInitStruct);

	/* select the  */
	TIM_SelectInputTrigger(TIM5 , TIM_TS_TI1FP1);		/* set the input */
	TIM_SelectSlaveMode(TIM5 , TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM5 , TIM_MasterSlaveMode_Enable);

	TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);


	// No StructInit call in API
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 *
 */
void HC_SR04_Init_Pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	RCC_AHB1PeriphClockCmd(HC_TRIGGER_CLOCK | HC_ECHO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = HC_TRIGGER_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HC_TRIGGER_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(HC_TRIGGER_PORT, HC_TRIGGER_PIN_SRC, GPIO_AF_TIM2);

	GPIO_InitStructure.GPIO_Pin = HC_ECHO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(HC_ECHO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(HC_ECHO_PORT, HC_ECHO_PIN_SRC, GPIO_AF_TIM5);
}

/**
 *	@brief It starts operations for measruing range
 *		- set pin high
 *		- starts TIM2
 *		- starts TIM5
 */
static void HC_SR04_StartInterrupt(void)
{
	TIM_Cmd(TIM2, ENABLE);				/* set CEN - Counter enable bit */
	TIM_Cmd(TIM5, ENABLE);				/* set CEN - Counter enable bit */
}

/**
 *
 */
void TIM5_IRQHandler(void)
{
	BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
	static uint32_t startVal = 0;
	static uint32_t endValue = 0;

	/* is not used */
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1))
	{
		startVal = TIM_GetCapture1(TIM5);	/* to read channel 1 - USELESS ?*/
		endValue = 0;						/* so in case of error.. 0! */
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);	/* maybe not neede */
		/*vCCxIF can be cleared by software by writing it to 0 or by reading the captured data stored in the
		TIMx_CCRx register. */
	}

	if (TIM_GetITStatus(TIM5, TIM_IT_CC2))
	{
		endValue = TIM_GetCapture2(TIM5);	/* to read channel 2 ?*/
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);	/* maybe not neede */
		/*vCCxIF can be cleared by software by writing it to 0 or by reading the captured data stored in the
		TIMx_CCRx register. */

 		hc_sr_timeRead = /*startVal -*/ endValue;

		xSemaphoreGiveFromISR( pHC_sem, &xHigherPriorityTaskWoken);
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void TIM2_IRQHandler(void)
{
	/* is not used */
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1))
	{
		TIM_Cmd(TIM2, DISABLE);				/* clears CEN - Counter enable bit */
	}
}
