#ifndef __SWITCH_H
#define __SWITCH_H 			   

#include <ioCC2530.h>
#include "hal_types.h"

#define   Optocoupler_Switch 	        P1_1
#define   Optocoupler_State 	        P1_0

#define   Optocoupler_State_Read()   	Optocoupler_State       //��ȡ��紫����״̬

#define   Optocoupler_Switch_ON()	Optocoupler_Switch = 0	//������紫����
#define   Optocoupler_Switch_OFF()	Optocoupler_Switch = 1	//�رչ�紫����

void Optocoupler_Init(void);
#endif