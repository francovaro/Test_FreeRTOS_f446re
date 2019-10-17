/*
 * ledhardware.h
 *
 *  Created on: 15 ott 2019
 *      Author: franc
 */

#ifndef _LEDHARDWARE_H_
#define _LEDHARDWARE_H_

#define LED_GREEN_GPIO	GPIOA
#define LED_GREEN_PIN	GPIO_Pin_5

void vLedHardware_InitLed(void);
void vLedHardware_Toggle(void);

#endif
