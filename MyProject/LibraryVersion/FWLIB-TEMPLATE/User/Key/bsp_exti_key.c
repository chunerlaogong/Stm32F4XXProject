#include "bsp_exti_key.h"

static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    /*配置NVIC为优先组1*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*配置中断源: 按键0*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;
    /*配置抢占优先级：1*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;
    /*配置子优先级：1*/
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    /*使能中断通道*/
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	/*按键1*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	/*按键2*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void Key_EXTI_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    /*1.初始化需要连接到EXTI线的GPIO*/
    /*开启按键GPIO的时钟*/
    RCC_AHB1PeriphClockCmd(KEY_INT_GPIO_CLK, ENABLE);
    /*2.初始化EXTI*/
    GPIO_InitStruct.GPIO_Pin = KEY0_INT_GPIO_PIN | KEY1_INT_GPIO_PIN | KEY2_INT_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Pin = KEY0_INT_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(KEY_INT_GPIO_PORT, &GPIO_InitStruct);
    /*使能SYSCFG时钟，使用GPIO外部中断时必须使能SYSCFG时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /*连接EXTI中断源到Key1引脚*/
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY0_INT_EXTI_PINSOURCE);
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE);
    /*选择EXTI中断源*/
    EXTI_InitStruct.EXTI_Line = KEY0_INT_EXTI_LINE | KEY1_INT_EXTI_LINE | KEY2_INT_EXTI_LINE;                            
    /*中断模式*/
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /*上升沿触发*/
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    /*使能中断/事件线*/
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    /*3.配置NVIC*/
    NVIC_Config();
    /*4.编写中断中断服务函数*/
}
