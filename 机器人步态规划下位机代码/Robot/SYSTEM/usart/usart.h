#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
//////////////////////////////////////////////////////////////////////////////////	 


////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART2_RX 			0		//使能（1）/禁止（0）串口1接收
#define EN_USART1_RX 1
extern u8 Receive_data[10];	  	
extern UART_HandleTypeDef UART1_Handler; //UART句柄
extern UART_HandleTypeDef UART2_Handler; //UART句柄
extern u8 Receive_Data[11];
#define RXBUFFERSIZE   1 //缓存大小
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL库USART接收Buffer

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
u8 Check_Sum_State (void);
void Check_Receivedata(u8 *ReceiveStata,u8 *ServoStata);
#endif
