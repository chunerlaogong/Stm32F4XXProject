#include "bsp_key.h"

void KEY_GPIO_Config()   //设置GPIO为输入，检测按键是否按下
{
	/*1.开外设时钟*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
	/*2.定义一个GPIO初始化结构体*/
	GPIO_InitTypeDef GPIO_InitStruct;
	/*3.配置GPIO初始化结构体的成员*/
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;   //所有的状态都由外部决定，没有上拉下拉
	/*4.调用GPIO初始化函数，把配置好的GPIO初始化结构体的成员的参数写入寄存器*/
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
