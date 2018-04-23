#ifndef _COMMON_H
#define _COMMON_H
#include "stm32f4xx.h"
static u8  fac_us=0;							
static u16 fac_ms=0;	
void Delay(unsigned int count);
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);

#endif
