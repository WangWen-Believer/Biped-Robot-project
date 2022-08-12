/*
 * SCSProtocol.c
 * SCS串行舵机协议程序
 * 日期: 2016.11.11
 * 作者: 谭雄乐
 */

#include <stddef.h>
#include "SCSProtocol.h"

typedef		char			s8;
typedef		unsigned char	u8;	
typedef		unsigned short	u16;	
typedef		short			s16;
typedef		unsigned long	u32;	
typedef		long			s32;

static u8	Level =1;//舵机返回等级
static u8	End = 1;//处理器大小端结构

//1个16位数拆分为2个8位数
//DataL为低位，DataH为高位
void Host2SCS(u8 *DataL, u8* DataH, int Data)
{
	if(End){
		*DataL = (Data>>8);
		*DataH = (Data&0xff);
	}else{
		*DataH = (Data>>8);
		*DataL = (Data&0xff);
	}
}

//2个8位数组合为1个16位数
//DataL为低位，DataH为高位
int SCS2Host(u8 DataL, u8 DataH)
{
	int Data;
	if(End){
		Data = DataL;
		Data<<=8;
		Data |= DataH;
	}else{
		Data = DataH;
		Data<<=8;
		Data |= DataL;
	}
	return Data;
}

void writeBuf(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen, u8 Fun)
{
	u8 i;
	u8 msgLen = 2;
	u8 bBuf[6];
	u8 CheckSum = 0;
	bBuf[0] = 0xff;
	bBuf[1] = 0xff;
	bBuf[2] = ID;
	bBuf[4] = Fun;
	if(nDat){
		msgLen += nLen + 1;
		bBuf[3] = msgLen;
		bBuf[5] = MemAddr;
		writeSCS(bBuf, 6);
		
	}else{
		bBuf[3] = msgLen;
		writeSCS(bBuf, 5);
	}
	CheckSum = ID + msgLen + Fun + MemAddr;
	if(nDat){
		for(i=0; i<nLen; i++){
			CheckSum += nDat[i];
		}
		writeSCS(nDat, nLen);
	}
	CheckSum = ~CheckSum;
	writeSCS(&CheckSum, 1);
}

//普通写指令
//舵机ID，MemAddr内存表地址，写入数据，写入长度
int genWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen)
{
	flushSCS();
	writeBuf(ID, MemAddr, nDat, nLen, INST_WRITE);
	return Ack(ID);
}

//异步写指令
//舵机ID，MemAddr内存表地址，写入数据，写入长度
int regWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen)
{
	flushSCS();
	writeBuf(ID, MemAddr, nDat, nLen, INST_REG_WRITE);
	return Ack(ID);
}

//同步写指令
//舵机ID[]数组，IDN数组长度，MemAddr内存表地址，写入数据，写入长度
void snycWrite(u8 ID[], u8 IDN, u8 MemAddr, u8 *nDat, u8 nLen)
{
	u8 i, j;
	u8 mesLen = ((nLen+1)*IDN+4);
	u8 checkSum = 0;
	u8 bBuf[7];
	bBuf[0] = 0xff;
	bBuf[1] = 0xff;
	bBuf[2] = 0xfe;
	bBuf[3] = mesLen;
	bBuf[4] = INST_SYNC_WRITE;
	bBuf[5] = MemAddr;
	bBuf[6] = nLen;
	writeSCS(bBuf, 7);

	checkSum = 0xfe + mesLen + INST_SYNC_WRITE + MemAddr + nLen;
	for(i=0; i<IDN; i++){
		writeSCS(ID+i, 1);
		writeSCS(nDat, nLen);
		checkSum += ID[i];
		for(j=0; j<nLen; j++){
			checkSum += nDat[j];
		}
	}
	checkSum = ~checkSum;
	writeSCS(&checkSum, 1);
}

int writeByte(u8 ID, u8 MemAddr, u8 bDat)
{
	flushSCS();
	writeBuf(ID, MemAddr, &bDat, 1, INST_WRITE);
	return Ack(ID);
}

