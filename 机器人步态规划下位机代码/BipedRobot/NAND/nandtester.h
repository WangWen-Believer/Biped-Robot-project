#ifndef __NANDTESTER_H
#define __NANDTESTER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//NAND FLASH USMART测试代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	  

u8 test_writepage(u32 pagenum,u16 colnum,u16 writebytes);
u8 test_readpage(u32 pagenum,u16 colnum,u16 readbytes);
u8 test_copypageandwrite(u32 spnum,u32 dpnum,u16 colnum,u16 writebytes);
u8 test_readspare(u32 pagenum,u16 colnum,u16 readbytes);
void test_readallblockinfo(u32 sblock);
u8 test_ftlwritesectors(u32 secx,u16 secsize,u16 seccnt);
u8 test_ftlreadsectors(u32 secx,u16 secsize,u16 seccnt);

#endif
