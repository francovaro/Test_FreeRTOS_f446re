/*
 *  @file  : hc_sr04_task.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 02 ott 2020
 */

#ifndef INC_HC_SR04_TASK_H_
#define INC_HC_SR04_TASK_H_

volatile uint8_t hcsr04_signalDone;

extern void HC_SR04_Init(void);
extern void vHC_SR04_Task(void *pvParameters);


#endif /* INC_HC_SR04_TASK_H_ */
