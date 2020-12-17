/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		
*
*	���ڣ� 		2018-10-30
*
*	�汾�� 		V1.0
*
*	˵���� 		ʵ�������
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
#include <hal_lcd.h>
#include <hal_led.h>
#include <hal_joystick.h>
#include <hal_assert.h>
#include <hal_board.h>
#include <ioCC2530.h>
#include <hal_int.h>
#include "hal_mcu.h"
#include "hal_button.h"
#include "hal_rf.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "stdlib.h"
#include "string.h"
#include "delay.h"
#include "stdio.h"
#include "KEY.h"
#include "LED.h"

#define RF_CHANNEL                25      // 2.4 GHz RF channel
#define PAN_ID                0x2007
#define SWITCH_ADDR           0x2520
#define LIGHT_ADDR            0xBEEF

#define APP_PAYLOAD_LENGTH    0x02 //�շ������ݳ���
#define CMD_LIGHT_CTRL        0x01 //�ƹ��������


static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
//==========================================================
//	�������ƣ�	appLight()
//
//	�������ܣ�	���ݽ��պ�������������ģ�鷢�͵�����
//
//	��ڲ�����	@ PARAM BaseCfFiFig--�ļ���Χ������������Ƶ��������
//                        RX���ݻ�����ָ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appLight()
{
    basicRfConfig.panId      = PAN_ID;     //PANID
    basicRfConfig.channel    = RF_CHANNEL; //�ŵ�
    basicRfConfig.ackRequest = TRUE;			 //��ҪACK�ظ�        
    basicRfConfig.myAddr     = LIGHT_ADDR;  // ���ñ�����ַ
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {//�������ʧ��
      HAL_ASSERT(FALSE);
    }
    //����RF����
    basicRfReceiveOn();
    
    while (TRUE)
    {
        while(!basicRfPacketIsReady());   //��������

        if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0)  //���շ��͵��õ�ַ������
        {
						if(pRxData[0] == CMD_LIGHT_CTRL){//�ǵƿ�������
								switch(pRxData[1])
								{
									case S1_PRES:  //����1
										MCU_IO_TGL_PREP(0,2);//P0.2 IO�����ת
										break;
									case S2_PRES:  //����2
										MCU_IO_TGL_PREP(0,3);//P0.3 IO�����ת
										break;
									case S3_PRES:  //����3
										MCU_IO_TGL_PREP(1,6);//P1.6 IO�����ת
										break;
									case S4_PRES:  //����4
										MCU_IO_TGL_PREP(1,7);//P1.7 IO�����ת
										break;
									default: break;
								}
								/*��ջ���*/
								pRxData[0] = 0;
								pRxData[1] = 0;
						}
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
    halBoardInit(); //��Ƭ����ʼ��
		LED_Init();     //LEDģ���ϵ�LED�ƿ���IO��ʼ��
		
    // Initalise hal_rf Ӳ�������� rf ���г�ʼ��
    if(halRfInit()==FAILED)
    {//�������ʧ��
      HAL_ASSERT(FALSE);
    }
    
    appLight();         //���߿���������մ���
}