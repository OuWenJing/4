#ifndef WIFIGATE_H
#define WIFIGATE_H
#include "hal_types.h"
#include "SampleApp.h"
#include "string.h"
#include "stdio.h"
#include "hal_uart.h"
#include "OSAL.h"
#include <ioCC2530.h>
#include "delay.h"

#define WIFI_PROCESS_PRODIC         0x0001  


#define WiFi_RES P1_5  //����P1.5��ΪRES���ƶ�
#define WiFi_LED P1_6  //����P1.6��ΪLED���ƶ�
#define WiFi_KEY P1_7  //����P1.7��ΪKEY���ƶ�

#define WiFi_KEY_Read()   WiFi_KEY  //����

#define WiFi_LED_HI {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;\
        WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define WiFi_LED_LO {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;\
        WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define OneNET_IP                 "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"   //���������д��ȷ�ķ�����IP�Ͷ˿�
#define WIFI_AP                   "AT+CWJAP=\"zkk_2.4g\",\"18696560024\"\r\n"        //���������д��ȷ��SSID������
#define CIPMODE       			   "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND         		   "AT+CIPSEND\r\n"																	//��ʼ����
//#define CONNECT_ONENET_KEYSTRING  "*213941#0001#sample*"                        //�Ѿ�ָ�򱾵�NODERED���Ͳ�����ִ��ONENET
#define SEND_TO_WIFI(d,l)        HalUARTWrite(HAL_UART_PORT_0,d,l);
enum{
    WIFI_RSP_NULL,//��ʱ��û�з������ݣ�
    WIFI_RSP_TIMEOUT,//�ȴ�һ��ʱ��ʲô��û��
    WIFI_RSP_OK,//�õ��������ݣ����ǲ�һ������Ҫ�ġ�
    WIFI_RSP_0D0A,
    WIFI_RSP_CONNECT
}; 

extern uint8  WiFiModeInitDone;
extern uint8 WiFiGate_TaskId;
uint16 WiFiGate_ProcessEvent( uint8 task_id, uint16 events );
void WiFiGate_Init( uint8 task_id );
uint8 SendToWiFiNetwork(uint8 *pData,uint8 len);
extern void WiFi_LED_REST(void);
extern void WiFi_Set_White(void);
extern void WiFi_LED_SET(uint32 G8R8B8);
#endif