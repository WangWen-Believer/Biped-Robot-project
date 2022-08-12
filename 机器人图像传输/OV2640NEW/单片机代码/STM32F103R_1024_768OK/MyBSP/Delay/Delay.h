#ifndef DELAY_H_H_
#define	DELAY_H_H_
#include "stm32f10x.h"

void Delay_Init(u8 SYSCLK);
void Delay_nMS(u16 nms);
void Delay_nUS(u32 nus);

#endif





























