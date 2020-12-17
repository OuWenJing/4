/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-07-13
*
*	�汾�� 		V1.0
*
*	˵���� 		��ʪ�Ƚڵ��ȡ������ʪ�����ݺ��͸�Э����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include <hal_joystick.h>
#include <hal_assert.h>
#include <hal_board.h>
#include <ioCC2530.h>
#include <hal_int.h>
#include <hal_lcd.h>
#include <hal_led.h>
#include "hal_button.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "hal_mcu.h"
#include "OLEDIIC.h"
#include "hal_rf.h"
#include "TM1640.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "Usart.h"	
#include "delay.h"
#include "SHT20.h"
#include "OLED.h"
#include "IIC.h"

//������������ 
#define RF_CHANNEL                25  // 2.4 GHz �ŵ� 11~26
#define PAN_ID                0x2007  //PANID
#define Coordinator_ADDR      0x2520  //������ַ

#define APP_PAYLOAD_LENGTH        30
/***********************************************************************************
* LOCAL VARIABLES
*/
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

static void Coordinator_Node(void); //Э�����ڵ�
//==========================================================
//	�������ƣ�	Coordinator_Node()
//
//	�������ܣ�	Э�����ڵ�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void Coordinator_Node(void)
{
  uint8_t i = 0,Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0,Temp_Data[30],Humi_Data[30];
		    // ���� basicRF
    basicRfConfig.panId      = PAN_ID;     //PAN_ID
    basicRfConfig.channel    = RF_CHANNEL; //�ŵ�
    basicRfConfig.ackRequest = TRUE;       //��ҪACk
    basicRfConfig.myAddr = Coordinator_ADDR;    // ���ñ�����ַ
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {
      HAL_ASSERT(FALSE);
    }
    //��������
    basicRfReceiveOn();

    //���������ѭ��
    while (TRUE)
    {
				/*���շ��͵��õ�ַ������*/
        if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0)  
        {
          Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0;

          
          for(i=0;i<APP_PAYLOAD_LENGTH;i++)
          {
             //�¶�����
            if(pRxData[i] == ',')
              Temp_Flag = 2;
            
            if(Temp_Flag == 1)
            {
              Temp_Data[Temp_Count] = pRxData[i];
              Temp_Count++;
            }
            
            if(pRxData[i] == ':' && Temp_Flag == 0)
              Temp_Flag = 1;

            //ʪ������
            if(Temp_Flag == 2)
            {
              if(pRxData[i] == '.')
                Humi_Flag = 2;
              
              if(Humi_Flag == 1)
              {
                Humi_Data[Humi_Count] = pRxData[i];
                Humi_Count++;
              }
              
              if(pRxData[i] == ':')
                Humi_Flag = 1;
            }
          }

          Temp_Data[2] = '\0';Humi_Data[2] = '\0';
          OLED_P8x16Str(45,3,Temp_Data);
          OLED_P8x16Str(45,6,Humi_Data);
          memset(Temp_Data,'\0',30);
          memset(Humi_Data,'\0',30);
        }
    }
}

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
void main(void)
{    
    // Initalise board peripherals ��ʼ����Χ�豸
    halBoardInit();
		
    OLED_IIC_Init();  //��ʼ��OLED��IIC
    OLED_Init();      //��ʼ��OLED��
    OLED_Init_UI();   //��ʼ����Ļ��ʾ
		
    // Initalise hal_rf Ӳ�������� rf ���г�ʼ��
    if(halRfInit()==FAILED)
    {
      HAL_ASSERT(FALSE);
    }
    Coordinator_Node(); //���߽�����ʾ����
}
