/*
 * SCServo.cpp
 * 硬件通信接口
 * 日期: 2016.11.11
 * 作者: 谭雄乐
 */

#include "stm32f10x.h"
#include "SCServo.h"
#include "uart.h"
#include "wiring.h"

uint32_t IOTimeOut = 2;//输入输出超时

//UART 接收数据接口
int readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	uint32_t t_begin = millis();
	uint32_t t_user;
	while(1){
		ComData = Uart1_Read();
		if(ComData!=-1){
			if(nDat){
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = millis();
		}
		if(Size>=nLen){
			break;
		}
		t_user = millis() - t_begin;
		if(t_user>IOTimeOut){
			break;
		}
	}
	return Size;
}

//UART 发送数据接口
int writeSCS(unsigned char *nDat, int nLen)
{
	Uart1_DmaSend(nDat, nLen);
	return 0;
}

//接收缓冲区刷新
void flushSCS()
{
	Uart1_Flush();
}
