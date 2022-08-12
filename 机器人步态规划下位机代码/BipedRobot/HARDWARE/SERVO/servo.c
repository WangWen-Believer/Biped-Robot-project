#include "servo.h"
#include "usart.h"
#include "dma.h"
/******servo_stata*****/
//                        位置      时间      速度
/*           当前 ID   高位 低位 高位 低位 高位  低位  */
uint8_t Servo_State[20][5]={{1,0X02,10,0X00,50},
                           {2,0X02,23,0X00,50},
													 {3,0X02,237,0X00,50},
												 	 {4,0X01,249,0X00,50},
													 {5,0X01,218,0X00,50},
													 {6,0X01,232,0X00,50},
													 {7,0X01,198,0X00,50},
													 {8,0X01,11,0X00,50},
													 {9,0X02,41,0X00,50},
													 {10,0X01,205,0X00,50},
													 {11,0X01,210,0X00,50},
													 {12,0X02,41,0X00,50},
													 {13,0X00,106,0X00,50},
													 {14,0X03,17,0X00,50},
													 {15,0X01,244,0X00,50},
													 {16,0X03,209,0X00,50},
													 {17,0X01,224,0X00,50},
                           {18,0X01,208,0X00,50},
													 {19,0X01,206,0X00,50},
													 {20,0X01,7  ,0X00,50}};//各个舵机的状态信息

void ReadServo_Position(u8 ID)  //读取舵机位置   
{
	Write_Buff(ID,READ_DATA,Position_Adress,0x02);
}
int EnableTorque(u8 ID)
{
  Write_Buff(ID,WRITE_DATA,TORQUE_SWITCH,ENABLE);  //id address parameter 
	return 0;
}

void Write_Buff(u8 id,u8 Instruction,u8 Adress,u8 Parameter)  //仅限有两个参数
{
	u16 Check_Sum=0;
	u8 send_buff[8]={0};
	u8 len=4;
	send_buff[0] = 0xff;
  send_buff[1] = 0xff;
  send_buff[2] =	id;
	send_buff[3] = len;
	send_buff[4] = Instruction;
	send_buff[5] = Adress;
	send_buff[6] = Parameter;
	Check_Sum=send_buff[2]+send_buff[3]+send_buff[4]+send_buff[5]+send_buff[6];
	if(Check_Sum>255)
	Check_Sum&=0xFF;
	Check_Sum |= 0xFF00;
	Check_Sum=~Check_Sum;
	send_buff[7] = Check_Sum;
	HAL_UART_Transmit_DMA(&UART2_Handler,send_buff,8);//开启DMA传输
	Watit_Sendcomplete();
}
void SYNC_Write_Buff(u8 *position_satae,u8 servo_number)
{
	u8 state_length=(4+1)*servo_number+4;   // (每个舵机发送的数据长度+1)*舵机个数+4
	u8 middle_state_number;                 //要发送4个数据  位置 时间 
	u8 check_sum=0;
	u8 send_buff[7]={0xff,0xff,0xfe,0,SYCNWRITE_DATA,Position_Adress,0x04};
	send_buff[3]=state_length;
	
	HAL_UART_Transmit_DMA(&UART2_Handler,send_buff,7);//发送前半部分

	Watit_Sendcomplete();	
	
	middle_state_number=5*servo_number;//  获取中间数据量
	HAL_UART_Transmit_DMA(&UART2_Handler,position_satae,middle_state_number);//发送中间部分	
	Watit_Sendcomplete();
  check_sum=Check_Sum(send_buff,position_satae,servo_number);
	HAL_UART_Transmit_DMA(&UART2_Handler,&check_sum,1);//发送中间部分
	Watit_Sendcomplete();
}
u16 Check_Sum(u8 *front_state,u8 *middle_stata,u8 servo_number)
{
	u16 Check_Sum_state=0;
	u8  i,j;
	u8 *Middle_Stata;
	Middle_Stata=middle_stata;
//	j=servo_number*5;
	for(i=2;i<7;i++)
	{
		Check_Sum_state+=front_state[i];
	}
 	for(i=0;i<servo_number;i++)
	   for(j=0;j<5;j++)
	   {
	      Check_Sum_state+=*Middle_Stata++;
	   }
  if(Check_Sum_state>255)
	    Check_Sum_state&=0xFF;
	Check_Sum_state |= 0xFF00;
	Check_Sum_state=~Check_Sum_state; 
	return (u8)Check_Sum_state;
}



void Write_Position(u8 id,u16 Position,u16 Times,u16 Speed)
{
	u16 Check_Sum=0;
	u8 len=9;
	u8 send_buff[13]={0};
	send_buff[0] = 0xff;
  send_buff[1] = 0xff;
  send_buff[2] =	id;
	send_buff[3] = len;
	send_buff[4] = WRITE_DATA;
	send_buff[5] = Position_Adress;
	Split_Number(send_buff+6, send_buff+7, Position);
	Split_Number(send_buff+8, send_buff+9, Times);
	Split_Number(send_buff+10,send_buff+11,Speed);
	Check_Sum=send_buff[2]+send_buff[3]+send_buff[4]+send_buff[5]+send_buff[6]+send_buff[7]+send_buff[8]+send_buff[9]+send_buff[10]+send_buff[11];
	if(Check_Sum>255)
	    Check_Sum&=0xFF;
	Check_Sum |= 0xFF00;
	Check_Sum=~Check_Sum;
	send_buff[12] = Check_Sum;
	HAL_UART_Transmit_DMA(&UART2_Handler,send_buff,13);//开启DMA传输
  Watit_Sendcomplete();	
}
void Set_Servo_ID(u8 new_servo_id)
{
	 Write_Buff(0xfe,WRITE_DATA,ID_ADRESS,new_servo_id);
}
void Servo_Lock(u8 enable)
{
	 Write_Buff(0xfe,WRITE_DATA,Lock_Adress,enable);
}
//1个16位数拆分为2个8位数
//DataL为低位，DataH为高位
void Split_Number(u8 *DataH, u8* DataL, u16 Data)
{
		*DataH = (Data>>8);
		*DataL = (Data&0xff);
}
u16 Together_Number(u8 *DataH, u8* DataL)
{
	u16 Data_High,Data_Low,Data;
	Data_High=(*DataH)<<8;
	Data_Low=*DataL;
	Data=Data_High+Data_Low;
	return Data;
}

