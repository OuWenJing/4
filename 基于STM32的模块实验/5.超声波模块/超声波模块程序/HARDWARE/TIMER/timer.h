#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f1xx.h"

extern	uint32_t HCSR04Count;
extern TIM_HandleTypeDef TIM2_Handler;      //��ʱ����� 

void TIM2_Init(unsigned int arr,unsigned int psc);

#endif

