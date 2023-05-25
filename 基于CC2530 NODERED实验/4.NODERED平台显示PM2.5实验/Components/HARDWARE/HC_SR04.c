#include "HC_SR04.h"
#include "TM1640.h"	
#include "delay.h"
#include "Time.h"

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
    P0SEL &= ~0x03;     //����P0.0��P0.1��ͨIO��  
    P1SEL &= ~0xF3;     //����P1.0��P1.1��P1.4��P1.5��P1.6��P1.7Ϊ��ͨIO�� 
    
    P0DIR |= 0x01;      //P0.0����Ϊ���
    P1DIR |= 0x62;      //P1.1��P1.5��P1.6����Ϊ���
    
    P0DIR &= ~0x02;     //��P0.1Ϊ����ģʽ 
    P0INP &= ~0x02;     //��P0.1��������
    P1DIR &= ~0x91;     //��P1.0��P1.4��P1.7Ϊ����ģʽ 
    P1INP &= ~0x91;     //��P1.0��P1.4��P1.7��������
	
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
//	��ڲ�����	number:���ƽ��ֵ ����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint16 HCSR04_StartMeasure(uint8 number)
{
					uint16_t rspcount;
  static  uint8 Flag = 1;
  static  uint16 i = 0;
  static  double HCSR04_Data = 0;
  static  double Apart = 0;
  
  for(i=0;i<number;i++)
  {
      Flag = 1;
      Trigl3_HIGH();  //����Trigl3
      delay_us(20);   //�������10us
      Trigl3_LOW();		//����Trigl3
      rspcount = 0;
			 
      while((!Echo3_STATE())&&(rspcount<9000)){	//�ȴ�����
					delay_us(1);
					rspcount++;
			}
      HCSR04Count = 0; //���������
      T1IE = 1;        //����ITM1�ж�,��ʼ��ʱ
      
			rspcount = 0;
      while(Flag)		//�ȴ����ջ����ź�
      {
					rspcount++;
					delay_us(1);
          if(!Echo3_STATE())    //�������
          {
              T1IE = 0;	        //�ر�ITM2�ж�
              if((HCSR04Count*17/50)>=400){
                  i--;
              }
              else{ 
                  Apart += HCSR04Count*17/100;	//��������
							}
              HCSR04Count = 0;
              Flag = 0;
          }
      }
			T1IE = 0;//ͣ����ʱ��1����  
			delay_ms(10);
  }
  
  HCSR04_Data = (Apart/number)/2;//ȡƽ��ֵ
  Apart = 0;
	return (uint16)HCSR04_Data;
}




