#ifndef __LED_H
#define __LED_H 			   

#include "ioCC2530.h"
#include "hal_types.h"
#include "stdio.h"

#define   LED1  P0_2        //����P0.2��ΪLED1���ƶ�
#define   LED2  P0_3        //����P0.3��ΪLED1���ƶ�
#define   LED3  P1_6        //����P1.6��ΪLED1���ƶ�
#define   LED4  P1_7        //����P1.7��ΪLED1���ƶ�

#define   LED1_ON()     LED1 = 0	//����LED1
#define   LED1_OFF()	LED1 = 1    //�ر�LED1

#define   LED2_ON()	LED2 = 0        //����LED2
#define   LED2_OFF()	LED2 = 1	//�ر�LED2

#define   LED3_ON()	LED3 = 0        //����LED3
#define   LED3_OFF()	LED3 = 1	//�ر�LED3

#define   LED4_ON()	LED4 = 0	//����LED4
#define   LED4_OFF()	LED4 = 1	//�ر�LED4

#define   LED_ON()	LED1=0;LED2=0;LED3=0;LED4=0;  //����ȫ��LED
#define   LED_OFF()	LED1=1;LED2=1;LED3=1;LED4=1;  //�ر�ȫ��LED


#define   S1    P1_5        //����P1.5��ΪS1���ƶ�
#define   S2    P1_4        //����P1.4��ΪS2���ƶ�
#define   S3    P0_0        //����P0.0��ΪS3���ƶ�
#define   S4    P0_1        //����P0.1��ΪS4���ƶ�

#define   S1_Read()   P1_5  //S1����P1_5
#define   S2_Read()   P1_4  //S2����P1_4
#define   S3_Read()   P0_0  //S3����P0_0
#define   S4_Read()   P0_1  //S4����P0_1

#define   S1_PRES     BV(0)
#define   S2_PRES     BV(1)
#define   S3_PRES     BV(2)
#define   S4_PRES     BV(3)
enum{
	KEY_RELASE,
	KEY_PRESSED
};
void LED_Init(void); //LED��ʼ��
uint8_t KEY_Scan(void); //����ɨ��
#endif

