#include "stm32f1xx.h"
#include "UART.h"	

UART_HandleTypeDef UART2_Handler; 								//UART���


//==========================================================
//	�������ƣ�	UART2_Init()
//
//	�������ܣ�	����2��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART2_Init(int bound)
{	
	//UART ��ʼ������
	UART2_Handler.Instance=USART2;					    						//USART2
	UART2_Handler.Init.BaudRate=bound;				    					//������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    			//һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    			//����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    				//�շ�ģʽ
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    						//HAL_UART_Init()��ʹ��UART1
    
  __HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_RXNE);    
}

//==========================================================
//	�������ƣ�	HAL_UART_MspInit()
//
//	�������ܣ�	UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//
//	��ڲ�����	huart:���ھ��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  /*	GPIO�˿�����	*/
	GPIO_InitTypeDef GPIO_Initure;
 
  if(huart->Instance==USART2)							//����Ǵ���2�����д���2 MSP��ʼ��
	{
			__HAL_RCC_GPIOA_CLK_ENABLE();							//ʹ��GPIOAʱ��
			__HAL_RCC_USART2_CLK_ENABLE();						//ʹ��USART2ʱ��
			
		 // __HAL_RCC_AFIO_CLK_ENABLE();

			GPIO_Initure.Pin=GPIO_PIN_2;							//PA2
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;				//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;						//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//����
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA2

			GPIO_Initure.Pin=GPIO_PIN_3;							//PA3
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;			//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA3
			
			HAL_NVIC_EnableIRQ(USART2_IRQn);					//ʹ��USART2�ж�ͨ��
			HAL_NVIC_SetPriority(USART2_IRQn,1,1);		//��ռ���ȼ�1�������ȼ�1
  }
}




