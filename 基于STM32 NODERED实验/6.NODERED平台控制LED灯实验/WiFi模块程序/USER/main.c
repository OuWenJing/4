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
uint16_t LED_Ctrl = 0;
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
        if(USART2_RX_STA>8){
            HAL_Delay(50);//��ʱ50ms�ȴ��������
            printf("get cmd=%s\r\n",USART2_RX_BUF);//���Դ�ӡ
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED1,1")){//LED1 ��
                LED_Ctrl = 1;//������������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_ON1,1,(void*)&LED_Ctrl);//�����������LED1              
            }
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED1,0")){//LED1 ��
                LED_Ctrl = 0;//�����������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_OFF1,1,(void*)&LED_Ctrl);//�����������LED1                
            }    
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED2,1")){//LED2 ��
                LED_Ctrl = 1;//������������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_ON2,1,(void*)&LED_Ctrl);//�����������LED2              
            }
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED2,0")){//LED2 ��
                LED_Ctrl = 0;//�����������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_OFF2,1,(void*)&LED_Ctrl);//�����������LED2                
            } 
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED3,1")){//LED3 ��
                LED_Ctrl = 1;//������������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_ON3,1,(void*)&LED_Ctrl);//�����������LED3              
            }
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED3,0")){//LED3 ��
                LED_Ctrl = 0;//�����������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_OFF3,1,(void*)&LED_Ctrl);//�����������LED3                
            }
            if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED4,1")){//LED4 ��
                LED_Ctrl = 1;//������������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_ON4,1,(void*)&LED_Ctrl);//�����������LED4              
            }
            else if(strstr((void*)&USART2_RX_BUF[0],(const char*)"$LED4,0")){//LED4 ��
                LED_Ctrl = 0;//�����������
                Rs485_Send(Addr_WiFi,Addr_LED,LED_OFF4,1,(void*)&LED_Ctrl);//�����������LED1                
            }						
            USART2_RX_STA = 0;//��մ��ڽ��ռ�����
            memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);//��ս��ջ���
        }
    }
}





