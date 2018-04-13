#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

void Delay(unsigned int count)
{
    while(count--);
}
int main()
{
#if 0  /*编写端口的复位和置位函数*/
    /*外设时钟一般是默认关闭的，降低功耗，所以使能GPIOE端口时钟*/
    RCC_AHB1 |= (0x1 << 4);
    /*控制GPIO口的方向GPIOE 8:9:10:11管脚配置为输出模式*/
    GPIOE->MODER &= ~(0x03 << 2*8);
    GPIOE->MODER |= (0x1 << 2*8);
    GPIOE->MODER &= ~(0x03 << 2*9);
    GPIOE->MODER |= (0x1 << 2*9);
    GPIOE->MODER &= ~(0x03 << 2*10);
    GPIOE->MODER |= (0x1 << 2*10);
    GPIOE->MODER &= ~(0x03 << 2*11);
    GPIOE->MODER |= (0x1 << 2*11);
    /*PE 8:9:10:11设置为高电平*/
    GPIOE->ODR &= ~(0xf << 8);    //全部置位0，LED全亮
    GPIOE->ODR |= (0x6 << 8);
    /*PE 8:9:10:11设置为低电平*/
    //GPIOE_ODR &= ~(0x6 << 8);
    while(1)
    {
        GPIO_RestBits(GPIOE, GPIO_Pin_8);
        GPIO_RestBits(GPIOE, GPIO_Pin_9);
        GPIO_RestBits(GPIOE, GPIO_Pin_10);
        GPIO_RestBits(GPIOE, GPIO_Pin_11);
        Delay(0xfffff);
        //  GPIOE->ODR &= ~(0x6 << 8);
        GPIO_SetBits(GPIOE, GPIO_Pin_8);
        GPIO_SetBits(GPIOE, GPIO_Pin_9);
        GPIO_SetBits(GPIOE, GPIO_Pin_10);
        GPIO_SetBits(GPIOE, GPIO_Pin_11);
        Delay(0xfffff);
    }
#elif 1 /*定义外设的初始化结构体和编写外设的初始化函数*/
    /*外设时钟一般是默认关闭的，降低功耗，所以使能GPIOE端口时钟*/
    RCC_AHB1 |= (0x1 << 4);
    /*初始化Pin脚*/
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;     //默认配置为上拉，输出高电平
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   //配置为通用的推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;  //为了降低功耗，配置为最低
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    while(1)
    {
        GPIO_RestBits(GPIOE, GPIO_Pin_8);
        GPIO_RestBits(GPIOE, GPIO_Pin_9);
        GPIO_RestBits(GPIOE, GPIO_Pin_10);
        GPIO_RestBits(GPIOE, GPIO_Pin_11);
        Delay(0xfffff);
        //  GPIOE->ODR &= ~(0x6 << 8);
        GPIO_SetBits(GPIOE, GPIO_Pin_8);
        GPIO_SetBits(GPIOE, GPIO_Pin_9);
        GPIO_SetBits(GPIOE, GPIO_Pin_10);
        GPIO_SetBits(GPIOE, GPIO_Pin_11);
        Delay(0xfffff);
    }
#endif
}

void SystemInit()
{
}

