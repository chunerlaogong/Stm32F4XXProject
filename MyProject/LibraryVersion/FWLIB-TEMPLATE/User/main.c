#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
void Delay(unsigned int count)
{
	while(count--);
}
int main(void)
{
	//led…¡À∏
	LED_GPIO_Config();
	/*while(1)
	{
		GPIO_ToggleBits(GPIOE, GPIO_Pin_8 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_9 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_10 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_11 );
		Delay(0xFFFFFF);
		GPIO_ToggleBits(GPIOE, GPIO_Pin_8 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_9 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_10 );
		GPIO_ToggleBits(GPIOE, GPIO_Pin_11 );
		Delay(0xFFFFFF);
	}*/
	//∞¥º¸…®√Ë
	KEY_GPIO_Config();
	while(1)
	{
		if(KEY_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			GPIO_ToggleBits(GPIOE, GPIO_Pin_8);
		}
	}
}
