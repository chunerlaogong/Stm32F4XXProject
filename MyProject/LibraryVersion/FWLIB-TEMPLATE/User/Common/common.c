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
void delay_init(u8 SYSCLK)
{
#if SYSTEM_SUPPORT_OS 						//��?1?D����a?��3?OS.
	u32 reload;
#endif
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;						//2???��?��?��1��?OS,fac_us??D����a��1��?
#if SYSTEM_SUPPORT_OS 						//��?1?D����a?��3?OS.
	reload=SYSCLK/8;						//?????����???��y��?��y �̣�???aM	   
	reload*=1000000/delay_ostickspersec;	//?��?Ydelay_ostickspersec����?����?3?����??
											//reload?a24????��??��,��?�䨮?��:16777216,?��168M??,??o?0.7989s��������	
	fac_ms=1000/delay_ostickspersec;		//�䨲����OS?����??��������?��?�����̣�??	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//?a??SYSTICK?D??
	SysTick->LOAD=reload; 					//??1/delay_ostickspersec???D??��?��?	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//?a??SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;				//��?OS??,�䨲����????msD����a��?systick����?����y   
#endif
}		

