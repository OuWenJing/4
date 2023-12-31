#include "delay.h"
#include "Fan.h"

//==========================================================
//	函数名称：	Fan_Init()
//
//	函数功能：	初始化风扇
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Fan_Init(void)
{
   P0DIR |= 0x02;   //P0.1定义为输出
   Fan = 0;         //初始化关闭风扇
}

//==========================================================
//	函数名称：	Fan_Set()
//
//	函数功能：	风扇档位调节
//
//	入口参数：	@state 0，风扇不转;1,风扇转动
//
//	返回参数：	无
//
//	说明:
//==========================================================
void Fan_Set(uint8_t state)
{
		Fan = state;
}