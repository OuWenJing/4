/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-24
*
*	版本： 		V2.0
*
*	说明： 		按键控制实验
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
#include <ioCC2530.h>
#include "delay.h"
#include "KEY.h"
#include "LED.h"

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
	static uint8_t key = 0;  
    Hal_Init_32M();   //初始化系统32M时钟
    LED_Init();       //初始化LED模块的LED灯控制接口
    KEY_Init();       //初始化LED模块的按键控制接口
    while(1)
    {
		key = KEY_Scan(0);//获取按键
		
		switch(key)
		{
			case S1_PRES://按键S1按键下
				LED1 = ~LED1;
				break;
			case S2_PRES://按键S2按键下
				LED2 = ~LED2;
				break;
			case S3_PRES://按键S3按键下
				LED3 = ~LED3;
				break;
			case S4_PRES://按键S4按键下
				LED4 = ~LED4;
				break;
			default:break;
		}
    }
}
