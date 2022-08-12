#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

void setup()
{
	Uart_Init(1000000);
	delay(500);
	wheelMode(1);
	EnableTorque(1, 1);
}

void loop()
{
  WriteSpe(1, 511);
	delay(5000);
  WriteSpe(1, 0);
	delay(2000);
	WriteSpe(1, -511);
	delay(5000);
	WriteSpe(1, 0);
	delay(2000);
}