int writeWord(u8 ID, u8 MemAddr, u16 wDat)
{
	u8 buf[2];
	flushSCS();
	Host2SCS(buf+0, buf+1, wDat);
	writeBuf(ID, MemAddr, buf, 2, INST_WRITE);
	return Ack(ID);
}

int EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, P_TORQUE_ENABLE, Enable);
}

int writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun)
{
	u8 buf[6];
	flushSCS();
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	writeBuf(ID, P_GOAL_POSITION_L, buf, 6, Fun);
	return Ack(ID);
}

//写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int WritePos(u8 ID, u16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_WRITE);
}

//异步写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_REG_WRITE);
}

void RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//写位置指令
//舵机ID[]数组，IDN数组长度，Position位置，执行时间Time，执行速度Speed
void SyncWritePos(u8 ID[], u8 IDN, u16 Position, u16 Time, u16 Speed)
{
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	snycWrite(ID, IDN, P_GOAL_POSITION_L, buf, 6);
}

//读指令
//舵机ID，MemAddr内存表地址，返回数据nData，数据长度nLen
int Read(u8 ID, u8 MemAddr, u8 *nData, u8 nLen)
{
	int Size;
	u8 bBuf[5];
	flushSCS();
	writeBuf(ID, MemAddr, &nLen, 1, INST_READ);
	if(readSCS(bBuf, 5)!=5){
		return 0;
	}
	Size = readSCS(nData, nLen);
	if(readSCS(bBuf, 1)){
		return Size;
	}
	return 0;
}

//读1字节，超时返回-1
int readByte(u8 ID, u8 MemAddr)
{
	u8 bDat;
	int Size = Read(ID, MemAddr, &bDat, 1);
	if(Size!=1){
		return -1;
	}else{
		return bDat;
	}
}

//读2字节，超时返回-1
int readWord(u8 ID, u8 MemAddr)
{	
	u8 nDat[2];
	int Size;
	u16 wDat;
	Size = Read(ID, MemAddr, nDat, 2);
	if(Size!=2)
		return -1;
	wDat = SCS2Host(nDat[0], nDat[1]);
	return wDat;
}

//读位置，超时返回-1
int ReadPos(u8 ID)
{
	return readWord(ID, P_PRESENT_POSITION_L);
}

//多圈控制指令
int WriteSpe(u8 ID, s16 Speed)
{
	if(Speed<0){
		Speed = -Speed;
		Speed |= (1<<10);
	}
	return writeWord(ID, P_GOAL_TIME_L, Speed);
}

//读电压，超时返回-1
int ReadVoltage(u8 ID)
{	
	return readByte(ID, P_PRESENT_VOLTAGE);
}

//读温度，超时返回-1
int ReadTemper(u8 ID)
{	
	return readByte(ID, P_PRESENT_TEMPERATURE);
}

//Ping指令，返回舵机ID，超时返回-1
int Ping(u8 ID)
{
	int Size;
	u8 bBuf[6];
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_PING);
	Size = readSCS(bBuf, 6);
	if(Size==6){
		return bBuf[2];
	}else{
		return -1;
	}
}

int wheelMode(u8 ID)
{
	u8 bBuf[4];
	bBuf[0] = 0;
	bBuf[1] = 0;
	bBuf[2] = 0;
	bBuf[3] = 0;
	return genWrite(ID, P_MIN_ANGLE_LIMIT_L, bBuf, 4);
}

int joinMode(u8 ID, u16 minAngle, u16 maxAngle)
{
	u8 bBuf[4];
	Host2SCS(bBuf, bBuf+1, minAngle);
	Host2SCS(bBuf+2, bBuf+3, maxAngle);
	return genWrite(ID, P_MIN_ANGLE_LIMIT_L, bBuf, 4);
}

//复位舵机参数为默认值
int Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}

int	Ack(u8 ID)
{
	if(ID != 0xfe && Level){
		u8 buf[6];
		u8 Size = readSCS(buf, 6);
		if(Size!=6){
			return 0;
		}
	}
	return 1;
}
