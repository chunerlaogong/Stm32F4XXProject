#include "common.h"
						
void Delay(unsigned int count)
{
	while(count--);
}
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			
	SysTick->VAL =0x00;           			
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;         
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	  
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;     
	SysTick->VAL =0X00;     		  	 	    
}

void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;						
											
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
}
	

