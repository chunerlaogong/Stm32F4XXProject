#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f4xx.h"


void LED_GPIO_Config(void);
void LED_Blink(int ledNum);
void LED_On(int ledNum);
void LED_Off(int ledNum);



#endif   //_BSP_LED_H

