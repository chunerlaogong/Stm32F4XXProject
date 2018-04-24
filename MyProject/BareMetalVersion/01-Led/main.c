#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

void Delay(unsigned int count)
{
    while(count--);
}
int main()
{
#if 0  /*��д�˿ڵĸ�λ����λ����*/
    /*����ʱ��һ����Ĭ�Ϲرյģ����͹��ģ�����ʹ��GPIOE�˿�ʱ��*/
    RCC_AHB1 |= (0x1 << 4);
    /*����GPIO�ڵķ���GPIOE 8:9:10:11�ܽ�����Ϊ���ģʽ*/
    GPIOE->MODER &= ~(0x03 << 2*8);
    GPIOE->MODER |= (0x1 << 2*8);
    GPIOE->MODER &= ~(0x03 << 2*9);
    GPIOE->MODER |= (0x1 << 2*9);
    GPIOE->MODER &= ~(0x03 << 2*10);
    GPIOE->MODER |= (0x1 << 2*10);
    GPIOE->MODER &= ~(0x03 << 2*11);
    GPIOE->MODER |= (0x1 << 2*11);
    /*PE 8:9:10:11����Ϊ�ߵ�ƽ*/
    GPIOE->ODR &= ~(0xf << 8);    //ȫ����λ0��LEDȫ��
    GPIOE->ODR |= (0x6 << 8);
    /*PE 8:9:10:11����Ϊ�͵�ƽ*/
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
#elif 1 /*��������ĳ�ʼ���ṹ��ͱ�д����ĳ�ʼ������*/
    /*����ʱ��һ����Ĭ�Ϲرյģ����͹��ģ�����ʹ��GPIOE�˿�ʱ��*/
    RCC_AHB1 |= (0x1 << 4);
    /*��ʼ��Pin��*/
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;     //Ĭ������Ϊ����������ߵ�ƽ
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   //����Ϊͨ�õ��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;  //Ϊ�˽��͹��ģ�����Ϊ���
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

