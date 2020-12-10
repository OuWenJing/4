#include "stm32f1xx.h"
#include "led.h"
#include "key.h"

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
*	˵���� 		IO���뺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
    static uint8_t key = 0;  
    HAL_Init();       //��ʼ��HAL�⣬Ϊ����õ���HAL_Delay()�����ṩʱ�ӡ�
    LED_Init();				//��ʼ��LED�ƿ��Ƶ�IO��	
    KEY_Init();				//��ʼ�����������IO��

    while(1)
    {
        key = KEY_Scan();//��ȡ����      
        switch(key)
        {
              case S1_PRES:
                HAL_GPIO_TogglePin(LED_PORT,LED1_PIN);	//S1 ���£���תLED1��״̬
                break;
              case S2_PRES:
                HAL_GPIO_TogglePin(LED_PORT,LED2_PIN);	//S2 ���£���תLED2��״̬
                break;
              case S3_PRES:
                HAL_GPIO_TogglePin(LED_PORT,LED3_PIN);	//S3 ���£���תLED3��״̬
                break;
              case S4_PRES:
                HAL_GPIO_TogglePin(LED_PORT,LED4_PIN);	//S4 ���£���תLED4��״̬
                break;
              default:break;
        }
    }
}



