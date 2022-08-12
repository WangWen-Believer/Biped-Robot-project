#include "stm32f10x.h"
#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

void setup(void)
{
  Uart_Init(1000000);
  delay(500);
  EnableTorque(1, 1);
  EnableTorque(2, 1);
}

void loop(void)
{
  WritePos(1, 1023, 4000, 0);// Servo ID:1, rotate to the position:0x2FF
  WritePos(2, 1023, 4000, 0);// Servo ID:2, rotate to the position:0x2FF
  delay(4000); 
  WritePos(1,0x0000, 3000, 0);// Servo ID:1, rotate to the position:0x000
  WritePos(2, 0x0000, 3000, 0);// Servo ID:1, rotate to the position:0x000
  delay(3000);
  WritePos(1, 1023, 2000, 0);// Servo ID:1, rotate to the position:0x2FF
  WritePos(2, 1023, 2000, 0);// Servo ID:2, rotate to the position:0x2FF
  delay(2000);
  WritePos(1, 0x0000, 1000, 0);// Servo ID:1, rotate to the position:0x000
  WritePos(2, 0x0000, 1000, 0);// Servo ID:2, rotate to the position:0x000
  delay(1000);
}
