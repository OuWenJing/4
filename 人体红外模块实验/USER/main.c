#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "PIR.h"


int main(void)
{
  HAL_Init();						//��ʼ��HAL�� 
	PIR_Init();						//��ʼ���������

	while(1)
	{
		if(PIR_Read())
		{
			PIR_LED_ON();
		}
		else
		{
			PIR_LED_OFF();
		}
	}
}

