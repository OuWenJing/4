#ifndef __WiFi_H
#define __WiFi_H 			   

#include <ioCC2530.h>

#define	CLOSE_TCP     "+++"						//关闭TCP连接，退出透传模式
#define AT            "AT\r\n"
#define CWMODE        "AT+CWMODE=3\r\n"					//设置模式为AP+STA
#define RST           "AT+RST\r\n"					//软重启模块
#define CIFSR         "AT+CIFSR\r\n"					//查询IP地址
#define CWJAP         "AT+CWJAP=\"zkk_2.4g\",\"18696560024\"\r\n"		//设置SID和PWD连接网络
#define TCP_CIPSTART  "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"	//设置为TCP协议传输并指定IP和端口号
#define CIPMODE       "AT+CIPMODE=1\r\n"				//透传
#define CIPSEND       "AT+CIPSEND\r\n"					//开始传输
//#define CIPSTATUS     "*238724#0001#sample*"				//ONE.NET平台个人账号识别码

extern void WiFi_Init(void); //WiFi初始化

#endif

