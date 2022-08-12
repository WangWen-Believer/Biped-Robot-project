/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL)  &&  !defined (USE_STM3210C_EVAL)
 //#define USE_STM3210B_EVAL
 //#define USE_STM3210E_EVAL
 #define USE_STM3210C_EVAL
#endif


/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define USB_DISCONNECT                      GPIOD  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_9
  
  #define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOD

  #define RCC_APB2Periph_ALLGPIO             (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE )

#elif defined (USE_STM3210E_EVAL)
  #define USB_DISCONNECT                      GPIOB  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_5
  #define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOB
                                                
  #define RCC_APB2Periph_ALLGPIO             (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE \
                                              | RCC_APB2Periph_GPIOF \
                                              | RCC_APB2Periph_GPIOG )

#elif defined (USE_STM3210C_EVAL)
  /* USB_Disconnect pin not used */
  #define USB_DISCONNECT                      0  
  #define USB_DISCONNECT_PIN                  0
  #define RCC_APB2Periph_GPIO_DISCONNECT      0

  #define GPIO_Pin_UP                         GPIO_Pin_15  /* PG.15 */
  #define GPIO_Pin_DOWN                       GPIO_Pin_3   /* PD.03 */
  #define GPIO_Pin_LEFT                       GPIO_Pin_14  /* PG.14 */
  #define GPIO_Pin_RIGHT                      GPIO_Pin_13  /* PG.13 */    

  #define RCC_APB2Periph_ALLGPIO             (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE \
                                              | RCC_APB2Periph_GPIOF \
                                              | RCC_APB2Periph_GPIOG )
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

