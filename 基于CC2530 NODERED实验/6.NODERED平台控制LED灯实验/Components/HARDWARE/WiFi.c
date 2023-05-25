#include "Usart.h"	
#include "delay.h"
#include "WiFi.h"

//==========================================================
//	函数名称：	WiFi_Init()
//
//	函数功能：	初始化WiFi
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void WiFi_Init(void)
{
    WiFi_Send_Cmd(CLOSE_TCP,"",5);			/*退出WiFi透传模式*/

    delay_ms(3000);

    while(!WiFi_Send_Cmd(AT,"OK",20));		        /*进入AT命令模式*/														//显示电源状态
    
    while(!WiFi_Send_Cmd(CWMODE,"OK",30));		/*设置模块应用模式*/													//显示电源状态

//    while(!WiFi_Send_Cmd(RST,"",80));		        /*重置模块*/															//显示电源状态
//
//    while(!WiFi_Send_Cmd(CIFSR,"OK",30));;		/*查询设备IP可放在需要的位置*/															//显示电源状态

    while(!WiFi_Send_Cmd(CWJAP,"OK",300));		/*配置要连接的路由器的SSID和密码*/																			/*LED2亮*/

    while(!WiFi_Send_Cmd(TCP_CIPSTART,"OK",60));	/*与服务器建立TCP连接*/																			/*LED3亮*/

    while(!WiFi_Send_Cmd(CIPMODE,"OK",60));		/*透传模式*/
    
    while(!WiFi_Send_Cmd(CIPSEND,"OK",30));		/*开始传输*/																			/*LED4亮*/
    
    //while(!WiFi_Send_Cmd(CIPSTATUS,"",30));		/*连接设备*/
    
    WiFi_AT_STA = 1;           			        /*AT指令发送完成标志位*/	
}


