/*
 * SCSProtocol.h
 * SCS串行舵机协议程序
 * 日期: 2016.11.11
 * 作者: 谭雄乐
 */

#ifndef _SCSPROTOCOL_H
#define _SCSPROTOCOL_H

#include <stdint.h>

extern int genWrite(uint8_t ID, uint8_t MemAddr, uint8_t *nDat, uint8_t nLen);//普通写指令
extern int regWrite(uint8_t ID, uint8_t MemAddr, uint8_t *nDat, uint8_t nLen);//异步写指令
extern void snycWrite(uint8_t ID[], uint8_t IDN, uint8_t MemAddr, uint8_t *nDat, uint8_t nLen);//同步写指令
extern int writeByte(uint8_t ID, uint8_t MemAddr, uint8_t bDat);//写1个字节
extern int writeWord(uint8_t ID, uint8_t MemAddr, uint16_t wDat);//写2个字节
extern int EnableTorque(uint8_t ID, uint8_t Enable);//扭力控制指令
extern int WritePos(uint8_t ID, uint16_t Position, uint16_t Time, uint16_t Speed);//普通写位置指令
extern int RegWritePos(uint8_t ID, uint16_t Position, uint16_t Time, uint16_t Speed);//异步写位置指令
extern void RegWriteAction(void);//执行异步写指令
extern void SyncWritePos(uint8_t ID[], uint8_t IDN, uint16_t Position, uint16_t Time, uint16_t Speed);//同步写位置指令
extern int WriteSpe(uint8_t ID, int16_t Speed);//多圈控制指令
extern int Read(uint8_t ID, uint8_t MemAddr, uint8_t *nData, uint8_t nLen);//读指令
extern int readByte(uint8_t ID, uint8_t MemAddr);//读1个字节
extern int readWord(uint8_t ID, uint8_t MemAddr);//读2个字节
extern int ReadPos(uint8_t ID);//读位置
extern int ReadVoltage(uint8_t ID);//读电压
extern int ReadTemper(uint8_t ID);//记温度
extern int Ping(uint8_t ID);//Ping指令
extern int wheelMode(uint8_t ID);//多圈轮子模式
extern int joinMode(uint8_t ID, unsigned short minAngle, unsigned short maxAngle);//普通伺服模式
extern int Reset(uint8_t ID);//复位舵机参数为默认值

extern int Ack(uint8_t ID);//应答

//硬件接口函数
extern int writeSCS(uint8_t *nDat, int nLen);
extern int readSCS(uint8_t *nDat, int nLen);
extern void flushSCS(void);

	#define		B_1M			0
	#define		B_0_5M		1
	#define		B_250K		2
	#define		B_128K		3
	#define		B_115200	4
	#define		B_76800		5
	#define		B_57600		6
	#define		B_38400		7

	//register Address
	#define P_VERSION_L 3
	#define P_VERSION_H 4
	#define P_ID 5
	#define P_BAUD_RATE 6
	#define P_RETURN_DELAY_TIME 7
	#define P_RETURN_LEVEL 8
	#define P_MIN_ANGLE_LIMIT_L 9
	#define P_MIN_ANGLE_LIMIT_H 10
	#define P_MAX_ANGLE_LIMIT_L 11
	#define P_MAX_ANGLE_LIMIT_H 12
	#define P_LIMIT_TEMPERATURE 13
	#define P_MAX_LIMIT_VOLTAGE 14
	#define P_MIN_LIMIT_VOLTAGE 15
	#define P_MAX_TORQUE_L 16
	#define P_MAX_TORQUE_H 17
	#define P_ALARM_LED 19
	#define P_ALARM_SHUTDOWN 20
	#define P_COMPLIANCE_P 21
	#define P_PUNCH_L 24
	#define P_PUNCH_H 25
	#define P_CW_DEAD 26
	#define P_CCW_DEAD 27

	#define P_TORQUE_ENABLE 40
	#define P_LED 41
	#define P_GOAL_POSITION_L 42
	#define P_GOAL_POSITION_H 43
	#define P_GOAL_TIME_L 44
	#define P_GOAL_TIME_H 45
	#define P_GOAL_SPEED_L 46
	#define P_GOAL_SPEED_H 47
	#define P_LOCK 48

	#define P_PRESENT_POSITION_L 56
	#define P_PRESENT_POSITION_H 57
	#define P_PRESENT_SPEED_L 58
	#define P_PRESENT_SPEED_H 59
	#define P_PRESENT_LOAD_L 60
	#define P_PRESENT_LOAD_H 61
	#define P_PRESENT_VOLTAGE 62
	#define P_PRESENT_TEMPERATURE 63
	#define P_REGISTERED_INSTRUCTION 64
	#define P_MOVING 66

	//Instruction:
	#define INST_PING 0x01
	#define INST_READ 0x02
	#define INST_WRITE 0x03
	#define INST_REG_WRITE 0x04
	#define INST_ACTION 0x05
	#define INST_RESET 0x06
	#define INST_SYNC_WRITE 0x83

#endif
