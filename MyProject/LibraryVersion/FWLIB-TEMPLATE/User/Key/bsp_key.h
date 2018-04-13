#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "stm32f4xx.h"
#define KEY1_PIN                 GPIO_Pin_12
#define KEY1_GPIO_PORT           GPIOE
#define KEY1_GPIO_CLK            RCC_AHB1Periph_GPIOE
#define KEY_ON 1
#define KEY_OFF 0
void KEY_GPIO_Config();
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif   //_BSP_KEY_H