#include "stm32f1xx.h"
#include "led.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-01-19
*
*	版本： 		V2.0
*
*	说明： 		流水灯库函数操作实验-HAL库版本
*
*	修改记录：
************************************************************
************************************************************
************************************************************
**/
#define TIMEOUT_MS 300 /*亮灭的间隔时间，单位为ms*/
int main(void)
{
    HAL_Init();				//初始化HAL库，为随后用到的HAL_Delay()函数提供时钟。    
    LED_Init();				//初始化LED灯控制的IO接口	
    while(1)
    {
        LED1_ON();              //LED1亮                
        HAL_Delay(TIMEOUT_MS);  //延时 TIMEOUT_MS 毫秒，HAL_Delay()为HAL库函数提供的延时函数。      
        LED1_OFF();             //LED1灭

        LED2_ON();              //LED2亮
        HAL_Delay(TIMEOUT_MS);   //延时 TIMEOUT_MS 毫秒     
        LED2_OFF();             //LED2灭

        LED3_ON();              //LED3亮
        HAL_Delay(TIMEOUT_MS);   //延时 TIMEOUT_MS 毫秒     
        LED3_OFF();             //LED3灭

        LED4_ON();              //LED4亮
        HAL_Delay(TIMEOUT_MS);   //延时 TIMEOUT_MS 毫秒      
        LED4_OFF();             //LED4灭 
    }
}




