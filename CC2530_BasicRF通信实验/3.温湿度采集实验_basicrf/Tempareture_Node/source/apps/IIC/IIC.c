#include "delay.h"
#include "IIC.h"

//==========================================================
//	函数名称：	IIC_Delay
//
//	函数功能：	IIC延时函数
//
//	入口参数：	时间
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Delay(u32 n)
{
  while(n--);
}

//==========================================================
//	函数名称：	IIC_Init
//
//	函数功能：	初始化IIC
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Init(void)
{
    P0SEL &= ~0x03;     //设置P0.0、P0.1为普通IO口  
    P0DIR |= 0x03;      //P0.0、P0.1定义为输出
}

//==========================================================
//	函数名称：	IIC_SCL_OUTPUT
//
//	函数功能：	IIC时钟线输出模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_SCL_OUTPUT(void)
{
    P0SEL &= ~0x02;     //设置P0.1为普通IO口  
    P0DIR |= 0x02;      //P0.1定义为输出
}

//==========================================================
//	函数名称：	IIC_SCL_INPUT
//
//	函数功能：	IIC时钟线输入模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_SCL_INPUT(void)
{
    P0SEL &= ~0x02;     //设置P0.1为普通IO口  
    P0DIR &= ~0x02;     //按键接在P0.6口上，设P0.6为输入模式 
    P0INP &= ~0x02;     //打开P0.1上拉电阻
}

//==========================================================
//	函数名称：	IIC_SDA_OUTPUT
//
//	函数功能：	IIC数据线输出模式 
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_SDA_OUTPUT(void)
{
    P0SEL &= ~0x01;     //设置P0.0为普通IO口  
    P0DIR |= 0x01;      //P0.0定义为输出
}

//==========================================================
//	函数名称：	IIC_SDA_INPUT
//
//	函数功能：	IIC数据线输入模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_SDA_INPUT(void)
{
    P0SEL &= ~0x01;     //设置P0.0为普通IO口  
    P0DIR &= ~0x01;     //按键接在P0.0口上，设P0.7为输入模式 
    P0INP &= ~0x01;     //打开P0.0上拉电阻
}

//==========================================================
//	函数名称：	IIC_Start
//
//	函数功能：	IIC启动时序
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Start(void)
{
    IIC_SDA_OUTPUT();	//时钟线输出模式
    IIC_SCL_OUTPUT();	//数据线输出模式
    SDA_HIGH();		//拉高数据线
    delay_us(1);
    SCL_HIGH();		//拉高时钟线
    SDA_LOW();		//拉低数据线	
    delay_us(1);
    SCL_LOW();		//拉低时钟线
}

//==========================================================
//	函数名称：	IIC_Stop
//
//	函数功能：	IIC停止时序 
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Stop(void)
{
    IIC_SDA_OUTPUT();
    IIC_SCL_OUTPUT();
    SCL_LOW();
    delay_us(1);
    SDA_LOW();
    SCL_HIGH();
    delay_us(1);
    SDA_HIGH();
}

//==========================================================
//	函数名称：	IIC_Wait_Ack
//
//	函数功能：	等待应答信号到来
//
//	入口参数：	无
//
//	返回参数：	返回值：1，接收应答失败
//        							0，接收应答成功
//
//	说明：		
//==========================================================
u8 IIC_Wait_Ack(void)
{
    u8 Time=0;
    IIC_SCL_OUTPUT();
    IIC_SDA_OUTPUT();
    SDA_HIGH();
    delay_us(1);
    SCL_HIGH();
    IIC_SDA_INPUT();
    while(SDA_STATE())
    {
      Time++;
      if(Time>250)
      {
        IIC_Stop();
        return 1;
      }
    }
    SCL_LOW();
    return 0;
}



