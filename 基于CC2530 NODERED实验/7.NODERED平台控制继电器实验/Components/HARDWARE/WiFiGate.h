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


#define WiFi_RES P1_5  //定义P1.5口为RES控制端
#define WiFi_LED P1_6  //定义P1.6口为LED控制端
#define WiFi_KEY P1_7  //定义P1.7口为KEY控制端

#define WiFi_KEY_Read()   WiFi_KEY  //按键

#define WiFi_LED_HI {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;\
        WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define WiFi_LED_LO {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;\
        WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define OneNET_IP                 "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"   //这里必须填写正确的服务器IP和端口
#define WIFI_AP                   "AT+CWJAP=\"zkk_2.4g\",\"18696560024\"\r\n"        //这里必须填写正确的SSID和密码
#define CIPMODE       			   "AT+CIPMODE=1\r\n"																//透传
#define CIPSEND         		   "AT+CIPSEND\r\n"																	//开始传输
//#define CONNECT_ONENET_KEYSTRING  "*213941#0001#sample*"                        //已经指向本地NODERED，就不必再执行ONENET
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
extern void WiFi_LED_REST(void);
extern void WiFi_Set_White(void);
extern void WiFi_LED_SET(uint32 G8R8B8);
#endif