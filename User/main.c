#include "stm32f10x_conf.h"
#include "timer2.h"
#include "timer.h"
#include "usart3.h"
#include "usart1.h"
#include "led.h"
int main()
{
	//��ʼ��tim2��ʱ��
	timer2_init();
	//��ʼ��tim3��ʱ��
	timer3_init(1000);
	//��ʼ��led�ȡ��Լ������ùܽ�
	led_init();
	//��ʼ������1
	usart_init1();
	//��ʼ������3�������ò�����Ϊ115200
	Uart3_Init(115200);
	//�����ж�
	NVIC_Configuration1();
	//��ʼ��wifiģ�鲢��
	wifi_init();
	//��ʼ������ĽǶȣ�ʹ���ˮƽ״̬
	TIM2->CCR1=1500;
	TIM2->CCR2=1500;
	msdelay(1000);
	while(1)
	{
		//ǰ��
		if(flag_w)
			walk();
		//����ת10��
		if(flag_a)
			round_left();
		//����ת10��
		if(flag_d)
			round_right();
		//����
		if(flag_h)
			dance();
	}
	return 0;
}

