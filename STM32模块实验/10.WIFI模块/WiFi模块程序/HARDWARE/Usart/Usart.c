#include "stm32f1xx.h"
#include "usart.h"	
#include "Rs485.h"	
#include "timer.h"
#include "delay.h"
#include "WiFi.h"

#if UART1   //使能接收

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
unsigned char USART1_RX_BUF[USART1_REC_LEN];     	//接收缓冲,最大USART_REC_LEN个字节.

unsigned int 	USART1_RX_STA=0;       							//接收状态标记	  

unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];	//HAL库使用的串口接收缓冲

UART_HandleTypeDef UART1_Handler; 								//UART句柄
  

//==========================================================
//	函数名称：	UART1_Init()
//
//	函数功能：	串口1初始化
//
//	入口参数：	bound:波特率
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void UART1_Init(int bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    			//USART1
	UART1_Handler.Init.BaudRate=bound;				    		//波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    	//收发模式
	HAL_UART_Init(&UART1_Handler);					    			//HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *)UART1_RxBuffer, UART1_RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

//==========================================================
//	函数名称：	USART1_IRQHandler()
//
//	函数功能：	串口1中断服务程序
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART1_IRQHandler(void)                	
{ 
	static unsigned char Res = 0;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
		Res=USART1->DR; 
		if(USART1_RX_STA!=0x8000)
		{
			RS485_RX_EN();					//开启485接收
			Rs485_Receive(Res);			//进入485接收函数
		}
	}
}

#endif

#if UART2

//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

unsigned int USART2_RX_STA=0;       							//接收状态标记	  
																//湿度数据
uint8_t Command_LED[10]={1,1,1,1};													//控制LED灯命令码
uint8_t Send_OneNET[30];													//发送到OneNET显示数据
uint16_t LDR_Data = 0;														//光强数据

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];	//HAL库使用的串口接收缓冲

UART_HandleTypeDef UART2_Handler,huart3; 								//UART句柄


//==========================================================
//	函数名称：	UART2_Init()
//
//	函数功能：	串口2初始化
//
//	入口参数：	bound:波特率
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void UART2_Init(int bound)
{	
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    						//USART2
	UART2_Handler.Init.BaudRate=bound;				    					//波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    			//一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    			//无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    				//收发模式
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    						//HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (unsigned char *)UART2_RxBuffer, UART2_RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
  
}

//==========================================================
//	函数名称：	USART2_IRQHandler()
//
//	函数功能：	串口2中断服务程序
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART2_IRQHandler(void)
{
	unsigned char Res;

	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
		Res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)			//接收未完成
		{
			if(WiFi_AT_STA)									//AT指令发送完成
			{	
				USART2_Receive(Res);					//串口二数据处理
			}
			else														//AT指令未发送完成
			{
				USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
				USART2_RX_STA++;
				if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收		
			}
		}
	}
	HAL_UART_IRQHandler(&UART2_Handler);
}

//==========================================================
//	函数名称：	USART2_Receive()
//
//	函数功能：	串口二接收
//
//	入口参数：	data:串口二数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART2_Receive(uint8_t data)
{
	static uint8_t End_Flag 		= 0;	//帧尾标志位
	static uint8_t Header_Flag 	= 0;	//帧头标志位
	static uint8_t Receive_Flag = 0;	//接收标志位

/*
*
*				帧头接收
*
*/
	/*帧头1 数据帧头中第一个字节*/
	if(Header_Flag == 0 && data == 0x43)
	{
		Header_Flag = 1;
	}

	/*帧头2 数据帧头中第二个字节*/
	else if(Header_Flag == 1 && data == 0x47)
	{
		USART2_RX_BUF[0] = 0x43;//将缓存值存到接收数组中
		USART2_RX_STA = 1;	//存放数据数组下标清零
		Receive_Flag = 1;		//开始接收数据标志位
	}

	else Header_Flag = 0;
	
/*
*
*				数据+帧尾接收
*
*/
	if(Receive_Flag)	//帧头接收完成，准备接收帧尾
	{
		if(USART2_RX_STA>=(USART2_REC_LEN-1))
		{
			End_Flag = 0;
			Receive_Flag = 0;
			USART2_RX_STA = 0;
		}
		
		USART2_RX_BUF[USART2_RX_STA++] = data;	//数据接收
	
		/*帧尾1  数据帧尾中第一个字节*/
		if(!End_Flag && data == 0x53)
		{
			End_Flag = 1;
		}
		/*帧尾2  数据帧尾中第二个字节*/
		else if(End_Flag && data == 0x57)
		{
			USART2_RX_STA = 0x8000;		//接收完成
			Receive_Flag = 0;
			End_Flag = 0;
		}

		/*接收错误 重新接收*/
		else End_Flag = 0;
	}
}

