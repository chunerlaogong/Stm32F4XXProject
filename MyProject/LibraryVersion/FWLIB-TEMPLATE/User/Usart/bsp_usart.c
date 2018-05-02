#include "bsp_usart.h"
#include "common.h"
void USART2_Init(u32 USART_BaudRate)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

//1.串口时钟和和GPIO时钟使能。
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能USART2时钟
//2.设置引脚复用器映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA2复用为USART2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA3复用为USART2

//3.GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2和GPIOA3初始化
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIOA2，和GPIOA3
//4.串口参数初始化：设置波特率，字长，奇偶校验等参数
    USART_InitStructure.USART_BaudRate = 115200;//波特率一般设置为115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =
    USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口2参数
//5.初始化NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ; //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);
//根据指定的参数初始化VIC寄存器
//6.开启中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
//7.使能串口
    USART_Cmd(USART2, ENABLE);                    //使能串口
}
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    USART_SendData(USART2, ch);         //向串口2发送数据
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //等待发送结束
}
#define USART2_MAX_RECV_LEN 400     //最大接收缓存字节数
#define USART2_MAX_SEND_LEN 400     //最大发送缓存字节数
#define USART2_RX_EN 1              //0,不接收;1,接收.                 

u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; //接收缓冲,最大USART2_MAX_RECV_LEN个字节.
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
            len = USART2_RX_STA & 0x3fff; //得到此次接收到的数据长度
            for(t = 0; t < len; t++)
            {
                USART_SendData(USART2, USART2_RX_BUF[t]);         //向串口2发送数据
                while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //等待发送结束
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
                    USART_SendData(USART2, USART_RX_BUF1[t]);         //向串口2发送数据
                    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET); //等待发送结束
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











