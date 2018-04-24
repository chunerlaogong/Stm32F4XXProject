#include "bsp_systick.h"

/*
 *nms������ms����һ���ж�
 */
void SysTick_Init(u32 nms)
{
    /* 1������=(1/168MHz)us = (1/168*10^6)us
     *SystemFrequency / 1000        1ms�ж�һ��
     * SystemFrequency / 100000      10us�ж�һ��
     * SystemFrequency / 1000000     1us�ж�һ��
     */
    SysTick_Config(SystemCoreClock / 1000);      //1ms����һ���ж�
}
void SysTick_Delay_Ms(__IO u32 ms)
{
	u32 i;
	SysTick_Config(SystemCoreClock / 1000);      //1ms��ʱ�� 
	for(i = 0; i < ms; i++)
	{
		while(!((SysTick->CTRL)&(1 << 16)));
	}
	//�رն�ʱ��
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}




























