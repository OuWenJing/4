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

#define APP_PAYLOAD_LENGTH     0x02  //�շ������ݳ���
#define CMD_LIGHT_CTRL         0x01  //�ƿ�������
/*�����������ã�����Ҫ*/
#define RF_CHANNEL                25  // 11~26,�շ�˫��������ͬ�����ŵ�
#define PAN_ID                0x2007 	//PANID���շ�˫��������ͬ��PAIN
#define SWITCH_ADDR           0x2520 	//�����ڵ������̵�ַ
#define LIGHT_ADDR            0xBEEF	//�ƹ�ڵ������̵�ַ

static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
//==========================================================
//	�������ƣ�	appSwitch()
//
//	�������ܣ�	���ݷ��ͺ�����������������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appSwitch(void)
{    
    basicRfConfig.panId      = PAN_ID;     //PANID
    basicRfConfig.channel    = RF_CHANNEL; //�ŵ�
    basicRfConfig.ackRequest = TRUE;			 //��ҪACK�ظ�
    basicRfConfig.myAddr     = SWITCH_ADDR;  // ���÷��͵�ַ
		
    if(basicRfInit(&basicRfConfig)==FAILED) //��������ͨ�Ų���
    {//������ô���
      HAL_ASSERT(FALSE);
    }

    pTxData[0] = CMD_LIGHT_CTRL;//�ƿ���������

    //����������,ֻ����
    basicRfReceiveOff();

    //���������ѭ��
    while (TRUE)
    {
        pTxData[1] = KEY_Scan(0);//����ɨ��

        switch(pTxData[1])
        {
          case S1_PRES:  //����1
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S2_PRES:  //����2
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S3_PRES:  //����3
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S4_PRES:  //����4
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          default: break;
        }
        
        delay_ms(100);//100ms���һ�ΰ���
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
		KEY_Init();   //��ʼ��LEDģ���ϵİ���
    // Initalise hal_rf Ӳ�������� rf ���г�ʼ��
    if(halRfInit()==FAILED)
    {
      HAL_ASSERT(FALSE);
    }
    appSwitch();        //�ڵ�Ϊ����    
}
