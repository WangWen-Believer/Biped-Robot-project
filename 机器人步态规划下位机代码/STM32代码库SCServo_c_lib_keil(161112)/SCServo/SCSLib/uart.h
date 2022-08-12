#ifndef		_UART_H
#define		_UART_H

#include <stdint.h>
extern void Uart_Init(uint32_t baudRate);
extern void Uart1_Flush(void);
extern short Uart1_Read(void);
extern void Uart1_DmaSend(uint8_t *buf , uint8_t len);

#endif
