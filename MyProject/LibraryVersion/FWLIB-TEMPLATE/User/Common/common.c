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
#if SYSTEM_SUPPORT_OS 						//豕?1?D豕辰a?∫3?OS.
	u32 reload;
#endif
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;						//2???那?﹞?那1車?OS,fac_us??D豕辰a那1車?
#if SYSTEM_SUPPORT_OS 						//豕?1?D豕辰a?∫3?OS.
	reload=SYSCLK/8;						//?????車米???那y∩?那y 米ㄓ???aM	   
	reload*=1000000/delay_ostickspersec;	//?迄?Ydelay_ostickspersec谷豕?“辰?3?那㊣??
											//reload?a24????∩??¯,℅?∩車?米:16777216,?迆168M??,??o?0.7989s℅車車辰	
	fac_ms=1000/delay_ostickspersec;		//∩迆㊣赤OS?谷辰??車那㊣米?℅?谷迄米ㄓ??	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//?a??SYSTICK?D??
	SysTick->LOAD=reload; 					//??1/delay_ostickspersec???D??辰?∩?	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//?a??SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;				//﹞?OS??,∩迆㊣赤????msD豕辰a米?systick那㊣?車那y   
#endif
}		

