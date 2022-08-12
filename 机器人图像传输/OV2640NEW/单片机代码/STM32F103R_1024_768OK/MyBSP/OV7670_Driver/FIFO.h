# ifndef FIFO_H_H_
# define FIFO_H_H_

#include "stm32f10x.h"

# ifndef _BIT
	#define _BIT
	#define BIT(n)		(1 << (n))
# endif
///////////////////////摄像头 CAM1////////////////////
//FIFO WEN引脚						
# define FIFO_WEN_BIT		0			//PB0
# define FIFO_WEN_DDR		GPIOB->CRL
# define FIFO_WEN_PORT		GPIOB->ODR

# define FIFO_WEN_L			FIFO_WEN_PORT &= ~BIT(FIFO_WEN_BIT)
# define FIFO_WEN_H			FIFO_WEN_PORT |= BIT(FIFO_WEN_BIT)

//FIFO WRST引脚						
# define FIFO_WRST_BIT		5			//PB5
# define FIFO_WRST_DDR		GPIOB->CRL
# define FIFO_WRST_PORT		GPIOB->ODR	

# define FIFO_WRST_L		FIFO_WRST_PORT &= ~BIT(FIFO_WRST_BIT)
# define FIFO_WRST_H		FIFO_WRST_PORT |= BIT(FIFO_WRST_BIT)

//FIFO RRST引脚						
# define FIFO_RRST_BIT		2			//PB2
# define FIFO_RRST_DDR		GPIOB->CRL
# define FIFO_RRST_PORT		GPIOB->ODR

# define FIFO_RRST_L		FIFO_RRST_PORT &= ~BIT(FIFO_RRST_BIT)
# define FIFO_RRST_H		FIFO_RRST_PORT |= BIT(FIFO_RRST_BIT)
//
# define FIFO_RCLK_BIT		2			//PA2
# define FIFO_RCLK_DDR		GPIOA->CRL
# define FIFO_RCLK_PORT		GPIOA->ODR

# define FIFO_RCLK_L		FIFO_RCLK_PORT &= ~BIT(FIFO_RCLK_BIT)
# define FIFO_RCLK_H		FIFO_RCLK_PORT |= BIT(FIFO_RCLK_BIT)

//
# define FIFO_OE_BIT		1			//PA1
# define FIFO_OE_DDR		GPIOA->CRL
# define FIFO_OE_PORT		GPIOA->ODR

# define FIFO_OE_L			FIFO_OE_PORT &= ~BIT(FIFO_OE_BIT)
# define FIFO_OE_H			FIFO_OE_PORT |= BIT(FIFO_OE_BIT)
//
# define FIFO_DATA_DDR		GPIOB->CRH	//PC0-7
# define FIFO_DATA_PIN		(GPIOB->IDR & 0xff00)
# define FIFO_DATA_PORT		GPIOB->ODR

# define FIFO_DATA_IN		FIFO_DATA_DDR = 0x88888888;FIFO_DATA_PORT |= 0xFF00;
# define FIFO_DATA_OUT		FIFO_DATA_DDR = 0x33333333;FIFO_DATA_PORT |= 0xFF00;

void FIFO_PortInit(void);
void FIFO_WrRdReset(void);
u8 FIFO_GetData(void);

# endif
