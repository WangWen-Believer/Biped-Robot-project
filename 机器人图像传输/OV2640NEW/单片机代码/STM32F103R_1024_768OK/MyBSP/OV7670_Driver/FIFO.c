# include "FIFO.h"
void FIFO2_PortInit(void);
void FIFO_PortInit(void)
{
	RCC->APB2ENR |= BIT(3);				//PB时钟时能
	GPIOB->CRL &= 0xfffffff0;
	GPIOB->CRL |= 0x00000003;			//PB0 FIFO_WEN
	GPIOB->ODR |= BIT(0);

	GPIOB->CRL &= 0xff0fffff;			//PB5 FIFO_WRST
	GPIOB->CRL |= 0x00300000;			
	GPIOB->ODR |= BIT(5);
	
	GPIOB->CRL &= 0xfffff0ff;
	GPIOB->CRL |= 0x00000300;			//PB2 FIFO_RRST
	GPIOB->ODR |= BIT(2);
	
	GPIOB->CRH = 0x88888888;			//PB8-15 输入
	GPIOB->ODR |= 0xff00;				//上拉
	
	RCC->APB2ENR |= BIT(2);				//PA时钟时能
	GPIOA->CRL &= 0xfffff0ff;			//PA2 FIFO_RCLK
	GPIOA->CRL |= 0x00000300;
	GPIOA->ODR |= BIT(2);
	
	GPIOA->CRL &= 0xffffff0f;			//PA1 FIFO_OE
	GPIOA->CRL |= 0x00000030;
	GPIOA->ODR |= BIT(1);
}

void FIFO_WrRdReset(void)
{
	FIFO_RRST_L;				//读指针复位						
	FIFO_RCLK_L;				//至少需要一个时钟周期的跳变才能复位
	FIFO_RCLK_H;
	FIFO_RCLK_L;				//至少需要一个时钟周期的跳变才能复位
	FIFO_RCLK_H;
	FIFO_RRST_H;
								//写指针复位
	FIFO_WEN_L;					//按照手册上说明,复位时WEN要置高,但 
	FIFO_WRST_L;				//MCU的WEN和HREF是做与非逻辑后再输入								
	__nop();					//到AL422B的,所以MCU的WEN置低则输出到422的WEN一定为低
	__nop();					//写指针复位需要一定的延时			
	FIFO_WRST_H;
}
u8 FIFO_GetData(void)
{
	u8 temp = 0;
	FIFO_DATA_IN;
	temp = FIFO_DATA_PIN;
	FIFO_DATA_OUT;
	return temp;
}
