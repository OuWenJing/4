#include "Ble.h"	
#include "delay.h"
#include "Usart.h"

uint8_t BLE_AT_STA = 0;

//==========================================================
//	�������ƣ�	BLE_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	��
//				
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void BLE_Init(void)
{
	delay_ms(2000);
	ble_send_cmd("AT+TXPW0\r\n","OK",2000);	//���÷��书��4dBm
		delay_ms(1000); 
	ble_send_cmd("AT+ROLE0\r\n","OK",20);	//����Ϊ���豸  
	delay_ms(1000);    
	ble_send_cmd("AT+MODE0\r\n","OK",20);	//����Ϊ���豸
    
  BLE_AT_STA = 1;        /*ATָ�����ɱ�־λ*/
}


