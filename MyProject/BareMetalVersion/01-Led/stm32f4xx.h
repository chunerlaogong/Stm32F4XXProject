#ifndef _STM32_F4XX_H
#define _STM32_F4XX_H
#include <stdint.h>


/*存放寄存器映射相关的代码*/
#define GPIOE_BASE            ((unsigned int )0x40021000)

#define GPIOE_MODER           *(unsigned int *)0x40021000
#define GPIOE_ODR             *(unsigned int *)(0x40021000+0x14)
//外设时钟寄存器地址定义
#define RCC_BASE              ((unsigned int )0x40023800)
#define RCC_AHB1              *(unsigned int *)(0x40023800+0x30)

//外设寄存器结构体定义
typedef struct
{
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint16_t BSRRL;
    uint16_t BSRRH;
    uint32_t LCKR;
    uint32_t AFRL;
    uint32_t AFRH;

} GPIO_TypeDef;

#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#endif  // _STM32_F4XX_H_
