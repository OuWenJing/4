#include "WiFiGate.h"


#define WIFI_RECV_DATA_BUFFER_LEN 128
uint8 WiFiRecvDataBuffer[ WIFI_RECV_DATA_BUFFER_LEN ];
uint8 WiFiRecvLenght = 0;
uint8 NextEvent=0;
uint8 WiFiCmdHandle = 0;

#define GET_RECV_LENGHT()        Hal_UART_RxBufLen(HAL_UART_PORT_0);
#define GET_RECV_DATA(b,l)       HalUARTRead(HAL_UART_PORT_0,b,l);
/*
WIFI模块初始化
*/
uint8 WiFiGate_TaskId = 0;
uint8 WiFiModeInitDone = 0;


void WiFiGate_Init( uint8 task_id )
{
  WiFiGate_TaskId = task_id;
  osal_start_timerEx( WiFiGate_TaskId, WIFI_PROCESS_PRODIC,2000); 
  UartInit(HAL_UART_PORT_0,HAL_UART_BR_115200);
    P1DIR |= 0x60;      //P1.5、P1.6定义为输出
    P1SEL &= ~0x80;     //设置P1.7为普通IO口  
    P1DIR &= ~0x80;     //按键接在P1.7口上，设P1.7为输入模式 
    P1INP &= ~0x80;     //打开P1.7上拉电阻
  printf("wifi connect start\r\n");
  WiFi_RES = 0;
  delay_ms(1);
  WiFi_RES = 1;
  WiFi_LED=0;
  //WiFi_LED_REST();
}
/*
send_times 发送次数
*/
uint32 Ticks_SendATCmd_Count = 0;
static uint8 len;  
uint8 WiFi_Send_ATCommand(uint8 *buf,uint32 timeout,uint8 send_times,uint8 *expect)
{
    uint8 ret = WIFI_RSP_NULL;
    static uint8 state0 = 0,count = 0;
    if(state0 == 0){
		memset((void*)WiFiRecvDataBuffer,0,WIFI_RECV_DATA_BUFFER_LEN);
		WiFiRecvLenght = 0;
		HalUARTResetRxQueue();
		SEND_TO_WIFI(buf,strlen((const char*)buf)); 
        printf("WiFi>>>:%s\r\n",buf);
        state0 = 1;
        count++;
		Ticks_SendATCmd_Count = 0;
		WiFiRecvLenght = 0;
    }
    else if(state0 == 1){
        if((++Ticks_SendATCmd_Count) >= timeout){ 
            if(send_times == count){//多次发送之后 还是没有反应就返回
                ret = WIFI_RSP_TIMEOUT;
                count = 0;
            }
            state0 = 0;            
        }
        else{
		  len = GET_RECV_LENGHT();
		  if(len){
			GET_RECV_DATA(&WiFiRecvDataBuffer[WiFiRecvLenght],len);
			WiFiRecvLenght += len;
			if(WiFiRecvLenght >= WIFI_RECV_DATA_BUFFER_LEN){
				WiFiRecvLenght = 0;
			}				
		  }
		  	
		  if((expect)&&strstr((const char*)WiFiRecvDataBuffer,(const char*)expect)){
			ret = WIFI_RSP_OK;
			state0 = 0;
			count = 0;      
		  }			
        }//else
    }
    
    return ret;
}
/*
wifi网关处理任务，包括初始化WiFi模块，接收数据
*/
static uint8 ConnectState = 0,len,*cptr;
static uint8 FAN_Cmd;
uint16 WiFiGate_ProcessEvent( uint8 task_id, uint16 events )
{

  (void)task_id;  // Intentionally unreferenced parameter

  if ( events & SYS_EVENT_MSG )
  {//如果是系统任务
    return (events ^ SYS_EVENT_MSG);
  }
  else
  {//如果是用户自定义任务
	if(events & WIFI_PROCESS_PRODIC){
	    osal_start_timerEx( WiFiGate_TaskId, WIFI_PROCESS_PRODIC,100);
		switch(ConnectState)
		{
			case 0:
				P1_5 = 0;
				ConnectState++;
				break; 
			case 1:
				P1_5 = 1;
				ConnectState++; 
				break;
			case 2:
			case 3:
			case 4:
				ConnectState++; 
				break;
			break;	  
			case 5:
				  switch(WiFi_Send_ATCommand("AT\r\n",20,5,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState++;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;
			case 6:
				  switch(WiFi_Send_ATCommand("AT+CWMODE=3\r\n",20,5,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState++;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;	
			case 7:
				  switch(WiFi_Send_ATCommand(WIFI_AP,30,10,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState++;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;
			case 8:
				  switch(WiFi_Send_ATCommand(OneNET_IP,20,5,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState = 10;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;		
	
			case 10:
				  switch(WiFi_Send_ATCommand(CIPMODE,20,0,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState++;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;	
			case 11:
				  switch(WiFi_Send_ATCommand(CIPSEND,20,0,"OK"))
				  {
					case WIFI_RSP_OK:
						 ConnectState++;
					break;
					case WIFI_RSP_TIMEOUT:
						 ConnectState = 0xff;
					break;  				  
				  }
				break;		
			case 12:
				  //WiFi_Send_ATCommand(CONNECT_ONENET_KEYSTRING,20,0,"");   //跳过注册到ONENET的操作
				  ConnectState++;
				  WiFiRecvLenght = 0;
				  WiFiModeInitDone = 1;
				  memset((void*)WiFiRecvDataBuffer,0,WIFI_RECV_DATA_BUFFER_LEN);
                                  WiFi_LED_SET(0xFE0000);
				break;	
			case 13:
				  len = GET_RECV_LENGHT();
				  if(len){
					if((WiFiRecvLenght+len) >= (WIFI_RECV_DATA_BUFFER_LEN-1)){
						WiFiRecvLenght = 0;
						memset((void*)WiFiRecvDataBuffer,0,WIFI_RECV_DATA_BUFFER_LEN);
						printf("overflow\r\n");
					}						
					GET_RECV_DATA(&WiFiRecvDataBuffer[WiFiRecvLenght],len);
					WiFiRecvLenght = WiFiRecvLenght + len;			
				  }
				  if((WiFiRecvLenght)&&(!strstr((const char*)WiFiRecvDataBuffer,(const char*)"$"))){//没有~这个符号
				  	WiFiRecvLenght = 0;
					memset((void*)WiFiRecvDataBuffer,0,WIFI_RECV_DATA_BUFFER_LEN);
				  }
			          cptr = (uint8*)strstr((const char*)WiFiRecvDataBuffer,(const char*)"$BEEP,");				
				  if(cptr){
                                        FAN_Cmd = WiFiRecvDataBuffer[6]-0x30;//是打开还是关闭。
					printf("cmd=%d\r\n",FAN_Cmd);//串口调试
                                        if(FAN_Cmd>0)
                                        {
                                          Send_LEDCtrl(1,1);//发送控制命令
                                        }
                                        else
                                        {
                                          Send_LEDCtrl(1,0);//向终端节点发送命令
                                        }
					//Send_FANCtrl(FAN_Cmd);
					WiFiRecvLenght = 0;
					
				  }	
				  memset((void*)WiFiRecvDataBuffer,0,WIFI_RECV_DATA_BUFFER_LEN); 		  
			    break;
		}		
		return (events ^ WIFI_PROCESS_PRODIC);
	}
  }//if(events & WIFI_PROCESS_PRODIC){
  return 0;
} 




/*
发送数据到WIFI网络上
*/
uint8  SendToWiFiNetwork(uint8 *pData,uint8 len)
{
  if(WiFiModeInitDone)
  {
    SEND_TO_WIFI(pData,len);
	return 1;
  }
  return 0;
}

/***********************************************************************************
* 函数名称        WiFi_LED_REST()
*
* 函数功能        拉低电平等待
*
* 入口参数        无
*
* 返回参数        无 
*
* 说明            
***********************************************************************************/
/* 拉低电平等待下一次命令  */
void WiFi_LED_REST(void)
{
    WiFi_LED = 0;
    delay_ms(1);  
}

//==========================================================
//	函数名称：	WiFi_LED_SET()
//
//	函数功能：	设置颜色
//
//	入口参数：	G8R8B8:颜色
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void WiFi_LED_SET(uint32_t G8R8B8)
{
    static int i = 0;
    static unsigned char byte = 0;
    
    for(i=23;i>=0;i--)
    {
        byte = ((G8R8B8 >> i) & 0x01);
        if(byte == 1)
        {
            WiFi_LED_HI;//1
        }
        else
        {
            WiFi_LED_LO; //0
        }
    }
    WiFi_LED_REST();
}

//==========================================================
//	函数名称：	WiFi_Set_White()
//
//	函数功能：	白色
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void WiFi_Set_White(void)
{
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;

  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;  
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;  
}