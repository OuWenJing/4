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

//����ͨ�Ų���
#define RF_CHANNEL                25  // 2.4 GHz RF channel ֵ��Χ11~26
#define PAN_ID                0x2007 //PANID
#define Coordinator_ADDR      0x2520 //Э�����ĵ�ַ
#define SHT20_ADDR            0xBEEF //������ַ

#define APP_PAYLOAD_LENGTH        30

static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

static void SHT20_Node(void);   //��ʪ�Ƚڵ�

//==========================================================
//	�������ƣ�	SHT20_Node()
//
//	�������ܣ�	��ʪ�Ƚڵ�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void SHT20_Node(void)
{ 
    // ���� basicRF
    basicRfConfig.panId      = PAN_ID;      //����PANID
    basicRfConfig.channel    = RF_CHANNEL; //�����ŵ�
    basicRfConfig.ackRequest = TRUE;       //��ҪACK
    basicRfConfig.myAddr     = SHT20_ADDR;    // ���ñ�����ַ

    if(basicRfInit(&basicRfConfig)==FAILED)
    {
      HAL_ASSERT(FALSE);
    }

    //�رս���
    basicRfReceiveOff();				
    // Main loop
    while (TRUE)
    {
				/*��ȡ��ʪ��ֵ.�ֱ𱣴�g_sht2x_param.TEMP_HM��g_sht2x_param.HUMI_HM*/
        SHT2x_GetTempHumi(); 
        send_LED_Display(0xC0,(uint16_t)g_sht2x_param.TEMP_HM,1);   //��ʾ�¶�
				delay_ms(500);      //��ʱ1��    
        send_LED_Display(0xC0,(uint16_t)g_sht2x_param.HUMI_HM,2);  //��ʾʪ��
				delay_ms(500);      //��ʱ1��   

				/*��ʪ��ת�����ַ���*/
        sprintf((char *)pTxData,"Temp:%d,\tHumi:%d.\r\n", 
								(uint16_t)g_sht2x_param.TEMP_HM,(uint16_t)g_sht2x_param.HUMI_HM);
				
        basicRfSendPacket(Coordinator_ADDR, pTxData,APP_PAYLOAD_LENGTH); //������ʪ�����ݵ�Э�����ڵ�

        memset(pTxData,0,APP_PAYLOAD_LENGTH);//�������
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
    IIC_Init();           //��ʼ��IIC 
    TM1640_Init();        //��ʼ��TM1640
    // Initalise hal_rf Ӳ�������� rf ���г�ʼ��
    if(halRfInit()==FAILED)
    {
      HAL_ASSERT(FALSE);
    }
    SHT20_Node();       //��ʪ�Ƚڵ�
}
