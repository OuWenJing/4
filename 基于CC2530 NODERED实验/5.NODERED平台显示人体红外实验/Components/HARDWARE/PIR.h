#ifndef __PIR_H
#define __PIR_H			   

#include <ioCC2530.h>

#define   PIR_LED  P0_3        //����P0.3��ΪLED���ƶ�

#define   PIR_LED_ON()      PIR_LED = 0	//����LED1
#define   PIR_LED_OFF()	    PIR_LED = 1 //�ر�LED1

#define   PIR_Read()        P1_1  //�������ʹ��P1_1

extern void PIR_Init(void); //LED��ʼ��

#endif

