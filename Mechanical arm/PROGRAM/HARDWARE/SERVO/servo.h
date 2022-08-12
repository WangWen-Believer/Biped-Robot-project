#ifndef _USART_H
#define _USART_H
#endif
#include "sys.h"
#include "stdio.h"
#include "usart.h"
    //                        位置  时间  速度                 
extern u8 Servo_State[11][7];  
/******Instruction*******/
#define PING          0x01
#define READ_DATA     0x02
#define WRITE_DATA    0x03
#define REGWRITE_DATA 0x04
#define ACTION        0x05
#define SYCNWRITE_DATA 0X83
#define REST          0X06
/*********Adress*********/
#define ID_ADRESS     0X05
#define TORQUE_SWITCH 0x28
#define Position_Adress 0x2a
#define Lock_Adress   0x30



extern UART_HandleTypeDef UART2_Handler; //UART句柄


void ReadServo_state(u8 ID,u8 Instruction);
int  EnableTorque(u8 ID);
void Write_Buff(u8 ID,u8 Instruction,u8 Adress,u8 Parameter);
void Split_Number(u8 *DataH, u8* DataL, u16 Data);
void Set_Servo_ID(u8 new_servo_id);
void Servo_Lock(u8 enable);
u16  Check_Sum(u8 *front_state,u8 *middle_stata,u8 servo_number);
void Data_Init(u8 servo_number);
void ReadServo_Position(u8 ID); 
void Write_Position(u8 id,u16 Position,u16 Times,u16 Speed);
