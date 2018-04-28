#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_exti_key.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "common.h"
/*Led��˸����*/
void Led_Blink_Test(void)
{
    LED_GPIO_Config();
    LED_Blink(0);
    LED_Blink(1);
}
/*����ɨ�����*/
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
/*�ⲿ�жϰ�������*/
void KEY_EXTI_INT_Test(void)
{
    //delay_init(168);
    Key_EXTI_Config();

}
int main(void)
{
    LED_GPIO_Config();
    //LED_Blink(0);
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ����� 2
    USART1_Init();
	 // USART_SendByte(USART1, 'h');
    while(1)
    {
        USART_SendByte(USART1, 'h');
    }

}
