#include "bsp_usart.h"

void USART2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//GPIOA �� USART1 ʱ��ʹ�ܢ�
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //ʹ�� GPIOD ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ�� USART2 ʱ��
//USART_DeInit(USART1); //��λ���� 1 ��
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //PD5 ����Ϊ USART2
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //PD6����Ϊ USART2
//USART1_TX PD5 PD6 ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOD5 �� GPIOD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ�� PD5�� PD6
//USART ��ʼ������ ��
    USART_InitStructure.USART_BaudRate = 115200;//һ������Ϊ 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ 8 λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������
#if EN_USART2_RX
    //Usart2 NVIC ���� ��
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //��Ӧ���ȼ� 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ�� VIC �Ĵ���
    //NVIC ���ã�ʹ���ж�
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
#endif
    USART_Cmd(USART2, ENABLE); //ʹ�ܴ���
}
void USART1_Init()
{
    //GPIO???������??
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //��1?��GPIOA����?��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //��1?��USART1����?��

    //��??��1??��|��y???�䨮?��3��?
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9?�䨮??aUSART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,
                     GPIO_AF_USART1); //GPIOA10?�䨮??aUSART1

    //USART1???��????
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��?GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//?�䨮?1|?��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //?��?��50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //��?����?�䨮?��?3?
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //��?��-
    GPIO_Init(GPIOA, &GPIO_InitStructure); //3?��??��PA9��?PA10

    //USART1 3?��??������??
    USART_InitStructure.USART_BaudRate = 115200;//2����??������??
    USART_InitStructure.USART_WordLength =
        USART_WordLength_8b;//��?3��?a8??��y?Y??��?
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//��???����?1??
    USART_InitStructure.USART_Parity = USART_Parity_No;//?T????D��?��??
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;//?T��2?t��y?Y����????
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //��?����?�꨺?
    USART_Init(USART1, &USART_InitStructure); //3?��??����??��1

    USART_Cmd(USART1, ENABLE);  //��1?����??��1

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART1_RX
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//?a???��1??D??
    //Usart1 NVIC ????
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//��??��1?D??�����̨�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //?��??��??��??3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //������??��??3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ�����̨���1?��
    NVIC_Init(&NVIC_InitStructure); //?��?Y???����?2?��y3?��??��VIC??��??��?��

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
    /*����һ���ֽڵ�USART*/
    USART_SendData(pUSARTx, ch);
    /*�ȴ����ݼĴ���Ϊ��*/
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}










