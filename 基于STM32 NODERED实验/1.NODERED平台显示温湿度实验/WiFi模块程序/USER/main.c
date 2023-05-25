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

uint32_t CPU_ID[3];

void Get_ChipID(void)
{
	CPU_ID[0] = *(__IO uint32_t *)(0X1FFFF7F0); // 高字节
	CPU_ID[1] = *(__IO uint32_t *)(0X1FFFF7EC); // 
	CPU_ID[2] = *(__IO uint32_t *)(0X1FFFF7E8); // 低字节
	
	/* 芯片的唯一ID */
	printf("\r\n芯片的唯一ID为: %08X-%08X-%08X\r\n",CPU_ID[0],CPU_ID[1],CPU_ID[2]);
}


int main(void)
{
    HAL_Init();             				//初始化HAL库  
	//Get_ChipID();
    Rs485_Init();										//初始化485
    UART1_Init(115200);							//初始化串口1 485总线使用
    UART2_Init(115200);							//初始化串口2
    USART3_Init(115200);						//调试串口   
    printf("this usart3 print\r\n");
    WiFi_Init();											//初始化WiFi，并连接OneNET  
    /*中断频率2HZ 关联回调函数RS485_HandlerCb*/
    TIM3_Init(10000-1,3200-1,RS485_HandlerCb);  
    while(1)
    {
        HAL_Delay(3000);//延时3秒，3钟更新一次
        /*转成字符串*/
        sprintf((void*)&SendBuffer[0],"%02d%02d",SensorData[0],SensorData[1]);
        WiFi_SerialSend(&SendBuffer[0],4);//发送到OneNET
        printf("传感器数据==%d,%d,%d\r\n",SensorData[0],SensorData[1],SensorData[2]);//调试打印
    }
}
//==========================================================
//	函数名称：	void RS485_HandlerCb(void)
//
//	函数功能：	通过485总线获取数据处理函数
//
//	入口参数：	void
//
//	返回参数：	无
//
//	说明：		接收通过485总线发送过来的数据请求
//==========================================================
void RS485_HandlerCb(void)
{
    static uint8_t state = 0;
  if(state == 0){//发送请求
        Rs485_Send(Addr_WiFi,Addr_SHT20,SHT20_Get_All,0,(void*)0);
        printf("请求传感器数据\n");
        state = 1;
    }
    else{//检测是否返回数据
        if(!DataHandling_485(Addr_WiFi)){	//是本机期望的485数据处理
              printf("get data\r\n");
              SensorData[0] = Rx_Stack.Data[0];
              SensorData[1] = Rx_Stack.Data[1];            
              SensorData[2] = (Rx_Stack.Data[2] << 8) + Rx_Stack.Data[3];
        }
        state = 0;
    }
}





