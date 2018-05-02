#include "bsp_usart.h"
#include "common.h"
void USART2_Init(u32 USART_BaudRate)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

//1.����ʱ�Ӻͺ�GPIOʱ��ʹ�ܡ�
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ��USART2ʱ��
//2.�������Ÿ�����ӳ��
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA2����ΪUSART2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA3����ΪUSART2

//3.GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3��ʼ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIOA2����GPIOA3
//4.���ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ���
    USART_InitStructure.USART_BaudRate = 115200;//������һ������Ϊ115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl =
    USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������2����
//5.��ʼ��NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ; //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);
//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//6.�����ж�
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
//7.ʹ�ܴ���
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
}
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    USART_SendData(USART2, ch);         //�򴮿�2��������
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //�ȴ����ͽ���
}
#define USART2_MAX_RECV_LEN 400     //�����ջ����ֽ���
#define USART2_MAX_SEND_LEN 400     //����ͻ����ֽ���
#define USART2_RX_EN 1              //0,������;1,����.                 

u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; //���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
u16 USART2_RX_STA = 0;

void USART2_Test(void)
{
    u8 t;
    u8 len;
    u16 times = 0;
    u8 USART_RX_BUF1[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '\n'};
    while(1)
    {
        if(USART2_RX_STA & 0x8000)
        {
            len = USART2_RX_STA & 0x3fff; //�õ��˴ν��յ������ݳ���
            for(t = 0; t < len; t++)
            {
                USART_SendData(USART2, USART2_RX_BUF[t]);         //�򴮿�2��������
                while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //�ȴ����ͽ���
            }
            USART2_RX_STA = 0;
        }
        else
        {
            times++;
            if(times % 50 == 0)
            {
                for(t = 0; t < 10; t++)
                {
                    USART_SendData(USART2, USART_RX_BUF1[t]);         //�򴮿�2��������
                    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //�ȴ����ͽ���
                }
            }
            delay_ms(10);
        }
    }
}

void Usart2_Send_isr(uint8_t ch)
{
    USART2->DR=ch;
    while((USART2->SR & 0x40)==0);
}
void Usart2_sendstring(uint8_t* cp)
{
    while((*cp) != '\0')
    {
        Usart2_Send_isr(*cp);
        cp++;
    }
}











