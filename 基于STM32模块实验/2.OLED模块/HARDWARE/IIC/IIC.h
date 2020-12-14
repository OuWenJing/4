#ifndef __IIC_H 
#define __IIC_H 			   

#include "stm32f1xx_hal.h" 
#include "stm32f1xx.h"

#define u8    						uint8_t
#define u16    						uint16_t
#define u32    						uint32_t
	 
#define Bit_SET  					1
#define Bit_RESET    			0

#define ACK_OK  					0x00
#define ACK_ERROR    			0x01

#define I2C_PORT          GPIOA
#define SCL_PIN           GPIO_PIN_3
#define SDA_PIN           GPIO_PIN_2

#define SCL_HIGH()        HAL_GPIO_WritePin(I2C_PORT,SCL_PIN,GPIO_PIN_SET);
#define SCL_LOW()         HAL_GPIO_WritePin(I2C_PORT,SCL_PIN,GPIO_PIN_RESET);

#define SDA_HIGH()       HAL_GPIO_WritePin(I2C_PORT,SDA_PIN,GPIO_PIN_SET);
#define SDA_LOW()         HAL_GPIO_WritePin(I2C_PORT,SDA_PIN,GPIO_PIN_RESET);

#define SCL_STATE()       HAL_GPIO_ReadPin(I2C_PORT,SCL_PIN)
#define SDA_STATE()       HAL_GPIO_ReadPin(I2C_PORT,SDA_PIN)

//IIC���в�������
void IIC_Delay(u32 n);								//IIC��ʱ����
void IIC_Init(void);           				//��ʼ��IIC��IO��		
void IIC_Start(void);									//����IIC��ʼ�ź�
void IIC_Stop(void);	  							//����IICֹͣ�ź�
void IIC_Ack(void);										//IIC����ACK�ź�
void IIC_NAck(void);									//IIC������ACK�ź�
u8 IIC_Wait_Ack(void);								//�ȴ�Ӧ���źŵ���
void IIC_SCL_OUTPUT(void);						//IICʱ�������ģʽ
void IIC_SCL_INPUT(void);							//IICʱ��������ģʽ
void IIC_SDA_OUTPUT(void);						//IIC���������ģʽ 
void IIC_SDA_INPUT(void);							//IIC����������ģʽ
u8 IIC_Read_Byte(u8 ack);							//IIC��ȡ����
void IIC_Send_Byte(u8 txd);						//IICд����
u8 SHT2x_I2cReadByte(void);						//SHT20��ȡ����
u8 Write_IIC_Byte(u8 byte);						//IICд����

#endif

