#include "bsp_key.h"

void KEY_GPIO_Config()   //����GPIOΪ���룬��ⰴ���Ƿ���
{
	/*1.������ʱ��*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
	/*2.����һ��GPIO��ʼ���ṹ��*/
	GPIO_InitTypeDef GPIO_InitStruct;
	/*3.����GPIO��ʼ���ṹ��ĳ�Ա*/
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;   //���е�״̬�����ⲿ������û����������
	/*4.����GPIO��ʼ�������������úõ�GPIO��ʼ���ṹ��ĳ�Ա�Ĳ���д��Ĵ���*/
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
}
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON )
	{
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON )
		{
			return KEY_ON;
		}
	}
	else 
		return KEY_OFF;
}
