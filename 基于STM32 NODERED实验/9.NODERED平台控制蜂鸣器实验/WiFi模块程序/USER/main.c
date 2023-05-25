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
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-03-19
*
*	�汾�� 		V2.0
*
*	˵���� 		WiFi����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint32_t SensorData[3]={0};
uint8_t SendBuffer[16];
uint16_t Beep_Ctrl = 0;
int main(void)
{
    HAL_Init();             				//��ʼ��HAL��  
    Rs485_Init();										//��ʼ��485
    UART1_Init(115200);							//��ʼ������1 485����ʹ��
    UART2_Init(115200);							//��ʼ������2
    USART3_Init(115200);						//���Դ���   
    printf("this usart3 print\r\n");
    WiFi_Init();											//��ʼ��WiFi��������OneNET
    while(1)
    {
        if(USART2_RX_STA){
            HAL_Delay(50);//��ʱ50ms�ȴ��������
            printf("get cmd=%s\r\n",USART2_RX_BUF);//���Դ�ӡ
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$BEEP,1")){//�̵���1 ��
                Beep_Ctrl = 1;//�򿪼̵�����������
                Rs485_Send(Addr_WiFi,Addr_BEEP,BEEP_CTRL,1,(void*)&Beep_Ctrl);//����������Ƽ̵���1             
            }
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$BEEP,0")){//�̵���1 �ر�
                Beep_Ctrl = 0;//�رռ̵�����������
                Rs485_Send(Addr_WiFi,Addr_BEEP,BEEP_CTRL,1,(void*)&Beep_Ctrl);//����������Ƽ̵���1             
            }            
            USART2_RX_STA = 0;//��մ��ڽ��ռ�����
            memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);//��ս��ջ���
        }
    }
}





