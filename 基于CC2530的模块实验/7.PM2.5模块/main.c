#include "OLED.h"
#include "PM2p5.h"
#include "string.h"
#include "delay.h"
#include "stdio.h"
#include "USART.h"
#define SAMPLE_SIZE 20
void bubbleSort(int arr[], int n);//�����㷨
void Hal_Init_32M(void);//����ʱ�ӳ�ʼ����32M��Ƶ�ʣ�16M��ʱ��Ƶ�ʡ�
void Delay_280us(void);
void Dealy_10ms(void);
int PM2P5_ADC[SAMPLE_SIZE],PM2P5_ADC_Count = 0;
uint8_t OLED_DispBuf[16];
float voltage = 0;

void main(void)
{
  uint16_t ADC_Sum,ADC_Value,i;
	uint16_t PM2p5_ugm3 = 0;
	uint8_t  tmpbuf[16];
	uint16_t PM2p5_Data,ADC_Data;
	Hal_Init_32M(); //��ʼ��ϵͳʱ��32M
	USRT0_Init();   //��ʼ������1������͸�9600bps
	printf("this is uart0 print\r\n");
	OLED_Init();   //OLED ����ʼ��
	PM2p5_Init();  //PM2.5ģ���ʼ������ʼADC�ɼ���������ʹ�ܿ���IO
	while(1){
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
		sprintf(OLED_DispBuf,"PM2.5=%d ug/m3 ",PM2p5_ugm3);//ת���ַ���
		OLED_P8x16Str(0,4,OLED_DispBuf);//OLED����ʾ
		delay_ms(500);
	}
}
//==========================================================
//	�������ƣ�	Hal_Init_32M()
//
//	�������ܣ�	32Mʱ�ӳ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Hal_Init_32M(void)
{
    CLKCONCMD &= ~0x40;         // ����ϵͳʱ��ԴΪ 32MHZ����
    while(CLKCONSTA & 0x40);    // �ȴ������ȶ�
    CLKCONCMD &= ~0x47;         // ����ϵͳ��ʱ��Ƶ��Ϊ 32MHZ
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