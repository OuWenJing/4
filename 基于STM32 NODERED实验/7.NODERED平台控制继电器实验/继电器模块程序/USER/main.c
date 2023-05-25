#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Relay.h"
#include "Rs485.h"
#include "delay.h"
#include "USART.h"
/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-11
*
*	版本： 		V2.0
*
*	说明： 		继电器程序
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
uint8_t RelayState = 0;
uint16_t RelayCMD = 0;
int main(void)
{
    HAL_Init();        //初始化HAL库  
    Relay_Init();   	//初始化继电器
    Rs485_Init();		//初始化485
    UART1_Init(115200);	//初始化串口1,用于485通信
    USART3_Init(115200);
    printf("this usart3 print\r\n");
	while(1)
	{
      HAL_Delay(10);//延时10ms每10ms检测一次指令
      if(!DataHandling_485(Addr_Relay)){//是发给本机的指令
          printf("get data\r\n"); 
					RelayCMD=Rx_Stack.Command;
          //RelayState = Rx_Stack.Data[0];//控制指令
          if(RelayCMD==Relay1_ON){
              RELAY1_OPEN();//继电器1开 
          }
          else if(RelayCMD==Relay1_OFF)
						{
              RELAY1_CLOSE();//继电器1关                 
          }
          else if(RelayCMD==Relay2_ON)
						{
              RELAY2_OPEN();//继电器2                
          }
          else if(RelayCMD==Relay2_OFF)
						{
              RELAY2_CLOSE();//继电器2关                 
          }
      }        
	}
}




