#include"led.h"

//≥ı ºªØled
void led_init()
{
	GPIO_InitTypeDef gpio_initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_StructInit(&gpio_initstruct);

	gpio_initstruct.GPIO_Pin=GPIO_Pin_8;
	gpio_initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_initstruct);
}

void delay()
{
	int i,j;
	//for(i=0;i<1000;i++)
		for(j=0;j<1000;j++);
}
