#ifndef LED_KEY_H_H_
#define LED_KEY_H_H_

#include "stm32f10x.h"

typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2,
  BUTTON_RIGHT = 3,
  BUTTON_LEFT = 4,
  BUTTON_UP = 5,
  BUTTON_DOWN = 6,
  BUTTON_SEL = 7
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

/*--------------------------------------------------------------------------
****************************************************************************
   							对外函数声明区
****************************************************************************							
----------------------------------------------------------------------------*/
void LED_Init(Led_TypeDef Led);
void LED_On(Led_TypeDef Led);
void LED_Off(Led_TypeDef Led);
void LED_Toggle(Led_TypeDef Led);

void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
#endif
