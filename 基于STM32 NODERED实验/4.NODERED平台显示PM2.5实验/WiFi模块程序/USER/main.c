#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "WiFi.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-03-19
*
*	�汾�� 		V2.0
*
*	˵���� 		WiFi����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint32_t SensorData[3]={0};
uint8_t SendBuffer[16];
uint16_t PM2P5_Val = 0;
int main(void)
{
    HAL_Init();             				//��ʼ��HAL��  
    Rs485_Init();										//��ʼ��485
    UART1_Init(115200);							//��ʼ������1 485����ʹ��
    UART2_Init(115200);							//��ʼ������2
    USART3_Init(115200);						//���Դ���   
    printf("this usart3 print\r\n");
    WiFi_Init();											//��ʼ��WiFi��������OneNET
  
    /*�ж�Ƶ��2HZ �����ص�����RS485_HandlerCb*/
    TIM3_Init(10000-1,3200-1,RS485_HandlerCb);  
    while(1)
    {
        HAL_Delay(1000);//��ʱ1�룬1�Ӹ���һ��
        /*ת���ַ���*/
        PM2P5_Val = (SensorData[0]<<8) + SensorData[1];
        sprintf((void*)&SendBuffer[0],"%03d",PM2P5_Val);
        WiFi_SerialSend(&SendBuffer[0],4);//���͵�OneNET
        printf("����������(ug/m3)==%d\r\n",PM2P5_Val);//���Դ�ӡ
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
    static uint8_t state = 0;
  if(state == 0){//��������
        Rs485_Send(Addr_WiFi,Addr_PM2_5,PM2_5_Get_Conc,0,(void*)0);
        printf("���󴫸�������\n");
        state = 1;
    }
    else{//����Ƿ񷵻�����
        if(!DataHandling_485(Addr_WiFi)){	//�Ǳ���������485���ݴ���
              printf("get data\r\n");
              SensorData[0] = Rx_Stack.Data[0];
              SensorData[1] = Rx_Stack.Data[1];          
        }
        state = 0;
    }
}





