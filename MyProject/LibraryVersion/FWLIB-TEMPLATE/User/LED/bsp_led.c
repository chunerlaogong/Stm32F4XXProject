
#include "bsp_led.h"
#include "common.h"
/*LED��0-GPIOF_PIN9/1-GPIOF_PIN10 GPIO����*/
void LED_GPIO_Config(void)
{
    /*����4���ʺ���������ĳ�ʼ��*/
    /*1.������ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    /*2.����һ��GPIO��ʼ���ṹ��*/
    GPIO_InitTypeDef GPIO_InitStruct;
    /*3.����GPIO��ʼ���ṹ��ĳ�Ա*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    /*4.����GPIO��ʼ�������������úõ�GPIO��ʼ���ṹ��ĳ�Ա�Ĳ���д��Ĵ���*/
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    //GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10); //GPIOF9,GPIOF10��λ������
}
/*LED��˸*/
void LED_Blink(int ledNum)
{
    LED_GPIO_Config();
    while(1)
    {
        switch(ledNum)
        {
            case 0:
                GPIO_ToggleBits(GPIOF, GPIO_Pin_9 );    //GPIOF9���ͣ�����
                Delay(0xFFFFFF);
                GPIO_ToggleBits(GPIOF, GPIO_Pin_9 );    //GPIOF9���ߣ�����
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
/*����LED*/
void LED_On(int ledNum)
{
    LED_GPIO_Config();
    switch(ledNum)
    {
        case 0:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_RESET); //GPIOF9���ͣ�����
            break;
        case 1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_RESET);
            break;
        default:
            break;
    }
}
/*Ϩ��LED*/
void LED_Off(int ledNum)
{
    LED_GPIO_Config();
    switch(ledNum)
    {
        case 0:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_SET);   //GPIOF9���ߣ�����
            break;
        case 1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_SET);
            break;
        default:
            break;
    }
}


