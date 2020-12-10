#include "led.h"
#include "key.h"
#include "exti.h"
#include "stm32f1xx.h"

unsigned char Key_flag = 0;  //������־

//==========================================================
//	�������ƣ�	EXTI4_Init
//
//	�������ܣ�	�ⲿ�жϳ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI4_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();              //����GPIOAʱ��

    GPIO_Initure.Pin  = S2_PIN; 					     //����S1
    GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;   //�½��ش���,�����ް���ʱ��IO��Ϊ�ߵ�ƽ��
    GPIO_Initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(S2_PORT,&GPIO_Initure);

		HAL_NVIC_SetPriority(EXTI4_IRQn,1,1);      	//��ռ���ȼ�Ϊ1�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);            	//ʹ���ж���	
}
