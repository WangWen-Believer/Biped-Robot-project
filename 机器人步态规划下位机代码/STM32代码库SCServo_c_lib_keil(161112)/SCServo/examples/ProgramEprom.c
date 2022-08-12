#include "stm32f10x.h"
#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

void setup()
{
  Uart_Init(1000000);
  writeByte(0xfe, P_LOCK, 0);//打开EPROM保存功能
  writeByte(0xfe, P_ID, 0);//ID
  delay(50);
  writeWord(0xfe, P_MIN_ANGLE_LIMIT_L, 0);
  delay(50);
  writeWord(0xfe, P_MAX_ANGLE_LIMIT_L, 1023);
  delay(50);
  writeWord(0xfe, P_MAX_TORQUE_L, 1023);
  delay(50);
  writeWord(0xfe, P_PUNCH_L, 50);
  delay(50);
  writeByte(0xfe, P_CW_DEAD, 2);
  delay(50);
  writeByte(0xfe, P_CCW_DEAD, 2);
  delay(50);
  writeByte(0xfe, P_COMPLIANCE_P, 15);
  delay(50);
  writeByte(0xfe, P_BAUD_RATE, B_1M);//BaundRate=1Mbit/s
  delay(50);
  writeByte(0xfe, P_LOCK, 1);//关闭EPROM保存功能�
}

void loop()
{

}
