/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-01-06
*
*	版本： 		V2.0
*
*	说明： 		流水灯实验
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

#include <ioCC2530.h>
#include "delay.h"
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
    Hal_Init_32M();   //初始化系统32M时钟
    LED_Init();       //初始化LED控制接口

    while(1)
    {
		LED1=0;       //点亮LED1
		delay_ms(500);//延时500ms
		LED1=1;		  //熄灭LED1
		
		LED2=0;		  //点亮LED2	
		delay_ms(500);//延时500ms
		LED2=1;		  //熄灭LED2
		
		LED3=0;       //点亮LED3	
		delay_ms(500);//延时500ms
		LED3=1;		  //熄灭LED3
		
		LED4=0;		  //点亮LED4		
		delay_ms(500);//延时500ms
		LED4=1;       //熄灭LED4
    }
}
