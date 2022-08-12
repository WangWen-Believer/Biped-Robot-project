#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F746开发板
//DMA驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/12/28
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

extern DMA_HandleTypeDef  UART2TxDMA_Handler;      //DMA句柄
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx);
void Watit_Sendcomplete(void);
 
#endif
