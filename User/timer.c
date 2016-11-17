#include "stm32f10x_conf.h"
#include "timer.h"
#define DTIME 500

uint32_t Timer3_Count = 0;//��¼Timer3�жϴ���
uint16_t Timer3_Frequency;//Timer3�ж�Ƶ��

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
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;//װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	//��Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //���ָ�ʱ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//����ָ���Ĳ�����ʼ��TIMx���¼�������λ	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//����жϱ�־
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//ʹ��ָ����TIM3�жϣ���������ж�
	
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܶ�ʱ��timx
	
	//�ж����ȼ��趨nvic����
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//time3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���Ĵ���
	
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)//Timer3�ж�
{
	if(TIM3->SR & TIM_IT_Update)//���tim3��ʱ�������ж��Ƿ���
	{     
		TIM3->SR = ~TIM_FLAG_Update;//����жϱ�־
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
		//̧���
		TIM2->CCR1=1650;
		TIM2->CCR2=1800;
		msdelay(DTIME);
		//Ť��
		TIM2->CCR3=1150;
		TIM2->CCR4=1150;
		msdelay(DTIME);
		//���		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
		
		//̧�ҽ�		
		TIM2->CCR2=1350;
		TIM2->CCR1=1100;
		msdelay(DTIME);
		//Ť��		
		TIM2->CCR3=1750;
		TIM2->CCR4=1750;
		msdelay(DTIME);
		//���		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
}
void dance()
{
	int i=3,j=3,k=3;
	//��һ��
		while(i--)
		{
			//����
			TIM2->CCR1=1350;
			TIM2->CCR2=1700;
			msdelay(DTIME);
		//վ��
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
		//̧���
		TIM2->CCR1=1750;
		msdelay(DTIME);
		TIM2->CCR2=2050;
		msdelay(DTIME);
		//Ť��
		TIM2->CCR3=1300;
		TIM2->CCR4=1750;
		msdelay(DTIME);
		//���		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
			//̧�ҽ�		
		TIM2->CCR2=1250;
		TIM2->CCR1=1000;
		msdelay(DTIME);
		//Ť��		
		TIM2->CCR3=1500;
		TIM2->CCR4=1500;
		msdelay(DTIME);
		//���		
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
	
		//̧�ҽ�		
		TIM2->CCR2=1250;
		TIM2->CCR1=1000;
		msdelay(DTIME);
		//Ť��		
		TIM2->CCR3=1350;
		TIM2->CCR4=1700;
		msdelay(DTIME);
		//���		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
			//̧���
		TIM2->CCR1=1750;
		msdelay(DTIME);
		TIM2->CCR2=2050;
		msdelay(DTIME);
		//Ť��
		TIM2->CCR3=1500;
		TIM2->CCR4=1500;
		msdelay(DTIME);
		//���		
		TIM2->CCR2=1500;
		TIM2->CCR1=1500;
		msdelay(DTIME);
	
	}
}