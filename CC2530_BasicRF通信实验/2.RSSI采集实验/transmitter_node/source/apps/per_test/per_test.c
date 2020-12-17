/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-10-30
*
*	�汾�� 		V1.0
*   
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_timer_32k.h"
#include "hal_joystick.h"
#include "hal_button.h"
#include "hal_board.h"
#include "hal_rf.h"
#include "hal_assert.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "per_test.h"
#include "string.h"
#include "delay.h"
#include "OLED.h"
#include "IIC.h"

#define IDLE                      0
#define TRANSMIT_PACKET           1

/*****************************important select or shelt***********************************/
//#define MODE_SEND              //����ʱ��  appReceiver
                                 //������ʱ��appTransmitter
/*******************************************************************************/

static basicRfCfg_t basicRfConfig;
static perTestPacket_t txPacket;
static volatile uint8 appState;
static volatile uint8 appStarted;

static void appTimerISR(void);
//static void appStartStop(void);
static void appTransmitter();
void initUART(void);
void UartTX_Send_String(int8 *Data,int len);

/****************************************************************
���ڳ�ʼ������
****************************************************************/
void initUART(void)
{
    PERCFG = 0x00;		      //λ��1 P0��
    P0SEL = 0x0c;		      //P0_2,P0_3�������ڣ��ⲿ�豸���ܣ�
    P2DIR &= ~0XC0;                   //P0������ΪUART0

    U0CSR |= 0x80;		      //����ΪUART��ʽ
    U0GCR |= 11;				       
    U0BAUD |= 216;		      //��������Ϊ115200
    UTX0IF = 0;                       //UART0 TX�жϱ�־��ʼ��λ0
}
/****************************************************************
���ڷ����ַ�������			
****************************************************************/
void UartTX_Send_String(int8 *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

/***********************************************************************************
* @fn          appTimerISR
*
* @brief       32KHz timer interrupt service routine. Signals PER test transmitter
*              application to transmit a packet by setting application state.
*
* @param       none
*
* @return      none
*/
static void appTimerISR(void)
{
    appState = TRANSMIT_PACKET;
}



/***********************************************************************************
* @fn          appConfigTimer
*
* @brief       Configure timer interrupts for application. Uses 32KHz timer
*
* @param       uint16 rate - Frequency of timer interrupt. This value must be
*              between 1 and 32768 Hz
*
* @return      none
*/
static void appConfigTimer(uint16 rate)
{
    halTimer32kInit(TIMER_32K_CLK_FREQ/rate);
    halTimer32kIntConnect(&appTimerISR);
}
//==========================================================
//	�������ƣ�	appTransmitter()
//
//	�������ܣ�	���ͺ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appTransmitter()
{
  uint32 burstSize=0;
  uint32 pktsSent=0;
  //uint8 appTxPower;
  uint8 n;
  
	// ���� Basic RF
	basicRfConfig.panId = PAN_ID;
	basicRfConfig.ackRequest = FALSE;
	//�����ŵ����淶Ҫ���ŵ�ֻ��ΪΪ 11����25������ѡ���ŵ� 11
	basicRfConfig.channel = 0x0B;
  basicRfConfig.myAddr = TX_ADDR;
  if(basicRfInit(&basicRfConfig)==FAILED)
  {
    HAL_ASSERT(FALSE);
  }

   /* ����������� */
  halRfSetTxPower(2);

  /* ���ý���һ�β��������͵����ݰ����� */
  burstSize = 1000;

  basicRfReceiveOff();

   /* ���ö�ʱ����IO *************************/
  appConfigTimer(0xC8);

  /* ��ʼ�����ݰ��غ� */
  txPacket.seqNumber = 0;
  for(n = 0; n < sizeof(txPacket.padding); n++) 
  {
    txPacket.padding[n] = n;
  }
  
   /* ��ѭ�� */
  while (TRUE)
  {
   // �ȴ��û�����Ӧ��  

    while(appStarted)
      {

      if (pktsSent < burstSize) 
      {
          UINT32_HTON(txPacket.seqNumber);  // �ı䷢����ŵ��ֽ�˳��
          basicRfSendPacket(RX_ADDR, (uint8*)&txPacket, PACKET_SIZE);

          /* ���������ǰ���ֽ�˳��Ļ�Ϊ����˳�� */
          UINT32_NTOH(txPacket.seqNumber);
          txPacket.seqNumber++;

          pktsSent++;

          appState = IDLE;
          halLedToggle(1);   //�ı�LED1������״̬
          halMcuWaitMs(500);
      }
      else
        appStarted = !appStarted;
      
      /* ��λͳ�ƺ���� */
     pktsSent = 0;

    }
  }
}

//==========================================================
//	�������ƣ�	main()
//
//	�������ܣ�	������ں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void main (void)
{
    // ��ʼ����ΧӲ��
    halBoardInit();
    appStarted = TRUE;//Ӧ�ó���ʼ
    // ��ʼ�� hal_rf
    if(halRfInit()==FAILED) {
      HAL_ASSERT(FALSE);
    }  

    halMcuWaitMs(350);//��ʱ350ms

		appTransmitter(); //����ģʽ
}

