#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_exti_key.h"
#include "bsp_systick.h"
#include "common.h"
/*Led闪烁功能*/
void Led_Blink_Test(void)
{
	LED_GPIO_Config();
	LED_Blink(0);
	LED_Blink(1);
}
/*按键扫描测试*/
void KEY_Scan_Test(void)
{
	KEY_GPIO_Config();
	while(1)
	{
		if(KEY_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			GPIO_ToggleBits(GPIOE, GPIO_Pin_8);
		}		
	}		

}
/*外部中断按键测试*/
void KEY_EXTI_INT_Test(void)
{
	//delay_init(168);
	Key_EXTI_Config();
	
}
int main(void)
{
	LED_GPIO_Config();

	LED_Off(0);
	LED_Off(1);
	while(1)
	{
		LED_On(1);
		delay_ms(1000);
		LED_Off(1);
		delay_ms(1000);
	}
	//SysTick_Test();
	//KEY_EXTI_INT_Test();
	//while(1);
		
}
