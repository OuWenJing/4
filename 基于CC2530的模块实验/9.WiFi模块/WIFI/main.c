/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-19
*
*	�汾�� 		V2.0
*
*	˵���� 		WiFiʵ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include <ioCC2530.h>
#include "Usart.h"
#include "Rs485.h"
#include "delay.h"
#include "Lamp.h"
#include "Time.h"
#include "WiFi.h"
#include "stdio.h"
#include "string.h"
//==========================================================
//	�������ƣ�	main()
//
//	�������ܣ�	������ں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8 temp=10,humi=20;
uint16 Linght_Intensity = 1000;
uint8 Buffer_Tmp[32];
long Tick_SendOneNET = 0;
void main(void)
{
    Hal_Init_32M();     //��ʼ��32Mʱ��
    USRT0_Init();       //��ʼ������0
		Init_Timer1();			//��ʱ��1��ʼ�����ж�����1ms��Ϊ�������ݵ�OneNET�ṩʱ���׼��
    WiFi_Init();        //��ʼ��WiFiģ��    
	  Tick_SendOneNET = Time1_GetTicks()+2000;//2�뷢��һ��
    while(1)
    {
				if(Time1_GetTicks() > Tick_SendOneNET){
					/*ת�����ַ���*/
					sprintf((void*)&Buffer_Tmp[0],"%02d%02d%04d",temp,humi,Linght_Intensity);
					USART0_SendString(Buffer_Tmp,strlen((char const*)Buffer_Tmp));//���ڷ��͵�OneNET 
					
					Tick_SendOneNET = Time1_GetTicks()+2000;//2�뷢��һ��
					
					/*temp,humi,Linght_IntensityΪģ������*/
					temp++;
					humi++;
					temp = temp%100;//����100������
					humi = humi%100;//����100������
					Linght_Intensity += 50;
					if(Linght_Intensity>2000){//����2000����ֵ1000
						Linght_Intensity = 1000;
					}
				}
    }
}
