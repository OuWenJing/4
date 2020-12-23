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
            LED_State = Rx_Stack.Data[0];//LED1������
            if(LED_State){
                LED1_ON(); //LED1 ��
            }
            else{
                LED1_OFF();//LED2 ��                 
          }
        }        
    }
}




