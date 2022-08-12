/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : hw_config.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
////////////使用设备类型定义/////////////
//不同的设备类型需要关联不同的usb_prop.c等文件
#define USE_MASS_STORAGE	1
#define USB_HID_MOUSE		0

///////////U_Storage相关定义////////////
#define BULK_MAX_PACKET_SIZE  0x00000040
#define Led_RW_ON()				LED_On(LED1)
#define Led_RW_OFF()			LED_Off(LED1)
/////////////////////////////////////////

///////////HID_MOUSE相关定义///////////
#define CURSOR_STEP     20

#define DOWN            2
#define LEFT            3
#define RIGHT           4
#define UP              5

typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef
;
/////////////////////////////////////////

///////////硬件相关通用宏定义////////////
#define USB_DISCONNECT                      GPIOD  
#define USB_DISCONNECT_PIN                  GPIO_Pin_2
#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOD
/////////////////////////////////////////

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void GPIO_AINConfig(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void MAL_Config(void);
void Joystick_Send(uint8_t Keys);
uint8_t JoyState(void);
void Get_SerialNum(u8*string_setial);

#endif  /*__HW_CONFIG_H*/

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
