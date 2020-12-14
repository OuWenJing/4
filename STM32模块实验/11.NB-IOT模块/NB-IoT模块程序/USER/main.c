#include "stm32f1xx_hal.h"
#include "MsgHandler.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "M5310.h"
#include "nbiot.h"
#include "utils.h"
#include "coap.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-04-18
*
*	�汾�� 		V1.0
*
*	˵���� 		����NB-IoT������ʪ�ȴ�����ʵ��
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/
const char endpoint_name[] = "865820034613336;460043579906277";
uint32_t Ticks_SendData=0;
uint8_t SendOneNET[32];
float temp=5,humi=5;
void Platform_LED_Init(void);
void Platform_LED_Blue(void);
void Platform_LED_Green(void);
void Platform_LED_Red(void);
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	Rs485_Init();								//��ʼ��485
    Platform_LED_Init();
	M5310_Power_Init(); 						//M5310�ĸ�λ����IO��ʼ��
	UART1_Init(115200);							//��ʼ������1
	UART2_Init(9600);							//��ʼ������2
	netdev_init();      						//��ʼ��M5310
    init_miplconf(86400,coap_uri,endpoint_name);//�ϱ�ע����
	Subscription_esources();					//���� Object ������
	m5310_register_request();         //������½����
	delay_ms(1000);
	TIM2_Init(1000-1,64-1);						//��ʼ����ʱ��2(1ms)
    Ticks_SendData = HAL_GetTick() + 10000; 
    Platform_LED_Green();
	while(1)
	{
		msgcode = Msg_Handler();				//�������ݽ���
		USART_Data_Send();							//�������ݷ���
        if(HAL_GetTick() > Ticks_SendData){
			memset((void*)SendOneNET,0,10);
			sprintf((char *)SendOneNET,"%0.2f",temp);
			m5310_notify_upload(&temp_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);	//�ϴ��¶�����
			
			memset((void*)SendOneNET,0,10);
			sprintf((char *)SendOneNET,"%0.2f",humi);
			m5310_notify_upload(&humi_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);	//�ϴ�ʪ������
            Ticks_SendData = HAL_GetTick() + 5000; //5����ڴη���
            humi++;
            if(humi>50){
                humi = 30;
            }
            temp++;
            if(temp>60){
                temp = 10;
            }
        }
	}
}
void Platform_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_AFIO_CLK_ENABLE();	
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); 

    __HAL_RCC_GPIOB_CLK_ENABLE();           	                
    __HAL_RCC_GPIOA_CLK_ENABLE();           	              

    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	                
    GPIO_Initure.Pull  = GPIO_PULLUP;          	                
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	       

    GPIO_Initure.Pin   = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15; 	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    GPIO_Initure.Pin   = GPIO_PIN_15; 	                        	 	            
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);


    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15                      ,GPIO_PIN_SET);   
}
void Platform_LED_Blue(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
}
void Platform_LED_Red(void)
{
     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3            ,GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_15,GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15           ,GPIO_PIN_SET);
}
void Platform_LED_Green(void)
{
     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15          ,GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_SET);
}






