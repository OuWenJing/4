#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "beep.h"
#include "Rs485.h"
#include "delay.h"
#include "USART.h"
#include "TIMER.h"
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
uint8_t BeepState = 0;
uint8_t BeepCmd = 0;
int main(void)
{
    HAL_Init();     //��ʼ��HAL��  
    Beep_Init();		//��ʼ������
    Rs485_Init();		//��ʼ��485
    UART1_Init(115200);	//��ʼ������1,����485ͨ��
    USART3_Init(115200);
    printf("this usart3 print\r\n");
    while(1)
    {
        if(!DataHandling_485(Addr_BEEP)){//�Ƿ���������ָ��
            printf("get data\r\n"); 
            BeepCmd = Rx_Stack.Data[0];//����ָ��
            if(BeepCmd){
                BeepState = 1;//�򿪷�����
            }
            else{
                BeepState = 0;//�رշ�����                
            }
        }

        if(BeepState){
            HAL_Delay(1);//��ʱ1ms��������������Ƶ��Ϊ500HZ
            BEEP_IO_TOGGLE();//������IO��ƽ��ת
        }
        else{
            BEEP_IO_LOW();//ֹͣ������
        }
    }
}




