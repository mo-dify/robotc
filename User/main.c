#include "stm32f10x_conf.h"
#include "timer2.h"
#include "timer.h"
#include "usart3.h"
#include "usart1.h"
#include "led.h"
int main()
{
	//初始化tim2定时器
	timer2_init();
	//初始化tim3定时器
	timer3_init(1000);
	//初始化led等、以及串口用管脚
	led_init();
	//初始化串口1
	usart_init1();
	//初始化串口3，并设置波特率为115200
	Uart3_Init(115200);
	//设置中断
	NVIC_Configuration1();
	//初始化wifi模块并打开
	wifi_init();
	//初始化舵机的角度，使其呈水平状态
	TIM2->CCR1=1500;
	TIM2->CCR2=1500;
	msdelay(1000);
	while(1)
	{
		//前进
		if(flag_w)
			walk();
		//向左转10拍
		if(flag_a)
			round_left();
		//向右转10拍
		if(flag_d)
			round_right();
		//跳舞
		if(flag_h)
			dance();
	}
	return 0;
}

