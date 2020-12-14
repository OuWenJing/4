#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "WiFi.h"
#include "WS2812B.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-04-22
*
*	�汾�� 		V1.0
*
*	˵���� 		WiFi����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint8_t Send_OneNET_Buffer[32];
uint8_t Temp,Humi;
uint32_t Ticks_SendOnenET=0;
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);						    //��ʼ������1
	UART2_Init(115200);						    //��ʼ������2
    USART3_Init(115200);                        //�������Դ���
    printf("this is usart3 print\r\n");
    WS2812B_Init();                             //��ʼ��ȫ�ʵ�WS2812B
	
    WiFi_Init();							    //��ʼ��WiFi
	TIM2_Init(1000-1,64-1);						//��ʼ����ʱ��2(1ms)
    Ticks_SendOnenET = HAL_GetTick() + 2000;
    Temp = 16;
    Humi = 60;
	while(1)
	{
        if(HAL_GetTick() > Ticks_SendOnenET){
            sprintf((char *)Send_OneNET_Buffer,"%d%d",Temp,Humi);
            HAL_UART_Transmit(&UART2_Handler,Send_OneNET_Buffer,strlen((const char*)Send_OneNET_Buffer),1000);	//�������ݵ�OneNET
            
            Temp++;
            if(Temp>60){
                Temp = 16;
            }
            Humi++;
            if(Humi>90){
                Humi = 60;
            }
            printf("send onenet again\r\n");
            Ticks_SendOnenET = HAL_GetTick() + 2000;
        }
	}
}