//==========================================================
//	函数名称：	IIC_Ack
//
//	函数功能：	IIC ACK应答
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Ack(void)
{
    IIC_SCL_OUTPUT();
    SCL_LOW();
    IIC_SDA_OUTPUT();
    SDA_LOW();
    delay_us(1);
    SCL_HIGH();
    delay_us(1);
    SCL_LOW();
}

//==========================================================
//	函数名称：	IIC_NAck
//
//	函数功能：	IIC 无ACK应答
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_NAck(void)
{
    IIC_SCL_OUTPUT();
    SCL_LOW();
    IIC_SDA_OUTPUT();
    SDA_HIGH();
    delay_us(1);
    SCL_HIGH();
    delay_us(1);
    SCL_LOW();
}

//==========================================================
//	函数名称：	SHT2x_I2cReadByte
//
//	函数功能：	IIC 读取数据
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
u8 SHT2x_I2cReadByte(void)
{
    u8 i, val = 0;

    IIC_SCL_OUTPUT();  		    //设置为输出模式
    IIC_SDA_OUTPUT();

    SDA_HIGH();			    //数据线拉高
    
    IIC_SDA_INPUT();		    //数据线设置为输入模式
        
    for(i = 0; i < 8; i++)
    {
        val <<= 1; 
        
        SCL_HIGH();  	 	    //拉高时钟线
        
        if(Bit_SET == SDA_STATE())  //如果数据线被拉高
        {
            val |= 0x01;	    //读取数据线中的数据
        }
        
        SCL_LOW();      	    //拉低时钟线
    }

    IIC_SDA_OUTPUT();  		    //数据线输出模式

    SDA_HIGH();			    //数据线拉高
    
    return (val);		    //返回读取到的数据
}

//==========================================================
//	函数名称：	IIC_Read_Byte
//
//	函数功能：	IIC 读取数据
//
//	入口参数：	ack:是否发送ACK
//
//	返回参数：	无
//
//	说明：		
//==========================================================
u8 IIC_Read_Byte(u8 ack)
{
    u8 i,receive=0;
    IIC_SDA_INPUT();
    IIC_SCL_OUTPUT();
    for(i=0;i<8;i++)
    {
        SCL_LOW();
        SCL_HIGH();
        receive<<=1;
        if(SDA_STATE())receive++;
    }
    if(!ack) IIC_NAck();
    else IIC_Ack();
    return receive;
}


//==========================================================
//	函数名称：	Write_IIC_Byte
//
//	函数功能：	IIC 写入数据
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
u8 Write_IIC_Byte(u8 byte)
{
    u8 i, ack;

    IIC_SCL_OUTPUT();
    IIC_SDA_OUTPUT();		//设置为输出模式
    
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80)         //一次读取最高位 发送数据
        {
            SDA_HIGH();
        }
        else 
        {
            SDA_LOW();
        }
        
        SCL_HIGH();  		//时钟线拉高
        SCL_LOW();   		//时钟线拉低
        
        byte <<= 1;
    }

    IIC_SDA_INPUT();  	        //数据线输入模式
    
    SCL_HIGH();			//时钟线拉高
    
    if(Bit_SET == SDA_STATE())  //如果接受到数据线高信号  ACK错误
    {
        ack = ACK_ERROR;
    }
    else
    {
        ack = ACK_OK;
    }
    
    SCL_LOW();          //拉低时钟线

    IIC_SDA_OUTPUT();	

    SDA_HIGH();		//拉高数据线
    
    return (ack);
}



//==========================================================
//	函数名称：	IIC_Send_Byte
//
//	函数功能：	IIC 写入数据
//
//	入口参数：	txd:写入数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    IIC_SCL_OUTPUT();
    delay_us(1);
    IIC_SDA_OUTPUT();
    SCL_LOW();
    for(t=0;t<8;t++)
    {
        if(txd & 0x80)
        {
            SDA_HIGH();
        }
        else 
        {
            SDA_LOW();
        }
        
        SCL_HIGH();
        delay_us(1);
        SCL_LOW();
        txd<<=1;
    }
}


