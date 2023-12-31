/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-20
*
*	版本： 		V2.0
*
*	说明： 		蓝牙实验
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

#include <ioCC2530.h>
#include "Usart.h"
#include "Lamp.h"
#include "Ble.h"

//==========================================================
//	函数名称：	main()
//
//	函数功能：	程序入口函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void main(void)
{
    Hal_Init_32M();  //初始化32M时钟
    Init_Uart0();    //初始化串口0，连接蓝牙模块,接收数据保存在USART0_RX_BUF
    BLE_Init();     //初始化蓝牙为从机模式
	
		/*设备被连接后，返回“Connected”*/
		while(!strstr((const char*)USART0_RX_BUF,(const char*)"Connected"));
		USART0_RX_STA = 0;  //清空串口接收计数
    while(1)
    {
        if(USART0_RX_STA)//接收到数据
        {
	     	 	delay_ms(50);//延时50ms等待数据接收完成
          UR0SendString(USART0_RX_BUF); //发送接收到的数据
          USART0_RX_STA = 0;            //清空串口接收计数
          memset(USART0_RX_BUF,0,USART0_RX_SIZE);  //清空数组
        }
    }
}
