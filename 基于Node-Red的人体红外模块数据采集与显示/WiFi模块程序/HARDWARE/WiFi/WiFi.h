#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"

#define WiFi_RST_PIN 						GPIO_PIN_8
#define WiFi_RST_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define WiFi_RST_PORT 					GPIOA
#define WiFi_RST_High() 				HAL_GPIO_WritePin(WiFi_RST_PORT,WiFi_RST_PIN,GPIO_PIN_SET)
#define	CLOSE_TCP		 "+++"																						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=3\r\n"																//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"																			//������ģ��
#define CIFSR        "AT+CIFSR\r\n"			 															//��ѯIP��ַ
#define CWJAP        "AT+CWJAP=\"bacheng\",\"Stepiot123\"\r\n"			//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"TCP\",\"192.168.3.11\",9080\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      "AT+CIPSEND\r\n"																	//��ʼ����

extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/
void WiFi_Init(void);

#endif


