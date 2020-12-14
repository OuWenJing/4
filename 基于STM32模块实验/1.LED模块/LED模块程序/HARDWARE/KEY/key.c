#include "led.h"
#include "key.h"
#include "stm32f1xx.h"

//==========================================================
//	�������ƣ�	KEY_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		��ʼ����������IO
//==========================================================
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    KEY_IO_RCC();//ʹ��IO�˿�ʱ��
  
    GPIO_Initure.Pin   = S1_PIN|S2_PIN;        //S1_PIN,S2_PIN������key.h�� 
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull  = GPIO_PULLUP;        	//����
    GPIO_Initure.Speed = GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);       
	
    GPIO_Initure.Pin   = S3_PIN|S4_PIN;        //S3_PIN��S4_PIN������key.h�� 
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull  = GPIO_PULLUP;        	//����
    GPIO_Initure.Speed = GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}
//==========================================================
//	�������ƣ�	KEY_Scan()
//
//	�������ܣ�	����������
//
//	��ڲ�����	mode:	0,��֧��������;
//										1,֧��������;
//
//	���ز�����	���ذ���ֵ
//										0��û���κΰ�������
//										1��2��3��Ӧ��Ӧ�İ���
//	˵����			ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3!!
//S1_Read() == 0,�а������£�S1_Read() == 1,�����ɿ����Դ�����
//==========================================================
uint8_t KEY_Scan(void)
{
    static uint8_t key_up=1;     	//�����ɿ���־
    
    /*�ڰ����ɿ���������а�������*/
    if(key_up&&(S1_Read()==0||S2_Read()==0||S3_Read()==0||S4_Read()==0)){
        HAL_Delay(10);  //����а���������ʱ10������������
        key_up=0;       //����������
        if(S1_Read()==0){
            return S1_PRES; //���� S1 ����
        }
        else if(S2_Read()==0){
            return S2_PRES; //���� S2 ����
        }
        else if(S3_Read()==0){
            return S3_PRES; //���� S3 ����
        }          
				else if(S4_Read()==0){
            return S4_PRES; //���� S4 ����
        }
    }
    else if(S1_Read()==1&&S2_Read()==1&&S3_Read()==1&&S4_Read()==1){
        /*����ȫ���ɿ���*/
        key_up=1;
		}    
    return 0;   //�ް�������
}




