#include "timer2.h"

void timer2_init()
{
	//��tim2��ʱ��
	RCC->APB1ENR |= 0x01;
	//��gpioA��ʱ��
	RCC->APB2ENR |=	0x5;
	RCC->APB2ENR |= 1<<2;
	//��λbit0
	GPIOA->CRL &=0xffff0000;
	//��1011���򿪹ܽţ������������
	GPIOA->CRL |=0xbbbb;
	//��Ƶ���������
	TIM2->PSC=71;
	//����װ��ֵ
	TIM2->ARR=20000;
	//ʹ��CCRx�Ĵ���
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



