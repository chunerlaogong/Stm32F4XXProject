#include "bsp_exti_key.h"

static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    /*����NVICΪ������1*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*�����ж�Դ: ����0*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;
    /*������ռ���ȼ���1*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;
    /*���������ȼ���1*/
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    /*ʹ���ж�ͨ��*/
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	/*����1*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	/*����2*/
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
    /*1.��ʼ����Ҫ���ӵ�EXTI�ߵ�GPIO*/
    /*��������GPIO��ʱ��*/
    RCC_AHB1PeriphClockCmd(KEY_INT_GPIO_CLK, ENABLE);
    /*2.��ʼ��EXTI*/
    GPIO_InitStruct.GPIO_Pin = KEY0_INT_GPIO_PIN | KEY1_INT_GPIO_PIN | KEY2_INT_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Pin = KEY0_INT_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(KEY_INT_GPIO_PORT, &GPIO_InitStruct);
    /*ʹ��SYSCFGʱ�ӣ�ʹ��GPIO�ⲿ�ж�ʱ����ʹ��SYSCFGʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /*����EXTI�ж�Դ��Key1����*/
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY0_INT_EXTI_PINSOURCE);
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
    SYSCFG_EXTILineConfig(KEY_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE);
    /*ѡ��EXTI�ж�Դ*/
    EXTI_InitStruct.EXTI_Line = KEY0_INT_EXTI_LINE | KEY1_INT_EXTI_LINE | KEY2_INT_EXTI_LINE;                            
    /*�ж�ģʽ*/
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /*�����ش���*/
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    /*ʹ���ж�/�¼���*/
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    /*3.����NVIC*/
    NVIC_Config();
    /*4.��д�ж��жϷ�����*/
}
