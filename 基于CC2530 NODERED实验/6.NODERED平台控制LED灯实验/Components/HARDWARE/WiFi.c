#include "Usart.h"	
#include "delay.h"
#include "WiFi.h"

//==========================================================
//	�������ƣ�	WiFi_Init()
//
//	�������ܣ�	��ʼ��WiFi
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_Init(void)
{
    WiFi_Send_Cmd(CLOSE_TCP,"",5);			/*�˳�WiFi͸��ģʽ*/

    delay_ms(3000);

    while(!WiFi_Send_Cmd(AT,"OK",20));		        /*����AT����ģʽ*/														//��ʾ��Դ״̬
    
    while(!WiFi_Send_Cmd(CWMODE,"OK",30));		/*����ģ��Ӧ��ģʽ*/													//��ʾ��Դ״̬

//    while(!WiFi_Send_Cmd(RST,"",80));		        /*����ģ��*/															//��ʾ��Դ״̬
//
//    while(!WiFi_Send_Cmd(CIFSR,"OK",30));;		/*��ѯ�豸IP�ɷ�����Ҫ��λ��*/															//��ʾ��Դ״̬

    while(!WiFi_Send_Cmd(CWJAP,"OK",300));		/*����Ҫ���ӵ�·������SSID������*/																			/*LED2��*/

    while(!WiFi_Send_Cmd(TCP_CIPSTART,"OK",60));	/*�����������TCP����*/																			/*LED3��*/

    while(!WiFi_Send_Cmd(CIPMODE,"OK",60));		/*͸��ģʽ*/
    
    while(!WiFi_Send_Cmd(CIPSEND,"OK",30));		/*��ʼ����*/																			/*LED4��*/
    
    //while(!WiFi_Send_Cmd(CIPSTATUS,"",30));		/*�����豸*/
    
    WiFi_AT_STA = 1;           			        /*ATָ�����ɱ�־λ*/	
}


