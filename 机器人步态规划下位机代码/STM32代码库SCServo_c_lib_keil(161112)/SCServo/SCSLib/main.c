#include "stm32f10x.h"
#include "wiring.h"

extern void setup(void);
extern void loop(void);

void initSys(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
  //UART1-TX/RX---->PB6/PB7(≤ø∑÷”≥…‰)
  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

  // 2 bit for pre-emption priority, 2 bits for subpriority
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	SysTick_Config(SystemCoreClock / 1000);
}

int main()
{
	initSys();
	setup();
	while(1){
		loop();
	}
}
