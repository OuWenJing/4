#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "FAN.h"
#include "Rs485.h"
#include "delay.h"
#include "USART.h"
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
uint8_t RelayState = 0;
int main(void)
{
    HAL_Init();        //��ʼ��HAL��  
    /*PWMռ�ձ�100%~0%,�ֱ��Ӧ��2000~0*/
    TIM4_PWM_Init(64-1,2000-1);			//��ʼ����ʱ��4���PWM�ź�
    Rs485_Init();		//��ʼ��485
    UART1_Init(115200);	//��ʼ������1,����485ͨ��
    USART3_Init(115200);
    printf("this usart3 print\r\n");
	while(1)
	{
      HAL_Delay(10);//��ʱ10msÿ10ms���һ��ָ��
      if(!DataHandling_485(Addr_Fan)){//�Ƿ���������ָ��
          printf("get data\r\n"); 
          RelayState = Rx_Stack.Data[0];//����ָ��
          if(RelayState==1){
              PWM_SetTIM4Compare2(5000);//���ȴ� 
          }
					else if(RelayState==2)
					{
						PWM_SetTIM4Compare2(2000);//���ȴ�
					}
					else if(RelayState==3)
					{
						PWM_SetTIM4Compare2(500);//���ȴ�
					}
          else{
              PWM_SetTIM4Compare2(0);//���ȹر�                
          }
      }        
	}
}




