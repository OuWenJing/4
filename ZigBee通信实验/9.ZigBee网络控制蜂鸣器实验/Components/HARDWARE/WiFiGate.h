#ifndef WIFIGATE_H
#define WIFIGATE_H
#include "hal_types.h"
#include "SampleApp.h"
#include "string.h"
#include "stdio.h"
#include "hal_uart.h"
#include "OSAL.h"

#define WIFI_PROCESS_PRODIC         0x0001  

#define OneNET_IP                 "AT+CIPSTART=\"TCP\",\"183.230.40.40\",1811\r\n"
#define WIFI_AP                   "AT+CWJAP=\"bacheng\",\"f0f0f0f0f0\"\r\n"
#define CIPMODE       			   "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND         		   "AT+CIPSEND\r\n"																	//��ʼ����
#define CONNECT_ONENET_KEYSTRING  "*213941#0001#sample*"
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
#endif