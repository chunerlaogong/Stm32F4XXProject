#ifndef _EXTI_KEY_H
#define _EXTI_KEY_H
#include "stm32f4xx.h"

#define KEY_INT_GPIO_PORT                        GPIOE
#define KEY_INT_GPIO_CLK                         RCC_AHB1Periph_GPIOE
#define KEY0_INT_GPIO_PIN                        GPIO_Pin_4
#define KEY1_INT_GPIO_PIN                        GPIO_Pin_3
#define KEY2_INT_GPIO_PIN                        GPIO_Pin_2
#define KEYUP_INT_GPIO_PIN                       GPIO_Pin_1
#define KEY_INT_EXTI_PORTSOURCE                  EXTI_PortSourceGPIOE
#define KEY0_INT_EXTI_PINSOURCE                  EXTI_PinSource4
#define KEY0_INT_EXTI_LINE                       EXTI_Line4
#define KEY0_INT_EXTI_IRQ                        EXTI4_IRQn
#define KEY1_INT_EXTI_PINSOURCE                  EXTI_PinSource3
#define KEY1_INT_EXTI_LINE                       EXTI_Line3
#define KEY1_INT_EXTI_IRQ                        EXTI3_IRQn
#define KEY2_INT_EXTI_PINSOURCE                  EXTI_PinSource2
#define KEY2_INT_EXTI_LINE                       EXTI_Line2
#define KEY2_INT_EXTI_IRQ                        EXTI2_IRQn
#define KEYUP_INT_EXTI_PINSOURCE                 EXTI_PinSource1
#define KEYUP_INT_EXTI_LINE                      EXTI_Line1
#define KEYUP_INT_EXTI_IRQ                       EXTI1_IRQn




#define KEY0_IRQHandler                          EXTI4_IRQHandler
#define KEY1_IRQHandler                          EXTI3_IRQHandler
#define KEY2_IRQHandler                          EXTI2_IRQHandler
#define KEYUP_IRQHandler                         EXTI1_IRQHandler



void Key_EXTI_Config(void);
#endif   //_EXTI_KEY_H
