#include "timer2.h"

void timer2_init()
{
	//打开tim2的时钟
	RCC->APB1ENR |= 0x01;
	//打开gpioA的时钟
	RCC->APB2ENR |=	0x5;
	RCC->APB2ENR |= 1<<2;
	//置位bit0
	GPIOA->CRL &=0xffff0000;
	//（1011）打开管脚，复用推挽输出
	GPIOA->CRL |=0xbbbb;
	//分频，方便计数
	TIM2->PSC=71;
	//设置装在值
	TIM2->ARR=20000;
	//使能CCRx寄存器
	TIM2->CCMR1=0x6060;
	TIM2->CCMR1|=1<<3;
	TIM2->CCMR1|=1<<11;
	
	TIM2->CCMR2=0x6060;
	TIM2->CCMR2|=1<<3;
	TIM2->CCMR2|=1<<11;
	
	TIM2->CR1|=1<<7;
	TIM2->EGR|=0x1;
	
	TIM2->CCER|=0x1111;
	TIM2->CR1 |=0x1;
}



