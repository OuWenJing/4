#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "SHT20.h"	
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
*	˵���� 		��ʪ��ģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint32_t Tick_Disp;
int main(void)
{
  uint8_t state = 0;     //��ʾ�¶� ����ʪ��
  
  HAL_Init();            //��ʼ��HAL��
	SHT2x_Init();				  //��ʼ����ʪ�ȴ�����SHT20
	TM1640_Init();				//��ʼ�����������оƬTM1640
  
  /*HAL_GetTick(),����ֵΪ��Ƭ������������ʱ��ֵ����λΪms*/
  Tick_Disp = HAL_GetTick(); //HAL_GetTick(),HAL�⺯��������ֵ��msΪ��λ��
	while(1)
	{
      if((state == 0) && (HAL_GetTick()>(Tick_Disp))){//�����¶�
          state = 1;
          SHT2x_GetTempHumi();//��ȡһ����ʪ�ȣ�������g_sht2x_param.TEMP_HM
          send_LED_Display(0xC0,g_sht2x_param.TEMP_HM,1);//�������ʾ
          
          Tick_Disp = HAL_GetTick()+1000/*1000ms*/;//������һ�θ������ݵ�ʱ���
      }
      else if((state == 1) && (HAL_GetTick()>(Tick_Disp))){//����ʪ��
          state = 0;
          SHT2x_GetTempHumi();//��ȡһ����ʪ��,������g_sht2x_param.HUMI_HM        
          send_LED_Display(0xC0,g_sht2x_param.HUMI_HM,2);
          Tick_Disp = HAL_GetTick()+1000/*1000ms*/;//������һ�θ������ݵ�ʱ���        
      }
  }
}





