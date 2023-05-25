#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"

#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=3\r\n"									//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"										//������ģ��
#define CIFSR        "AT+CIFSR\r\n"										//��ѯIP��ַ
#define CWJAP        "AT+CWJAP_CUR=\"zkk_2.4g\",\"18696560024\"\r\n"	//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      "AT+CIPMODE=1\r\n"									//͸��
#define CIPSEND      "AT+CIPSEND\r\n"									//��ʼ����

												

#define 	WiFi_LED_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_LED_PORT 					GPIOA
#define 	WiFi_LED_PIN 						GPIO_PIN_7

#define 	WiFi_KEY_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_KEY_PORT 					GPIOA
#define 	WiFi_KEY_PIN						GPIO_PIN_6

#define 	WiFi_RST_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_RST_PORT 					GPIOA
#define 	WiFi_RST_PIN 						GPIO_PIN_5

#define 	WiFi_LED_High() 				WiFi_LED_PORT->BSRR = WiFi_LED_PIN
#define 	WiFi_LED_Low() 					WiFi_LED_PORT->BRR 	= WiFi_LED_PIN

#define 	WiFi_RST_High() 				WiFi_RST_PORT->BSRR = WiFi_RST_PIN
#define 	WiFi_RST_Low() 					WiFi_RST_PORT->BRR 	= WiFi_RST_PIN

#define 	WiFi_KEY_Read()   			HAL_GPIO_ReadPin(WiFi_KEY_PORT,WiFi_KEY_PIN)  //����

#define RED 		0xFF00  			//���
#define GREEN 	0xFF0000  		//�̹�
#define BLUE 		0xFF  				//����
#define WHITE 	0xFFFFFF  		//�׹�
#define CUTDOWN 0		  				//�ر���ʾ

extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/

extern void WiFi_Init(void);
extern void WiFi_LED_Init(void);					//��ʼ��LED
extern void WiFi_RST_Init(void);					//��ʼ��RST
extern void WiFi_KEY_Init(void);					//��ʼ������
extern void WiFi_RGB_Set_UP(void);				//1��  850ns�ߵ�ƽ  400ns�͵�ƽ
extern void WiFi_RGB_Set_Down(void);			//0��  400ns�ߵ�ƽ  850ns�͵�ƽ
extern void WiFi_RGB_SET(uint32_t G8R8B8);//������ɫ
extern void WiFi_RGB_REST(void);					//���͵�ƽ�ȴ���һ������ 
extern void WiFi_RGB_User(uint8_t Num_Lig,uint32_t DELAY);
extern void WiFi_SerialSend(uint8_t *p,uint16_t len);
#endif


