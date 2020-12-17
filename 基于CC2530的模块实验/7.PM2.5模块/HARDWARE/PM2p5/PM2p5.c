#include <ioCC2530.h>        
#include "stdio.h"
#include "PM2p5.h"
#include "typedef.h"
void PM2p5_Init(void)
{
	APCFG |= BV(2);	
	P0SEL |= BV(2);        //Ƭ������
	P0DIR &= ~(BV(2));    //��������ģʽ	
	
	P1SEL &= ~BV(0);
	P1DIR |= BV(0);
	PM2P5_LED_ENABLE();
}

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