#include "beep.h"
//==========================================================
//	�������ƣ�	Beep_Init()
//
//	�������ܣ�	��ʼ������������IO
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Beep_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();           				//����GPIOAʱ��

    GPIO_Initure.Pin   = GPIO_PIN_7; 						//PA7
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	//����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
  
    BEEP_IO_LOW();//������IOĬ�������
}
//==========================================================
//	�������ƣ�	void Beep_On(uint16_t ms)
//
//	�������ܣ�	���ݲ���ms����������msʱ��
//
//	��ڲ�����	@ms,�������춯ʱ�䳤��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Beep_ON(uint16_t ms)
{
    while(ms){
        ms--;
        HAL_Delay(1);
        BEEP_IO_TOGGLE();
    }
}
//==========================================================
//	�������ƣ�	void Beep_OFF(void)
//
//	�������ܣ�	ֹͣ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Beep_OFF(void)
{
    BEEP_IO_LOW();
}
