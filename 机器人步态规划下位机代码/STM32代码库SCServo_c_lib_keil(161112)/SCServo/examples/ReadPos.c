#include "stm32f10x.h"
#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

void setup(void)
{
	Uart_Init(1000000);
	delay(500);
	EnableTorque(1, 0);
	EnableTorque(2, 1);
}

void loop(void)
{
	int pos = ReadPos(1);
	if(pos!=-1)
	{
		WritePos(2, pos, 0, 0);
    delay(10);
	}
	else
	{
    delay(2000);
	}
}