#endif

//==========================================================
//	函数名称：	void MX_USART3_UART_Init(void)
//
//	函数功能：	初始化usart3
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART3_Init(int baud)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = baud;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        while(1);
    }
}
//==========================================================
//	函数名称：	HAL_UART_MspInit()
//
//	函数功能：	UART底层初始化，时钟使能，引脚配置，中断配置
//
//	入口参数：	huart:串口句柄
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  /*	GPIO端口设置	*/
	GPIO_InitTypeDef GPIO_Initure;
    
	if (huart->Instance==USART1)   								//如果是串口1，进行串口1 MSP初始化
	{
			__HAL_RCC_GPIOA_CLK_ENABLE();							//使能GPIOA时钟
			__HAL_RCC_USART1_CLK_ENABLE();						//使能USART1时钟
			__HAL_RCC_AFIO_CLK_ENABLE();

			GPIO_Initure.Pin=GPIO_PIN_9;							//PA9
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;				//复用推挽输出
			GPIO_Initure.Pull=GPIO_PULLUP;						//上拉
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//高速
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//初始化PA9

			GPIO_Initure.Pin=GPIO_PIN_10;							//PA10
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;			//模式要设置为复用输入模式！	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//初始化PA10
			
	#if EN_USART1_RX
			HAL_NVIC_EnableIRQ(USART1_IRQn);					//使能USART1中断通道
			HAL_NVIC_SetPriority(USART1_IRQn,1,2);		//抢占优先级1，子优先级2
	#endif	
	}
  else if(huart->Instance==USART2)							//如果是串口2，进行串口2 MSP初始化
	{
			__HAL_RCC_GPIOA_CLK_ENABLE();							//使能GPIOA时钟
			__HAL_RCC_USART2_CLK_ENABLE();						//使能USART2时钟
			
		 // __HAL_RCC_AFIO_CLK_ENABLE();

			GPIO_Initure.Pin=GPIO_PIN_2;							//PA2
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;				//复用推挽输出
			GPIO_Initure.Pull=GPIO_PULLUP;						//上拉
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//高速
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//初始化PA2

			GPIO_Initure.Pin=GPIO_PIN_3;							//PA3
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;			//模式要设置为复用输入模式！	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//初始化PA3
			
	#if EN_USART2_RX
			HAL_NVIC_EnableIRQ(USART2_IRQn);					//使能USART2中断通道
			HAL_NVIC_SetPriority(USART2_IRQn,1,1);		//抢占优先级1，子优先级1
	#endif	
  }
        if(huart->Instance==USART3)
    {
        __HAL_RCC_USART3_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
            
        GPIO_Initure.Pin   = GPIO_PIN_10;
        GPIO_Initure.Mode  = GPIO_MODE_AF_PP;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);

        GPIO_Initure.Pin  = GPIO_PIN_11;
        GPIO_Initure.Mode = GPIO_MODE_INPUT;
        GPIO_Initure.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    } 
}


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE
{ 
	int handle;
}; 

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)
{ 
	x = x;
}
//重定义fputc函数 
int fputc(int ch, FILE *f)
{
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (unsigned char) ch;
	return ch;
}
#endif

