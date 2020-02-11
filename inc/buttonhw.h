/**
  ******************************************************************************
  * @file    buttonhw.h
  * @author  franc
  * @version V1.0
  * @date    24 ott 2019
  * @brief   Button hw config
  ******************************************************************************
*/
#ifndef BUTTONHW_H_
#define BUTTONHW_H_

#include "stm32f4xx.h"

#include <stdint.h>

#define PUSH_BUTTON_GPIO	GPIOC
#define PUSH_BUTTON_PIN		GPIO_Pin_13

__IO uint8_t gButtonHwPressed;
extern void vButtonHardware_Init(void);

#endif /* BUTTONHW_H_ */
