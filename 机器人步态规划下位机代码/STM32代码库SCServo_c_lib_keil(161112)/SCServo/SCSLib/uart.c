/*
 * uart.c
 * UART接口
 * 日期: 2016.11.11
 * 作者: 谭雄乐
 */

#include "stm32f10x.h"
#include "uart.h"

//UART 读数据缓冲区
__IO uint8_t uart1Buf[128];
__IO int head1 = 0;
__IO int tail1  = 0;

void Uart1_Flush(void)
{
	head1 = tail1 = 0;
}

short Uart1_Read(void)
{
	if(head1!=tail1){
		uint8_t Data = uart1Buf[head1];
		head1 =  (head1+1)%128;
		return Data;
	}else{
		return -1;
	}
}

void Uart_Init(uint32_t baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//UART1 GPIO 配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PB6 UART1_TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PB7 UART1_RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	//DMA 配置
	//UART1	DMA
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;
  DMA_InitStructure.DMA_BufferSize = 0;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel4, ENABLE);
  
	//UART 数据格式配置
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_Init(USART1, &USART_InitStructure);
	
	//中断配置
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//打开DMA与UART使能开关
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
		uart1Buf[tail1] = USART1->DR;
		tail1 = (tail1+1)%128;
}

void Uart1_DmaSend(uint8_t *buf , uint8_t len)
{
	USART1->SR &= ~(1<<6);
	DMA1_Channel4->CCR &= ~0x01;
	DMA1_Channel4->CMAR = (uint32_t)buf;
	DMA1_Channel4->CNDTR = len;
	DMA1_Channel4->CCR |= 0x01;
	while(!(USART1->SR&(1<<7)));
	while(!(USART1->SR&(1<<6)));
}
