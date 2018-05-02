#ifndef _BSP_USART_H
#define _BSP_USART_H
#define EN_USART2_RX 1
#include "stm32f4xx.h" 
#include "stdio.h"	
#include "stm32f4xx_conf.h"

             //接收数据状态


/*串口初始化参数结构体*/
typedef struct 
{
	u32 USART_Num;           //串口号
	u32 GPIO_Num;            //GPIO组号
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
}USART_InitParamDef;


void USART2_Init(u32 USART_BaudRate);
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void u2_printf(char* fmt, ...);	
void USART2_Test(void);
void Usart2_Send_isr(uint8_t ch);
void Usart2_sendstring(uint8_t* cp) ;
#endif   //BSP_USART_H
