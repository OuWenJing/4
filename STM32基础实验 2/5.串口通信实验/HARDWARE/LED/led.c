#include "led.h"
#include "stm32f1xx.h"

//==========================================================
//	�������ƣ�	LED_Init
//
//	�������ܣ�	LED�Ƴ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		����LED�ƿ���IO�����
//==========================================================
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
  
    LED_IO_RCC();

    GPIO_Initure.Pin   = LED3_PIN;
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	  //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	  //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	  //����
    HAL_GPIO_Init(LED_PORT,&GPIO_Initure);
	
    LED_OFF();///��ʼ�����ȫ��LED����
}



