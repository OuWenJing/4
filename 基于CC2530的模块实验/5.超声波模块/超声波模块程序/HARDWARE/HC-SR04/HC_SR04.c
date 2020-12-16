#include "HC_SR04.h"
#include "TM1640.h"	
#include "delay.h"
#include "timer.h"
#include "math.h" 
//==========================================================
//	�������ƣ�	delay_us
//
//	�������ܣ�	΢����ʱ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void delay_us(uint32_t n)
{
  unsigned int i = 0,j = 0;
  for(i = 0;i<n;i++)
  {
      for(j = 0;j<10;j++)
      {;}
  }
}
//==========================================================
//	�������ƣ�	HCSR04_Init()
//
//	�������ܣ�	��ʼ��������ģ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HCSR04_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;
	
		__HAL_RCC_GPIOA_CLK_ENABLE();						//����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();						//����GPIOBʱ��
	
		GPIO_Initure.Pin = Echo1|Echo2|Echo3|Echo4; 	//Echo1,Echo2,Echo3,Echo4
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   	//����
		GPIO_Initure.Pull = GPIO_NOPULL;				//����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
	  GPIO_Initure.Pin=Trigl1|Trigl2|Trigl3|Trigl4; 	//Trigl1,Trigl2,Trigl3,Trigl4
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	//����
   	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
    Trigl1_LOW();	//Trigl1��ʼ����0
		Trigl2_LOW()	//Trigl2��ʼ����0
		Trigl3_LOW()	//Trigl3��ʼ����0
		Trigl4_LOW()	//Trigl4��ʼ����0	
}

//==========================================================
//	�������ƣ�	HCSR04_StartMeasure()
//
//	�������ܣ�	������ģ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		����ֵ��λcm
//==========================================================
uint16_t HCSR04_StartMeasure(uint8_t Num)
{
    static  uint8_t Flag = 1;
    static 	uint16_t i = 0,Avg = 0;
    static  uint32_t HCSR04_Distance = 0;
    
    for(i=0;i<Num;i++)
    {
        Trigl3_HIGH();			//����Trigl3
        delay_us(20);
        Trigl3_LOW();				//����Trigl3

        while(!Echo3_STATE())			//�ȴ�����
        {
            HCSR04Count = 0;
            HAL_NVIC_EnableIRQ(TIM2_IRQn);    	//����ITM2�ж�,��ʼ��ʱ
            Flag = 1;
        }

        while(Flag)														//�Ѿ���⵽�ߵ�ƽ
        {
            if(!Echo3_STATE())									//�������
            {
                HAL_NVIC_DisableIRQ(TIM2_IRQn);		//�ر�ITM2�ж�
                HCSR04_Distance	+= HCSR04Count*0.17;
                HCSR04Count = 0;
                Flag = 0;
            }
        }
        HAL_Delay(10);//��ʱ10ms�ڲ���һ��
    }
    Avg = HCSR04_Distance/Num;//���ƽ��ֵ
    HCSR04_Distance = 0;
    return Avg;//��λcm
}




