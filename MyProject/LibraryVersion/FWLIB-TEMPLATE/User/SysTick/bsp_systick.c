#include "bsp_systick.h"

/*
 *nms：多少ms产生一次中断
 */
void SysTick_Init(u32 nms)
{
    /* 1个周期=(1/168MHz)us = (1/168*10^6)us
     *SystemFrequency / 1000        1ms中断一次
     * SystemFrequency / 100000      10us中断一次
     * SystemFrequency / 1000000     1us中断一次
     */
    SysTick_Config(SystemCoreClock / 1000);      //1ms产生一次中断
}
void SysTick_Delay_Ms(__IO u32 ms)
{
	u32 i;
	SysTick_Config(SystemCoreClock / 1000);      //1ms定时器 
	for(i = 0; i < ms; i++)
	{
		while(!((SysTick->CTRL)&(1 << 16)));
	}
	//关闭定时器
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}




























