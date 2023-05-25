#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "Rs485.h"
#include "SHT20.h"	
#include "delay.h"
#include "timer.h"
#include "Usart.h"
#include "Optocoupler.h"

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
uint8_t DetectResult = 0;
int main(void)
{
  uint8_t state = 0;     //��ʾ�¶� ����ʪ��
  HAL_Init();             					//��ʼ��HAL��  
  Optocoupler_Init();               //��ʼ����翪��ģ��
  Rs485_Init();											//��ʼ��485
  USART3_Init(115200);              //���ڵ���
  UART1_Init(115200);								//��ʼ������1,RS485ͨ��
  
  /*�ж�Ƶ��20HZ,����RS485_HandlerCb()�ص�����*/
  TIM3_Init(10000-1,320-1,RS485_HandlerCb);    
	while(1)
	{
      DetectResult = Optocoupler_State_Read();//=1,��⵽�ڵ��0=δ��⵽
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
    if(!DataHandling_485(Addr_PH)){	//�Ǳ���������485���ݴ���
        printf("get requery\r\n");
        /*485��������*/
        Rs485_Send(Addr_PH,Addr_WiFi,PH_State,1,&DetectResult);
    }
}




