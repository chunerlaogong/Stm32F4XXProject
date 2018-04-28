#include "bsp_usart.h"

void USART2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//GPIOA 和 USART1 时钟使能①
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //使能 GPIOD 时钟
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能 USART2 时钟
//USART_DeInit(USART1); //复位串口 1 ②
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //PD5 复用为 USART2
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //PD6复用为 USART2
//USART1_TX PD5 PD6 ③
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOD5 与 GPIOD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化 PD5， PD6
//USART 初始化设置 ④
    USART_InitStructure.USART_BaudRate = 115200;//一般设置为 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为 8 位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口
#if EN_USART2_RX
    //Usart2 NVIC 配置 ⑤
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级 2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //响应优先级 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 VIC 寄存器
    //NVIC 设置，使能中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
#endif
    USART_Cmd(USART2, ENABLE); //使能串口
}
void USART1_Init()
{
    //GPIO???úéè??
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ê1?üGPIOAê±?ó
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ê1?üUSART1ê±?ó

    //′??ú1??ó|òy???′ó?ó3é?
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9?′ó??aUSART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,
                     GPIO_AF_USART1); //GPIOA10?′ó??aUSART1

    //USART1???ú????
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9ó?GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//?′ó?1|?ü
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //?ù?è50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //í?íì?′ó?ê?3?
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //é?à-
    GPIO_Init(GPIOA, &GPIO_InitStructure); //3?ê??ˉPA9￡?PA10

    //USART1 3?ê??ˉéè??
    USART_InitStructure.USART_BaudRate = 115200;//2¨ì??êéè??
    USART_InitStructure.USART_WordLength =
        USART_WordLength_8b;//×?3¤?a8??êy?Y??ê?
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//ò???í￡?1??
    USART_InitStructure.USART_Parity = USART_Parity_No;//?T????D￡?é??
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;//?Tó2?têy?Yá÷????
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ê?·￠?￡ê?
    USART_Init(USART1, &USART_InitStructure); //3?ê??ˉ′??ú1

    USART_Cmd(USART1, ENABLE);  //ê1?ü′??ú1

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART1_RX
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//?a???à1??D??
    //Usart1 NVIC ????
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//′??ú1?D??í¨μà
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //?à??ó??è??3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //×óó??è??3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQí¨μàê1?ü
    NVIC_Init(&NVIC_InitStructure); //?ù?Y???¨μ?2?êy3?ê??ˉVIC??′??÷?￠

#endif
}
//??????????                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//??_sys_exit()??????????    
_sys_exit(int x) 
{ 
	x = x; 
} 
//???fputc?? 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//????,??????   
	USART1->DR = (u8) ch;      
	return ch;
}
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /*发送一个字节到USART*/
    USART_SendData(pUSARTx, ch);
    /*等待数据寄存器为空*/
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}










