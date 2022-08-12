/***************************** (C) COPYRIGHT  **********************************
* File Name          : SD_Driver.h
* Author             : zidong404(zxb)
* Version            : V1.2
* Date               : 6/12/2010
* Description        : This file contains all the interface functions prototypes 
*                      for the SD_Driver.c.
*					 ：本文件包含了SD卡和MMC驱动对外接口函数声明,其中
*					 ：SD_TimeoutHandler()函数为用户定时器中断中调用，其他函数为
*					 ：ELM FATFS提供操作SD和MMC的接口
********************************************************************************/
#ifndef _SD_DRIVER_H_
#define _SD_DRIVER_H_

#include "stm32f10x.h"

#define AVR_8BIT_MCU_EN		0

#if AVR_8BIT_MCU_EN		> 0
//SD卡SS引脚配置					
#define MMC_SD_CS_DDR  DDRD
#define MMC_SD_CS_PORT PORTD
#define MMC_SD_CS_BIT  PD5

//SD卡SPI_引脚配置					
#define MMC_SD_SCK_DDR  SPI_DDR
#define MMC_SD_SCK_PORT SPI_PORT
#define MMC_SD_SCK_BIT  SPI_SCK

#define MMC_SD_MOSI_DDR  SPI_DDR
#define MMC_SD_MOSI_PORT SPI_PORT
#define MMC_SD_MOSI_BIT  SPI_MOSI

#define MMC_SD_MISO_DDR  SPI_DDR
#define MMC_SD_MISO_PORT SPI_PORT
#define MMC_SD_MISO_BIT  SPI_MISO

#endif

//////////////////////////////// Public Functions////////////////////////////////////
/* 包含diskio.h */
#include "diskio.h"

/* 以下声明函数为ELM FATFS的交互接口函数 */
DSTATUS SD_Status(void);

DRESULT SD_Write(
	const BYTE *buff,		/* Pointer to the data to be written */
	DWORD sector,			/* Start sector number (LBA) */
	BYTE count				/* Sector count (1..255) */
);
DRESULT SD_Read(
	BYTE *buff,				/* Pointer to the data buffer to store read data */
	DWORD sector,			/* Start sector number (LBA) */
	BYTE count				/* Sector count (1..255) */
);

DSTATUS SD_Init(void);

DRESULT SD_Ioctl(
	BYTE ctrl,				/* Control code */
	void *buff				/* Buffer to send/receive data block */
);

/********************************************************************
* 以下声明函数为超时处理接口函数，用户需要在1KHZ定时中断中调用 		*
* 如果该函数没有调用，在调用SD_Driver提供的接口函数时如卡出现硬件	*
* 故障，将可能导致软件出现不可预料的结果从而函数不能返回			*
********************************************************************/
void SD_TimeoutHandler(void);

/* 以下声明函数为兼容旧版本SD卡驱动而声明,ELM FATFS不调用 */ 
unsigned long SD_GetCapacity(void); 													//获取容量
DRESULT SD_ReadSingleBlock(unsigned long sector, unsigned char *p_buff);             	//读一个sector
DRESULT SD_WriteSingleBlock(unsigned long sector, unsigned char *p_buff);      			//写一个sector
DRESULT SD_ReadMultiBlock(unsigned long sector, unsigned char *p_buff, unsigned char count);    //读多个sector
DRESULT SD_WriteMultiBlock(unsigned long sector, const unsigned char *p_buff, unsigned char count);//写多个sector

//////////////////
void SD_WriteSectorEnd(BYTE count);
DWORD SD_WriteSectorStart(DWORD sector, BYTE count);
void SD_WriteSector(const BYTE *buff, BYTE count);
//////////////////
//////////////////
DWORD SD_ReadSectorStart(DWORD sector, BYTE count);
void SD_ReadSector(BYTE *buff);
void SD_ReadSectorEnd(BYTE count);
/////////////////
#endif
