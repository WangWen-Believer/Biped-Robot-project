#ifndef NVIC_EXIT_H_H_
#define NVIC_EXIT_H_H_

#include "stm32f10x.h"
#include "Rename_Pin.h"

#define SET_PORT_L(PORT, Pin)	(PORT)->BRR = (Pin)
#define SET_PORT_H(PORT, Pin)	(PORT)->BSRR = (Pin)

//通用引脚初始化函数
void GpioInit(GPIO_TypeDef* gpio_port, 
			   u16 gpio_pin,
			   GPIOMode_TypeDef gpio_pin_mode,
			   GPIOSpeed_TypeDef gpio_pin_speed);

//设置NVIC分组和Table存放位置
void NVIC_Config(uint32_t NVIC_PriorityGroup);
//外中断初始化
void Exit_Init(GPIO_TypeDef* gpio_port,
		 	   u16 gpio_pin,
			   GPIOMode_TypeDef gpio_pin_mode,
			   EXTITrigger_TypeDef exit_type,
			   u8 pre_pri,
			   u8 sub_pri);

#endif
