#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Relay.h"


int main(void)
{
  HAL_Init();         //初始化HAL库  
	Relay_Init();   		//初始化继电器

	while(1)
	{
			RELAY1_OPEN();	 //打开继电器1
			delay_ms(2000);
		
			RELAY1_CLOSE();  //关闭继电器1
			delay_ms(2000);

			RELAY2_OPEN();	 //打开继电器2
			delay_ms(2000);
		
			RELAY2_CLOSE();  //关闭继电器2
			delay_ms(2000);
	}
}




