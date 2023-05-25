#ifndef WIFIGATE_H
#define WIFIGATE_H
#include "hal_types.h"
#include "SampleApp.h"
#include "string.h"
#include "stdio.h"
#include "hal_uart.h"
#include "OSAL.h"

#define WIFI_PROCESS_PRODIC         0x0001  

#define OneNET_IP                 "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"
#define WIFI_AP                   "AT+CWJAP=\"zkk_2.4g\",\"18696560024\"\r\n"
#define CIPMODE       			   "AT+CIPMODE=1\r\n"																//透传
#define CIPSEND         		   "AT+CIPSEND\r\n"																	//开始传输

#define SEND_TO_WIFI(d,l)        HalUARTWrite(HAL_UART_PORT_0,d,l);
enum{
    WIFI_RSP_NULL,//暂时还没有返回数据，
    WIFI_RSP_TIMEOUT,//等待一段时间什么都没有
    WIFI_RSP_OK,//得到返回数据，但是不一定是想要的。
    WIFI_RSP_0D0A,
    WIFI_RSP_CONNECT
}; 

extern uint8  WiFiModeInitDone;
extern uint8 WiFiGate_TaskId;
uint16 WiFiGate_ProcessEvent( uint8 task_id, uint16 events );
void WiFiGate_Init( uint8 task_id );
uint8 SendToWiFiNetwork(uint8 *pData,uint8 len);
#endif