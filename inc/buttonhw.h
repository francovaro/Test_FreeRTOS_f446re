/*
 * buttonhw.h
 *
 *  Created on: 24 ott 2019
 *      Author: franc
 */

#ifndef BUTTONHW_H_
#define BUTTONHW_H_

#define PUSH_BUTTON_GPIO	GPIOC
#define PUSH_BUTTON_PIN		GPIO_Pin_13

extern void vButtonHardware_Init(void);

#endif /* BUTTONHW_H_ */