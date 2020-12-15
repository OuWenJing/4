#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "ADC.h"
#include "pwm.h"
#include "timer.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-18
*
*	�汾�� 		V2.0
*
*	˵���� 		PM2.5
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
/*
�ڵ�ѹС��3.5v����0.5�������  ����ѹ��Ũ�ȳ�һ�����ͱ����ġ�

Ũ��N= K* V;

K=N/V.Լ����0.13��

��������stm32��12λ��ADC�ɼ���ֵ���ȱ�ɵ�ѹ����value*3300/4096���ǵ�ѹֵ��Ȼ�����0.13��õ�mg/m3��
*/
uint32_t Data = 0;
void PA_CTRL_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();						//����GPIOAʱ��

    GPIO_Initure.Pin=GPIO_PIN_1;          	//PA1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�����������
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW; //����

    HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
    GPIOA->BRR = GPIO_PIN_1;
}
/*
�����㷨
*/
void bubbleSort(int arr[], int n)
{
    int i, j, tmp;

    for(i = 0; i < n - 1; i++){
        for(j = 1; j < n; j++){
            if(arr[j] < arr[j - 1]){
                tmp        = arr[j];
                arr[j]     = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
}
uint8_t PM_Data[10];
#define SAMPLE_SIZE 20
int PM2P5_ADC[SAMPLE_SIZE],PM2P5_ADC_Count = 0;
uint16_t PM25_ugm3;
int main(void)
{
  float voltage;
  int i = 0;
  
  HAL_Init();             			//��ʼ��HAL��
  ADC_Init();										//��ʼ��ADC���ɼ��������������ź�
  Rs485_Init();									//��ʼ��485
  UART1_Init(115200);						//��ʼ������1 485����ʹ��
  UART3_Init(115200);						//��ʼ������3�����ڵ���
  PA_CTRL_Init();
  TIM3_Init(65530,640-1,(void*)0);//����ʱ��10us

	while(1)
	{
        for(PM2P5_ADC_Count = 0;PM2P5_ADC_Count < SAMPLE_SIZE;PM2P5_ADC_Count++){
            /*ADCȡ��*/
            GPIOA->BSRR = GPIO_PIN_1;
            TIM3_DelayUS(28);//280us
            PM2P5_ADC[PM2P5_ADC_Count] = Get_Adc(ADC_CHANNEL_3);
            TIM3_DelayUS(1);//10us
            GPIOA->BRR = GPIO_PIN_1;
            TIM3_DelayUS(980);//9800us 
        }     
        bubbleSort(&PM2P5_ADC[0],SAMPLE_SIZE);//������ֵС����ǰ��
        Data = 0;        
        for(i=1;i<(SAMPLE_SIZE-1);i++){//ȥ�����������е����ֵ���ߵ�ֵ
            Data += PM2P5_ADC[i];
        }
        Data = Data / (SAMPLE_SIZE-2);//��ȥ������С������
        voltage = (Data / 4096.0)*3.3;//ת���ɵ�ѹֵ
        
        PM25_ugm3 = (voltage*0.13)*1000;//��λ ug/m3  
        
        /*ת�����ݣ�ͨ��485���߷������ݵ���ʾ����ʾ*/ 
        PM_Data[0] = PM25_ugm3>>8;PM_Data[1] = PM25_ugm3;
        Rs485_Send(Addr_PM2_5,Addr_LCD,PM2_5_Conc,2,PM_Data);	
        
        memset(PM_Data,0,10);//�������
        HAL_Delay(500);//ÿ500ms�ɼ�һ��
	}
}



