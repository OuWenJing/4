#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Relay.h"
#include "Rs485.h"
#include "delay.h"
#include "USART.h"
#include "TIMER.h"
#include "LED.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-11
*
*	�汾�� 		V2.0
*
*	˵���� 		�̵�������
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint8_t LED_State = 0;
uint16_t LED_CMD = 0;
int main(void)
{
    HAL_Init();      //��ʼ��HAL��  
    LED_Init();   	//��ʼ��ģ��
    Rs485_Init();		//��ʼ��485
    UART1_Init(115200);	 //��ʼ������1,����485ͨ��
    USART3_Init(115200); //���ڵ���
    printf("this usart3 print\r\n");
    while(1)
    {
        HAL_Delay(100);//��ʱ100ms,ÿһ100ms���һ�Ρ�
        if(!DataHandling_485(Addr_LED)){//�Ƿ�������������
            printf("get cmd\r\n=%d\r\n",Rx_Stack.Data[0]);//���Դ�ӡ
            //LED_State = Rx_Stack.Data[0];//LED1������
						LED_CMD=Rx_Stack.Command;
            if(LED_CMD==LED_ON1){
                LED1_ON(); //LED1 ��
            }
            else if(LED_CMD==LED_OFF1)
							{
                LED1_OFF();//LED1 ��                 
						}
            else if(LED_CMD==LED_ON2)
							{
                LED2_ON();//LED2                  
						}
            else if(LED_CMD==LED_OFF2)
							{
                LED2_OFF();//LED2 ��                 
						}
            else if(LED_CMD==LED_ON3)
							{
                LED3_ON();//LED3                 
						}
            else if(LED_CMD==LED_OFF3)
							{
                LED3_OFF();//LED3 ��                 
						}
            else if(LED_CMD==LED_ON4)
							{
                LED4_ON();//LED4                 
						}
            else if(LED_CMD==LED_OFF4)
							{
                LED4_OFF();//LED4 ��                 
						}
        }        
    }
}




