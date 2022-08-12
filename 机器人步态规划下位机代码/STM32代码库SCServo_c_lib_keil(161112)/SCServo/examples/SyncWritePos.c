#include "stm32f10x.h"
#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

uint8_t ID[2];
void setup(void)
{
  Uart_Init(1000000);
  delay(500);
  EnableTorque(1, 1);
  EnableTorque(2, 1);
  ID[0] = 1;
  ID[1] = 2;
}

void loop(void)
{
	SyncWritePos(ID, 2, 0, 4000, 0);
	delay(4000);
	SyncWritePos(ID, 2, 1023, 4000, 0);
	delay(4000);
}
