#ifndef _BSP_USART_H
#define _BSP_USART_H
#define EN_USART2_RX 1
#include "stm32f4xx.h" 
#include "stdio.h"	
#include "stm32f4xx_conf.h"
/*���ڳ�ʼ�������ṹ��*/
typedef struct 
{
	u32 USART_Num;           //���ں�
	u32 GPIO_Num;            //GPIO���
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
}USART_InitParamDef;


void USART2_Init(void);
void USART1_Init(void);
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
	
#endif   //BSP_USART_H
