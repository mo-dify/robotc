#include "stm32f10x_conf.h"
#include "usart1.h"
#include "usart3.h"
#define RX_BUFF_SIZE	256
uint8_t USART3_TxCount=0;
uint8_t USART3_Count=0;
static uint8_t USART3_TxBuff[512];	//���ڷ��ͻ�����
static uint8_t set_mux[256]="AT+CIPMUX=1\r\n";
static uint8_t set_server[256]="AT+CIPSERVER=1,8080\r\n";
//��Ϣ���У�������
static uint8_t USART3_RxBuff[RX_BUFF_SIZE];//
static uint8_t USART3_Rx_wr=0;
static uint8_t USART3_Rx_rd=0;
//��ʼ������3
void Uart3_Init(uint32_t baud)
{
	USART_InitTypeDef USART_init;
	//��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	
	USART_StructInit(&USART_init);
	USART_init.USART_BaudRate=baud;
	USART_Init(USART3,&USART_init);
	//ʹ�ܴ���3�����ж�
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	//ʹ�ܴ���3
	USART_Cmd(USART3,ENABLE);
	//��������ɱ�־λ
	USART_ClearFlag(USART3,USART_FLAG_TC);
}

//����3�жϺ���
void USART3_IRQHandler(void)
{
	uint8_t com_data;
	if(USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)//ORE�ж�
	{
	//	uart1_putchar('g');
		com_data=USART_ReceiveData(USART3);
		uart1_putchar(com_data);
	}
	if(USART3->SR & USART_SR_TC && (USART3->CR1 & USART_CR1_TXEIE) )//�����ж�
		{
		USART3->DR = USART3_TxBuff[USART3_TxCount++];//дDR����жϱ�־          
		if(USART3_TxCount == USART3_Count)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;//�ر�TXE�ж�
		}
	}
	if(USART3->SR & USART_SR_RXNE)//�����ж�
	{
		
		com_data = USART3->DR;
		//uart1_putchar('c');
		uart1_putchar(com_data);
		//+IPD,0,1:w
		//���յ������ݱ��浽�ַ�������
		b_check(com_data);
		//USART3_RxBuff[USART3_Rx_wr++%RX_BUFF_SIZE]=com_data;
	}
	USART_ClearITPendingBit(USART1, USART_IT_ORE);//�崮�����ж�
}

//ͨ������3��wifiģ�鷢������
void USART3_PrintHexU8(uint8_t data)
{
	USART3_TxBuff[USART3_Count++] = data;  
	if(!(USART3->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //��TXE�ж�
}

void send_delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<1000;j++);
}
void wifi_init()
{
	int i=0;

	//delay1();
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	//delay1();
	send_delay(3000);
  //send_delay(1000);
	while(i<15)
	{
		USART3_PrintHexU8(set_mux[i]);
		i++;
	}
	send_delay(1000);
	i=0;
	while(i<23)
	{
		USART3_PrintHexU8(set_server[i]);
		i++;
	}
}
//��Ϣ���д���ģ���շ���Ϣ��û��ʵ��
int USART3_bytes(void)
{
	return USART3_Rx_wr - USART3_Rx_rd;
}
uint8_t USART_GdtHexU8()
{
	if(USART3_bytes()==0)
		return 0;
	uart1_putchar(USART3_RxBuff[USART3_Rx_rd%RX_BUFF_SIZE]);
		return USART3_RxBuff[USART3_Rx_rd++%RX_BUFF_SIZE];
}
