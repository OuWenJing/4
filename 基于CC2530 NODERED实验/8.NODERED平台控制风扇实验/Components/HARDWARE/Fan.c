#include "Fan.h"
void FanOff(void);
/*
初始化风扇控制IO
*/
void Fan_Init(void)
{
   P0SEL &= ~0x02; //GPIO功能
   P0DIR |= 0x02;      //P0.1定义为输出
   //P0OUTP &= ~0x02;     //打开P0.0、P0.1上拉电阻
   FanOff();
}
/*
控制风扇转动
*/
void FanOn(void)
{
  Fan = 1;
}
/*
控制风扇停止
*/
void FanOff(void)
{
  Fan = 0;
}