//==========================================================
//	函数名称：	WiFi_Send_Cmd()
//
//	函数功能：	向WiFi发送命令
//
//	入口参数：	waittime:等待时间(单位:ms)
//							cmd:发送的命令字符串
//							ack:期待的应答结果,如果为空,则表示不需要等待应答
//
//	返回参数：	
//						返回值:	非0,发送成功(得到了期待的应答结果)
//       							0,发送失败
//
//	说明：		
//==========================================================
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
	static uint8_t len = 0;							//存放数据长度
	static uint16_t j = 0;
	char *strx=0;

	len = strlen((char *)cmd);					//获取数据长度

	memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);	//清空数组
	HAL_UART_Transmit(&UART2_Handler,cmd,len,1000);	//串口2发送数据
	
	for(j=0;j<waittime;j++)
	{
		delay_ms(50);
		strx=strstr((const char*)USART2_RX_BUF,(const char*)ack);
		if(strx)
			break;
	}
    
	USART2_RX_STA=0;
	return (uint8_t*)strx;
}

//==========================================================
//	函数名称：	USART_Data_Send()
//
//	函数功能：	串口数据发送函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：			
//==========================================================
void USART_Data_Send(void)
{
	static uint8_t Send_Flag = 0;
	
	if(Task_Count>=200 && Send_Flag == 0)				//200ms		控制LED模块
	{
		Rs485_Send(Addr_WiFi,Addr_LED,LED_Control,4,Command_LED);
		Send_Flag = 1;
	}
	else if(Task_Count>=300 && Send_Flag == 1)	//300ms 	获取温湿度数据
	{
		Rs485_Send(Addr_WiFi,Addr_SHT20,SHT20_Get_All,0,"");
		Send_Flag = 0;
		Task_Count = 0;
	}


}

//==========================================================
//	函数名称：	USART1_IRQHand()
//
//	函数功能：	处理485数据
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：				
//==========================================================
void USART1_IRQHand(void)
{
	if(!DataHandling_485(Addr_WiFi))				//485数据处理
	{
		if(Rx_Stack.Src_Adr == Addr_SHT20)		//获取温湿度数据
		{
			Temp = Rx_Stack.Data[0];						//温度数据
			Humi = Rx_Stack.Data[1];						//湿度数据
			LDR_Data = Rx_Stack.Data[2]*256+Rx_Stack.Data[3];	//光强数据
		}
	}
}

//==========================================================
//	函数名称：	USART2_IRQHand()
//
//	函数功能：	处理串口二数据
//
//	入口参数：	huart:串口句柄
//              
//	返回参数：	无
//
//	说明：			
//==========================================================
void USART2_IRQHand(void)
{
	static uint16_t Command;	//云平台下发命令

	if(USART2_RX_STA == 0x8000)
	{
        printf("get led command\r\n");
		Command = ((USART2_RX_BUF[2]-0x30)*1000)+((USART2_RX_BUF[3]-0x30)*100)
		+((USART2_RX_BUF[4]-0x30)*10)+(USART2_RX_BUF[5]-0x30);//获取平台下发命令码
		
		switch(Command)
		{
			case LED_ON1:
				Command_LED[0] = 1;			//将命令码装载到LED命令码中
				break;
			case LED_OFF1:
				Command_LED[0] = 0;			//将命令码装载到LED命令码中
				break;
			case LED_ON2:
				Command_LED[1] = 1;			//将命令码装载到LED命令码中
				break;
			case LED_OFF2:
				Command_LED[1] = 0;			//将命令码装载到LED命令码中
				break;
			case LED_ON3:
				Command_LED[2] = 1;			//将命令码装载到LED命令码中
				break;
			case LED_OFF3:
				Command_LED[2] = 0;			//将命令码装载到LED命令码中
				break;
			case LED_ON4:
				Command_LED[3] = 1;			//将命令码装载到LED命令码中
				break;
			case LED_OFF4:
				Command_LED[3] = 0;			//将命令码装载到LED命令码中
				break;
			default: break;
		}
		memset((void*)USART2_RX_BUF,0,10);	//清空数组
		USART2_RX_STA = 0;
	}
}




