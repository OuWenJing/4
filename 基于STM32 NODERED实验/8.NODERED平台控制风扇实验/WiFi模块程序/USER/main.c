#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "WiFi.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-03-19
*
*	版本： 		V2.0
*
*	说明： 		WiFi控制
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint32_t SensorData[3]={0};
uint8_t SendBuffer[16];
uint16_t FAN_Ctrl = 0;
int main(void)
{
    HAL_Init();             				//初始化HAL库  
    Rs485_Init();										//初始化485
    UART1_Init(115200);							//初始化串口1 485总线使用
    UART2_Init(115200);							//初始化串口2
    USART3_Init(115200);						//调试串口   
    printf("this usart3 print\r\n");
    WiFi_Init();											//初始化WiFi，并连接OneNET
    while(1)
    {
        if(USART2_RX_STA){
            HAL_Delay(50);//延时50ms等待接收完成
            printf("get cmd=%s\r\n",USART2_RX_BUF);//调试打印
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$FAN,1")){//风扇 打开
                FAN_Ctrl = 1;//打开风扇控制命令
                Rs485_Send(Addr_WiFi,Addr_Fan,FAN_ON,1,(void*)&FAN_Ctrl);//发送命令控制风扇             
            }
						else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$FAN,2"))
						{
                FAN_Ctrl = 2;//打开风扇控制命令
                Rs485_Send(Addr_WiFi,Addr_Fan,FAN_ON,1,(void*)&FAN_Ctrl);//发送命令控制风扇  
						}
						else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$FAN,3"))
						{
                FAN_Ctrl = 3;//打开风扇控制命令
                Rs485_Send(Addr_WiFi,Addr_Fan,FAN_ON,1,(void*)&FAN_Ctrl);//发送命令控制风扇  
						}
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$FAN,0")){//风扇 关闭
                FAN_Ctrl = 0;//关闭风扇控制命令
                Rs485_Send(Addr_WiFi,Addr_Fan,FAN_OFF,1,(void*)&FAN_Ctrl);//发送命令控制风扇             
            }            
            USART2_RX_STA = 0;//清空串口接收计数器
            memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);//清空接收缓冲
        }
    }
}





