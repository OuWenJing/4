#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "usart.h"
#include "Rs485.h"
#include "timer.h"
#include "IIC.h"
#include "OLED.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		OLED����ʾ����ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************

************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t ucArray_ID[10];
uint8_t DispBuf[40];
uint8_t GetId = 0;
int main(void)
{
    HAL_Init();     //��ʼ��HAL��
    Rs485_Init();		//��ʼ��485
    UART1_Init(115200);		//��ʼ�����ڣ�485����ʹ�õ��������
    TIM3_Init(10000-1,3200-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/32/10000/ = 2HZ
  
    OLED_Init();   //��ʼ��OLED��
   
    OLED_P8x16Str(0,0,"LF-RFID"); //��ʾHF-RFID���� 
    /*��ʾһ��Ĭ��ֵ*/
    sprintf((void*)&DispBuf[0],"ID:%02X%02X%02X%02X",0,0,0,0);    
    OLED_P8x16Str(0,3,DispBuf);
    while(1)
    {
        if(GetId)//GetId,��RS485_HandlerCb()�����С�
        {//���յ�Ҫ��ʾ��ID
            GetId = 0;//��ձ�־
            if(!(!ucArray_ID[0] && !ucArray_ID[1] && !ucArray_ID[2] && !ucArray_ID[3]))
            {//�������ȫ�㣬������ȷ�����ݡ�
              sprintf((void*)&DispBuf[0],"ID:%02X%02X%02X%02X",  
                        ucArray_ID[0],ucArray_ID[1],ucArray_ID[2],ucArray_ID[3]);
                OLED_P8x16Str(0,3,DispBuf);//��ʾID
            } 
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
	static uint16_t i = 0,state = 0;

    if(state == 0)
    {   
      /*��������LF_RFID�ڵ㣬�ش���������*/
        Rs485_Send(Addr_LCD,Addr_LF_RFID,LF_RFID_Get_ID,0,(void*)0);
        state = 1;//�¸�״̬Ϊ״̬1   
    }   
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_LCD))		//��������
        {
            if(Rx_Stack.Src_Adr == Addr_LF_RFID)	//����LF-RFID������
            {
                for(i=0;i<4;i++)//��������
                {
                    ucArray_ID[i] = Rx_Stack.Data[i];
                }
                GetId = 1;    
            }
        }
        state = 0;//�ص�״̬0
    }
}




