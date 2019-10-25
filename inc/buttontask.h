/**
  ******************************************************************************
  * @file    buttontask.h
  * @author  Francesco Varani
  * @version V1.0
  * @date    24 ott 2019
  * @brief   Task button stuff.
  ******************************************************************************
*/

#ifndef BUTTONTASK_H_
#define BUTTONTASK_H_

#include "semphr.h"

extern void vButtonTask( void *pvParameters );
extern SemaphoreHandle_t * sem_ButtonTask_GetSemHandler(void);

#endif /* BUTTONTASK_H_ */
