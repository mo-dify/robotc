#include "stm32f10x_conf.h"
#include "timer.h"
#define DTIME 500

uint32_t Timer3_Count = 0;//记录Timer3中断次数
uint16_t Timer3_Frequency;//Timer3中断频率

int flag_1HZ=0;
uint32_t Timer3_Count100Hz = 0;
int flag_100HZ=0;
int delay_count = 0;



void timer3_init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	Timer3_Frequency = Handler_Frequency;
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;//装载值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	//分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分割时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//按照指定的参数初始化TIMx的事件基数单位	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//清除中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能指定的TIM3中断，允许更新中断
	
	
	TIM_Cmd(TIM3,ENABLE);//使能定时器timx
	
	//中断优先级设定nvic设置
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//time3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//从占优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);//初始化寄存器
	
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)//Timer3中断
{
	if(TIM3->SR & TIM_IT_Update)//检查tim3定时器更新中断是否发生
	{     
		TIM3->SR = ~TIM_FLAG_Update;//清除中断标志
		delay_count++;
		Timer3_Count++;
		if(Timer3_Count == 1000){
			flag_1HZ = 1;
			Timer3_Count=0;
		}
		if(Timer3_Count100Hz++ == 100){
			flag_100HZ = 1;
			Timer3_Count100Hz = 0;
		}
	}
}

void msdelay(int ms)
{
	delay_count = 0;
	while(delay_count < ms);
}
void walk()
{
		//抬左脚
		TIM2->CCR1=1650;
		TIM2->CCR2=1800;
		msdelay(DTIME);
		//扭动
		TIM2->CCR3=1150;
		TIM2->CCR4=1150;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
		
		//抬右脚		
		TIM2->CCR2=1350;
		TIM2->CCR1=1100;
		msdelay(DTIME);
		//扭动		
		TIM2->CCR3=1750;
		TIM2->CCR4=1750;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
}
void dance()
{
	int i=3,j=3,k=3;
	//第一拍
		while(i--)
		{
			//收腿
			TIM2->CCR1=1350;
			TIM2->CCR2=1700;
			msdelay(DTIME);
		//站立
			TIM2->CCR1=1500;
			TIM2->CCR2=1500;
			msdelay(DTIME);
			//
			TIM2->CCR1=1750;
			TIM2->CCR2=1250;
			msdelay(DTIME);
			
				TIM2->CCR1=1500;
		TIM2->CCR2=1500;
		msdelay(DTIME);
		}
		TIM2->CCR1=1500;
		TIM2->CCR2=1500;
		msdelay(DTIME);
		while(j--)
		{
			TIM2->CCR1=1250;
			msdelay(DTIME);
			TIM2->CCR1=1500;
			msdelay(DTIME);
		}
		while(k--)
		{
			TIM2->CCR2=1850;
			msdelay(DTIME);
			TIM2->CCR2=1500;
			msdelay(DTIME);
		}
		TIM2->CCR1=1500;
		TIM2->CCR2=1500;
		msdelay(DTIME);
}
void round_left()
{
	int i=10;
while(i--)
{	
		//抬左脚
		TIM2->CCR1=1750;
		msdelay(DTIME);
		TIM2->CCR2=2050;
		msdelay(DTIME);
		//扭动
		TIM2->CCR3=1300;
		TIM2->CCR4=1750;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
			//抬右脚		
		TIM2->CCR2=1250;
		TIM2->CCR1=1000;
		msdelay(DTIME);
		//扭动		
		TIM2->CCR3=1500;
		TIM2->CCR4=1500;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	}
}

void round_right(void)
{
		int i=10;
while(i--)
{	
	
		//抬右脚		
		TIM2->CCR2=1250;
		TIM2->CCR1=1000;
		msdelay(DTIME);
		//扭动		
		TIM2->CCR3=1350;
		TIM2->CCR4=1700;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
			//抬左脚
		TIM2->CCR1=1750;
		msdelay(DTIME);
		TIM2->CCR2=2050;
		msdelay(DTIME);
		//扭动
		TIM2->CCR3=1500;
		TIM2->CCR4=1500;
		msdelay(DTIME);
		//落脚		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
	}
}