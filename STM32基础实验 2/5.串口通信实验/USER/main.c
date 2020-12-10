#include "stm32f1xx.h"
#include "UART.h"
#include "LED.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-01-19
*
*	�汾�� 		V2.0
*
*	˵���� 		����2ͨ��ʵ��-HAL��汾
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/
#define UART2_RX_SIZE  32 //����2���ջ���Ĵ�С
uint8_t UART2_RxBuf[UART2_RX_SIZE];  //����2���յ�����
uint8_t UART2_RxCnt = 0;  //����2���ռ���
char *usage="LED3 on->����LED3\r\nLED3 off->Ϩ��LED3\r\n";
int main(void)
{
    HAL_Init();				    //��ʼ��HAL�⣬Ϊ����õ���HAL_Delay()�����ṩʱ�ӡ�    
    UART2_Init(115200);   //����1������115200
    LED_Init();           //ֻ��ʼ����LED3  
    HAL_UART_Transmit(&UART2_Handler,(uint8_t*)usage,strlen(usage),10);//��ӡʹ�÷���
    while(1)
    {
        if(UART2_RxCnt){
            HAL_Delay(100);
            HAL_UART_Transmit(&UART2_Handler,UART2_RxBuf,UART2_RxCnt,10);
            if(strstr((void*)&UART2_RxBuf[0],"LED3 on")){//�յ�LED3 onָʾ������LED3
                LED3_ON();
            }
            if(strstr((void*)&UART2_RxBuf[0],"LED3 off")){//�յ�LED3 offָʾ��Ϩ��LED3
                LED3_OFF();
            }            
            UART2_RxCnt = 0;
        }
    }
}
//==========================================================
//	�������ƣ�	USART2_IRQHandler()
//
//	�������ܣ�	����2�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵��������2�Ľ����жϣ��������ֲ��������޸ġ�
//==========================================================
void USART2_IRQHandler(void)
{
    uint8_t res;
    if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET)){  
        /*�Ǵ��ڵĽ����ж�*/
        res = USART2->DR;
        UART2_RxBuf[UART2_RxCnt++] = res;
      
        if(UART2_RxCnt > (UART2_RX_SIZE-1)){//����������ݴ��ڻ�������UART2_RxCnt���㡣
            UART2_RxCnt = 0;
        }
    }
    HAL_UART_IRQHandler(&UART2_Handler);//����жϱ�־λ
}



