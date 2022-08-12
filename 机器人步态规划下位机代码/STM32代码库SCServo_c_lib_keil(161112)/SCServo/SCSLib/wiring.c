#include "stm32f10x.h"

__IO uint32_t TimingMillis = 0;


uint32_t millis(void)
{
	return TimingMillis;
}

void delay(uint32_t ms)
{
    uint32_t end = millis() + ms;
    while (millis() < end);
}

void SysTick_Handler(void)
{
	SysTick->CTRL &= ~(1<<16);
	TimingMillis++;
}
