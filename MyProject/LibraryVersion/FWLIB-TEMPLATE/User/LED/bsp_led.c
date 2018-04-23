
#include "bsp_led.h"
#include "common.h"
/*LED：0-GPIOF_PIN9/1-GPIOF_PIN10 GPIO配置*/
void LED_GPIO_Config(void)
{
    /*以下4步适合所有外设的初始化*/
    /*1.开外设时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    /*2.定义一个GPIO初始化结构体*/
    GPIO_InitTypeDef GPIO_InitStruct;
    /*3.配置GPIO初始化结构体的成员*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    /*4.调用GPIO初始化函数，把配置好的GPIO初始化结构体的成员的参数写入寄存器*/
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    //GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10); //GPIOF9,GPIOF10置位，灯灭
}
/*LED闪烁*/
void LED_Blink(int ledNum)
{
    LED_GPIO_Config();
    while(1)
    {
        switch(ledNum)
        {
            case 0:
                GPIO_ToggleBits(GPIOF, GPIO_Pin_9 );    //GPIOF9拉低，灯亮
                Delay(0xFFFFFF);
                GPIO_ToggleBits(GPIOF, GPIO_Pin_9 );    //GPIOF9拉高，灯灭
                break;
            case 1:

                GPIO_ToggleBits(GPIOF, GPIO_Pin_10 );
                Delay(0xFFFFFF);
                GPIO_ToggleBits(GPIOF, GPIO_Pin_10 );
                break;
            default:
                break;
        }
        Delay(0xFFFFFF);
    }
}
/*点亮LED*/
void LED_On(int ledNum)
{
    LED_GPIO_Config();
    switch(ledNum)
    {
        case 0:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_RESET); //GPIOF9拉低，灯亮
            break;
        case 1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_RESET);
            break;
        default:
            break;
    }
}
/*熄灭LED*/
void LED_Off(int ledNum)
{
    LED_GPIO_Config();
    switch(ledNum)
    {
        case 0:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_SET);   //GPIOF9拉高，灯灭
            break;
        case 1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_SET);
            break;
        default:
            break;
    }
}


