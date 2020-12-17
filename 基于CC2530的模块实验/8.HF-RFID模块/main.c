/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-11
*
*	�汾�� 		V2.0
*
*	˵���� 		HF-RFIDʵ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
#include <ioCC2530.h>
#include "OLEDIIC.h"
#include "delay.h"
#include "RC522.h"
#include "Usart.h"	
#include "Rs485.h"
#include "Time.h"
#include "OLED.h"
#include "Lamp.h"

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
uint8 Buffer_CarID[5];//���濨Ƭ����
uint8 Buffer_Tmp[16];
void main(void)
{
		Hal_Init_32M();           //��ʼ��32Mʱ��
		OLED_IIC_Init();          //��ʼ��OLEDIIC
		OLED_Init();              //��ʼ��OLED
		RC522_Init();             //��ʼ��RFIDоƬ
		
		/*��ʾ���⼰Ĭ��ֵ*/
		OLED_P8x16Str(0,0,"     HF_RFID   ");
		sprintf((void*)&Buffer_Tmp[0],"ID:XX XX XX XX",Buffer_CarID[0],Buffer_CarID[1],Buffer_CarID[2],Buffer_CarID[3]);
		OLED_P8x16Str(0,4,&Buffer_Tmp[0]);//OLED��ʾ
		while(1)
		{
				if(IC_Card_Search(&Buffer_CarID[0])){      //��ȡ����Ϣ
						/*������ת���ַ���*/
						sprintf((void*)&Buffer_Tmp[0],"ID:%02X %02X %02X %02X",
										       Buffer_CarID[0],Buffer_CarID[1],Buffer_CarID[2],Buffer_CarID[3]);
						OLED_P8x16Str(0,4,&Buffer_Tmp[0]);//OLED��ʾ
				}
		}
}
