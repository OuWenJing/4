/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-25
*
*	版本： 		V2.0
*
*	说明： 		定时器--LED控制实验
*
*	修改记录：	
************************************************************
************************************************************  
************************************************************
**/
#include <ioCC2530.h>
#include "delay.h"
#include "Time.h"
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
	uint8_t state = 0;
	Hal_Init_32M();   //初始化系统时钟32M
	LED_Init();       //初始化LED模块LED灯控制接口
	Init_Timer1();    //定时器初始化中断周期为1000KHZ，即周期1ms
	
	while(1)
	{     
		/*count 在定时器1中断服务函数中计数*/
		if(count>=1000)   //5秒
		{
			count  = 0;//清0，从0开始计数
			state = 1 - state;
			if(state == 1){
				LED_ON();
			}
			else if(state == 0){
				LED_OFF();
			}          
		}//if(count>=5000)
	}
}
//==========================================================
//	函数名称：	Timer1_Sevice()
//
//	函数功能：	定时器1服务函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		Timer1_Sevice这个名字是可以修改。
//==========================================================
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(void)
{
  T1STAT &= ~0x01;      //清除定时器1通道0中断标志
  count++;
}