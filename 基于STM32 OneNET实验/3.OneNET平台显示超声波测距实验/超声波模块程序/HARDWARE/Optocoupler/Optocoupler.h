#ifndef _Optocoupler_H
#define _Optocoupler_H

#include "stm32f1xx.h"

#define 	Optocoupler_PORT 		GPIOA

#define 	Optocoupler_Switch 	GPIO_PIN_0
#define 	Optocoupler_State 	GPIO_PIN_1

#define 	Optocoupler_State_Read()   	HAL_GPIO_ReadPin(Optocoupler_PORT,Optocoupler_State)  //��ȡ��紫����״̬

#define 	Optocoupler_Switch_ON()			HAL_GPIO_WritePin(Optocoupler_PORT,Optocoupler_Switch,GPIO_PIN_RESET)	//������紫����
#define 	Optocoupler_Switch_OFF()		HAL_GPIO_WritePin(Optocoupler_PORT,Optocoupler_Switch,GPIO_PIN_SET)		//�رչ�紫����

extern void Optocoupler_Init(void);//��紫������ʼ��

#endif


