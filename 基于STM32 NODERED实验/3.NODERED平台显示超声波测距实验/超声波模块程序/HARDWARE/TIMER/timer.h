#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f1xx_hal.h"

extern uint32_t HCSR04Count;
extern uint8_t Temp[ ],Humi[ ],Light[ ],Sum_Data[ ];//�¶ȡ�ʪ�ȡ���ǿ�����ݼ���
extern TIM_HandleTypeDef TIM3_Handler;  //��ʱ����� 
void TIM3_Init(uint16_t arr,uint16_t psc,void (*cb)(void));
void TIM2_Init(unsigned int arr,unsigned int psc);
#endif

