#include "stm32f10x_conf.h"
#include "misc.h"
#include "usart3.h"

int flag_w=0;
int flag_h=0;
int flag_a=0;
int flag_d=0;

//�����ж�
void NVIC_Configuration1()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ö˿ڵ�ʱ�򣬼ǵ�һ��Ҫ���������Ϸ�Ǽ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//��ʼ������1
void usart_init1()
{
	GPIO_InitTypeDef GPIO_init;//��ʼ���ṹ��
	USART_InitTypeDef USART_init;
	GPIO_StructInit(&GPIO_init);//���ÿ⺯���Խṹ����г�ʼ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

	GPIO_init.GPIO_Pin = GPIO_Pin_4;
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_init);
	GPIO_StructInit(&GPIO_init);
	
	//����1��������ӿڳ�ʼ��
	GPIO_init.GPIO_Pin = GPIO_Pin_9;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_init);	
	GPIO_init.GPIO_Pin = GPIO_Pin_10;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_init);
	//����2��ʼ����������ӿ�
	GPIO_init.GPIO_Pin = GPIO_Pin_10;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_init);
	GPIO_init.GPIO_Pin = GPIO_Pin_11;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_init);
	
	//����1��ʼ��
	USART_StructInit(&USART_init);//���ÿ⺯�����г�ʼ��
	USART_init.USART_BaudRate=115200;
	USART_Init(USART1,&USART_init);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����ж�
	USART_Cmd(USART1,ENABLE);//��������
}

void uart1_putchar(unsigned char c)
{                               
    USART_SendData(USART1, c);                                   
    //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
}

void delay1()
{
	int i,j;
	for(i=0;i<1000;i++)
		for(j=0;j<1000;j++);
}
void USART1_IRQHandler(void)
{
  uint16_t l_tmp; //Received char from USART1
  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);//�崮�ڽ����ж�
    //Read one byte from the receive data register
    l_tmp  = USART_ReceiveData(USART1);
		USART3_PrintHexU8(l_tmp);
  }
  USART_ClearITPendingBit(USART1, USART_IT_ORE);//�崮�����ж�
}
//�жϿͻ��˷����Ŀ�����Ϣ
void check(uint8_t tmp)
{
		if(tmp=='w')
		{
			 flag_w=1;
			 flag_h=0;
			 flag_a=0;  
				flag_d=0;
		}
		if(tmp=='h')
		{
			flag_w=0;
			flag_h=1;
			flag_a=0;
			flag_d=0;
		}
		if(tmp=='a')
		{
			 flag_w=0;
			 flag_d=0;
			 flag_a=1;
			 flag_d=0;
		}
		if(tmp=='d')
		{
			 flag_w=0;
			 flag_h=0;
			 flag_a=0;
			 flag_d=1;
		}
		if(tmp=='p')
		{
			 flag_w=0;
			 flag_h=0;
			 flag_a=0;
			 flag_d=0;
		}
}
//����wifi�յ�����Ϣ
void b_check(uint8_t c)
{
	static int pos=1;
		if(pos==0 && c== 'I')
		{
			pos++;
		}
		if(pos==1 && c== 'P')
		{
			pos++;
		}	
		if(pos==2 && c== 'D')
		{
			pos++;
		}	
		if(pos==3 && c== ',')
		{
			pos++;
		}	
		if(pos==4 && c!=',')
		{
			pos++;
		}
		if(pos==5 && c==',')
		{
			pos++;
		}
		if(pos==6 && c!=',')
		{
			pos++;
		}
		if(pos==7 && c==':')
		{
			pos++;
		}
		else	
		   if(pos==8)
		{
			check(c);
			pos=1;
		}


}









