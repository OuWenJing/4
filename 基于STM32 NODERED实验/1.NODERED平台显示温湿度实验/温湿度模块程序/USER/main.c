#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "Rs485.h"
#include "SHT20.h"	
#include "delay.h"
#include "timer.h"
#include "Usart.h"
#include "ADC.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.0
*
*	˵���� 		��ʪ��ģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t SendBuffer[3];
uint8_t ReadSensorState = 0;
uint32_t Tick_Disp;
int main(void)
{
  uint8_t state = 0;     //��ʾ�¶� ����ʪ��
  HAL_Init();             					//��ʼ��HAL��  
  Rs485_Init();											//��ʼ��485
  SHT2x_Init();											//��ʼ��SHT20
  TM1640_Init();										//��ʼ��TM1640
  USART3_Init(115200);              //���ڵ���
  UART1_Init(115200);								//��ʼ������1,RS485ͨ��
  
  /*�ж�Ƶ��20HZ,����RS485_HandlerCb()�ص�����*/
  TIM3_Init(10000-1,320-1,RS485_HandlerCb);    
	while(1)
	{
      if((state == 0) && (HAL_GetTick()>(Tick_Disp))){//�����¶�
          state = 1;
          SHT2x_GetTempHumi();//��ȡһ����ʪ�ȣ�������g_sht2x_param.TEMP_HM
          send_LED_Display(0xC0,g_sht2x_param.TEMP_HM,1);//�������ʾ
          SendBuffer[0] = g_sht2x_param.TEMP_HM;//�������ڷ��͵�WIFI�ڵ�
          Tick_Disp = HAL_GetTick()+1000/*1000ms*/;//������һ�θ������ݵ�ʱ���
      }
      else if((state == 1) && (HAL_GetTick()>(Tick_Disp))){//����ʪ��
          state = 0;
          SHT2x_GetTempHumi();//��ȡһ����ʪ��,������g_sht2x_param.HUMI_HM        
          send_LED_Display(0xC0,g_sht2x_param.HUMI_HM,2);
          SendBuffer[1] = g_sht2x_param.HUMI_HM;//�������ڷ��͵�WIFI�ڵ�        
          Tick_Disp = HAL_GetTick()+1000/*1000ms*/;//������һ�θ������ݵ�ʱ���        
      }
	}
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		����ͨ��485���߷��͹�������������
//==========================================================
void RS485_HandlerCb(void)
{
    if(!DataHandling_485(Addr_SHT20)){	//�Ǳ���������485���ݴ���
          printf("get requery\r\n");
          /*485��������*/
          Rs485_Send(Addr_SHT20,Addr_WiFi,SHT20_All,2,&SendBuffer[0]);
    }
}




