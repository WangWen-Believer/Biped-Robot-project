#ifndef USART_H_H_
#define USART_H_H_

#include "stm32f10x.h"

#define COMn                             2

//抢占优先级
#define USART_NVIC_PREE_PRI				0	
/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define USART_COM1                        USART1
#define USART_COM1_CLK                    RCC_APB2Periph_USART1
#define USART_COM1_TX_PIN                 GPIO_Pin_9
#define USART_COM1_TX_GPIO_PORT           GPIOA
#define USART_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM1_RX_PIN                 GPIO_Pin_10
#define USART_COM1_RX_GPIO_PORT           GPIOA
#define USART_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM1_IRQn                   USART1_IRQn
#define USART_COM1_IRQHandler 			  USART1_IRQHandler
#define USART_COM1_Prio					   0

/**
 * @brief Definition for COM port2, connected to USART2
 */ 
#define USART_COM2                        USART2
#define USART_COM2_CLK                    RCC_APB1Periph_USART2
#define USART_COM2_TX_PIN                 GPIO_Pin_2
#define USART_COM2_TX_GPIO_PORT           GPIOA
#define USART_COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM2_RX_PIN                 GPIO_Pin_3
#define USART_COM2_RX_GPIO_PORT           GPIOA
#define USART_COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM2_IRQn                   USART2_IRQn
#define USART_COM2_IRQHandler 			  USART2_IRQHandler
#define  USART_COM2_Prio					   1

typedef enum 
{
  	COM1 = 0,
  	COM2 = 1
}
COM_TypeDef;   

#define USART_Transmit(n)		USART1_Transmit(n)

void USART1_Init(u32 baud_rate);
void USART2_Init(u32 baud_rate);

void USART1_Transmit(u8 ch_data);
void USART2_Transmit(u8 ch_data);

void USART1_RxIntHandler(void);
void USART2_RxIntHandler(void);

void USART_Debug(u8 debug_data);
void USART_SendLine(s32 Data ,
					u8 Is_H, 
				    u8 Line_ID);
void USART_SendString(unsigned char *p_STR);

u8 USART_GetChar(u8* p_array, u8 frame_len);
u8 USART_GetRate(s32* p_rate);

///////////////////////////////
//调试用串口打印函数
void Prints(const u8 * pd);
void PrintLongInt(u32 x);
void PrintShortIntHex(u16 x);
void PrintHex(u8 x);

///////////////////////////////
#endif
