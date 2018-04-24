#ifndef _BSP_SYSTICK_H
#define _BSP_SYSTICK_H

#include "stm32f4xx.h"

void SysTick_Init(u32 nms);
void SysTick_Delay_Ms(__IO u32 ms);


#endif	//_BSP_SYSTICK_H

