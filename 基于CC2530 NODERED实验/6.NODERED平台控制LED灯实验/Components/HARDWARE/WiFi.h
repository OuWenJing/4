#ifndef __WiFi_H
#define __WiFi_H 			   

#include <ioCC2530.h>

#define	CLOSE_TCP     "+++"						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT            "AT\r\n"
#define CWMODE        "AT+CWMODE=3\r\n"					//����ģʽΪAP+STA
#define RST           "AT+RST\r\n"					//������ģ��
#define CIFSR         "AT+CIFSR\r\n"					//��ѯIP��ַ
#define CWJAP         "AT+CWJAP=\"zkk_2.4g\",\"18696560024\"\r\n"		//����SID��PWD��������
#define TCP_CIPSTART  "AT+CIPSTART=\"TCP\",\"192.168.3.213\",9080\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE       "AT+CIPMODE=1\r\n"				//͸��
#define CIPSEND       "AT+CIPSEND\r\n"					//��ʼ����
//#define CIPSTATUS     "*238724#0001#sample*"				//ONE.NETƽ̨�����˺�ʶ����

extern void WiFi_Init(void); //WiFi��ʼ��

#endif

