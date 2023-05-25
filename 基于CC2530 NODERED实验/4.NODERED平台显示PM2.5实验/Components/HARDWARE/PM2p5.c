#include "ioCC2530.h"      
#include "stdio.h"
#include "PM2p5.h"
#include "sampleApp.h"
#define SAMPLE_SIZE 20
static uint16_t ADC_Sum,ADC_Value,i;
static uint16_t PM2p5_ugm3 = 0;
static int PM2P5_ADC[SAMPLE_SIZE],PM2P5_ADC_Count = 0;
float voltage = 0;
//==========================================================
//	�������ƣ�	void PM2p5_Init(void)
//
//	�������ܣ�	��ʼPM2.5ģ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PM2p5_Init(void)
{
	APCFG |= BV(2);	
	P0SEL |= BV(2);        //Ƭ������
	P0DIR &= ~(BV(2));    //��������ģʽ	
	
	P1SEL &= ~BV(0);
	P1DIR |= BV(0);
	PM2P5_LED_ENABLE();
}
//==========================================================
//	�������ƣ�	uint16 PM2p5_ADC(void)
//
//	�������ܣ�	PM2.5ģ���ADC�ɼ�ֵ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint16 PM2p5_ADC(void)
{
	short value=0;
	ADCCON3 = (0x80 | 0x30 | 0x02);
	ADCCON1 |= 0x30;     //ѡ��ADC������ģʽΪ�ֶ�
	ADCCON1 |= 0x40;       //����ADת��             
	
	while(!(ADCCON1 & 0x80));    //�ȴ�ADCת������
	
	value  =  ADCL;
	value |= (ADCH << 8);    //ȡ������ת�����������value��  
	if(value<0){
		value = 0;
	}
	value  = value>>4;	
	return value;
}
//==========================================================
//	�������ƣ�	void Delay_280us(void)
//
//	�������ܣ�	280us��ʱ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Delay_280us(void)
{
	volatile int count = 100;
	while(count--);
}
//==========================================================
//	�������ƣ�	void Dealy_10ms(void)
//
//	�������ܣ�	10ms��ʱ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Dealy_10ms(void)
{
	volatile int  count = 4300;
	while(count--);
}
//==========================================================
//	�������ƣ�	void bubbleSort(int arr[], int n)
//
//	�������ܣ�	ʵ����С�������
//
//	��ڲ�����	@arr��Ҫ�������������
//					    @n,����������С
//
//	���ز�����	��
//
//	˵����		
//==========================================================
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
uint16_t PM2p5_Read(void)
{
		/*���вɼ�*/
		for(PM2P5_ADC_Count = 0;PM2P5_ADC_Count<SAMPLE_SIZE;PM2P5_ADC_Count++){
			PM2P5_LED_ENABLE();
			Delay_280us();//��ʱ280us
			PM2P5_ADC[PM2P5_ADC_Count++] = PM2p5_ADC();//ADCֵ���浽������
			PM2P5_LED_DISABLE();
			Dealy_10ms();//��ʱ10ms
		}
		bubbleSort(&PM2P5_ADC[0], PM2P5_ADC_Count);//����
		ADC_Sum = 0;        
		for(i=1;i<(SAMPLE_SIZE-1);i++){//ȥ�����������е����ֵ���ߵ�ֵ
			ADC_Sum += PM2P5_ADC[i];
		}
		ADC_Value  = ADC_Sum / (SAMPLE_SIZE-2);//��ȥ������С������	
		voltage    = (ADC_Value/2048.0)*3.3;//��ADCֵת����PM2.5ֵ(ug/m3)
		PM2p5_ugm3 = voltage*0.13*1000;
		printf("PM2p5_ugm3=%d ug/m3\r\n",PM2p5_ugm3);   //���Դ�ӡ
		return PM2p5_ugm3;
}