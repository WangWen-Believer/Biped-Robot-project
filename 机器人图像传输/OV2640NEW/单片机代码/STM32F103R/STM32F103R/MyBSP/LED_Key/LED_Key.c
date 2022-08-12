#include "LED_Key.h"
/*--------------------------------------------------------------------------
****************************************************************************
   							LED 接口
****************************************************************************							
----------------------------------------------------------------------------*/
#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_2
#define LED1_GPIO_PORT                   GPIOA
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOA  
  
#define LED2_PIN                         GPIO_Pin_2
#define LED2_GPIO_PORT                   GPIOA
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOA  

//如果板载还有更多LED,在下面定义
#define LED3_PIN                         LED1_PIN  
#define LED3_GPIO_PORT                   LED1_GPIO_PORT
#define LED3_GPIO_CLK                    LED1_GPIO_CLK  

#define LED4_PIN                         LED1_PIN
#define LED4_GPIO_PORT                   LED1_GPIO_PORT
#define LED4_GPIO_CLK                    LED1_GPIO_CLK


//GPIO_PORT 端口
static GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, 
										LED3_GPIO_PORT, LED4_GPIO_PORT};
//GPIO_PIN 	引脚			
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, 
                                 LED3_PIN, LED4_PIN};
//GPIO_CLK 	GPIO时钟
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, 
                                 LED3_GPIO_CLK, LED4_GPIO_CLK};
								 
/*--------------------------------------------------------------------------
****************************************************************************
   							Key 按键接口
****************************************************************************							
----------------------------------------------------------------------------*/
#define BUTTONn                          8
/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn 
/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                GPIO_Pin_13
#define TAMPER_BUTTON_GPIO_PORT          GPIOC
#define TAMPER_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOC
#define TAMPER_BUTTON_EXTI_LINE          EXTI_Line13
#define TAMPER_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOC
#define TAMPER_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource13
#define TAMPER_BUTTON_EXTI_IRQn          EXTI15_10_IRQn 
/**
 * @brief Key push-button
 */
#define KEY_BUTTON_PIN                   GPIO_Pin_8
#define KEY_BUTTON_GPIO_PORT             GPIOG
#define KEY_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOG
#define KEY_BUTTON_EXTI_LINE             EXTI_Line8
#define KEY_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOG
#define KEY_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource8
#define KEY_BUTTON_EXTI_IRQn             EXTI9_5_IRQn
/**
 * @brief Joystick Right push-button
 */
#define RIGHT_BUTTON_PIN                 GPIO_Pin_13
#define RIGHT_BUTTON_GPIO_PORT           GPIOC
#define RIGHT_BUTTON_GPIO_CLK            RCC_APB2Periph_GPIOC
#define RIGHT_BUTTON_EXTI_LINE           EXTI_Line13
#define RIGHT_BUTTON_EXTI_PORT_SOURCE    GPIO_PortSourceGPIOC
#define RIGHT_BUTTON_EXTI_PIN_SOURCE     GPIO_PinSource13
#define RIGHT_BUTTON_EXTI_IRQn           EXTI15_10_IRQn
/**
 * @brief Joystick Left push-button
 */    
#define LEFT_BUTTON_PIN                  GPIO_Pin_0
#define LEFT_BUTTON_GPIO_PORT            GPIOA
#define LEFT_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOA
#define LEFT_BUTTON_EXTI_LINE            EXTI_Line0
#define LEFT_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOA
#define LEFT_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource0
#define LEFT_BUTTON_EXTI_IRQn            EXTI0_IRQn 
/**
 * @brief Joystick Up push-button
 */
#define UP_BUTTON_PIN                    GPIO_Pin_8
#define UP_BUTTON_GPIO_PORT              GPIOA
#define UP_BUTTON_GPIO_CLK               RCC_APB2Periph_GPIOA
#define UP_BUTTON_EXTI_LINE              EXTI_Line5
#define UP_BUTTON_EXTI_PORT_SOURCE       GPIO_PortSourceGPIOA
#define UP_BUTTON_EXTI_PIN_SOURCE        GPIO_PinSource8
#define UP_BUTTON_EXTI_IRQn              EXTI9_5_IRQn  
/**
 * @brief Joystick Down push-button
 */   
#define DOWN_BUTTON_PIN                  GPIO_Pin_3
#define DOWN_BUTTON_GPIO_PORT            GPIOA
#define DOWN_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOA
#define DOWN_BUTTON_EXTI_LINE            EXTI_Line3
#define DOWN_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOA
#define DOWN_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource3
#define DOWN_BUTTON_EXTI_IRQn            EXTI3_IRQn  
/**
 * @brief Joystick Sel push-button
 */  
#define SEL_BUTTON_PIN                   GPIO_Pin_7
#define SEL_BUTTON_GPIO_PORT             GPIOG
#define SEL_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOG
#define SEL_BUTTON_EXTI_LINE             EXTI_Line7
#define SEL_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOG
#define SEL_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource7
#define SEL_BUTTON_EXTI_IRQn             EXTI9_5_IRQn      

//Key_PORT	端口
static GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT, TAMPER_BUTTON_GPIO_PORT, 
                                      		KEY_BUTTON_GPIO_PORT, RIGHT_BUTTON_GPIO_PORT,
                                      		LEFT_BUTTON_GPIO_PORT, UP_BUTTON_GPIO_PORT,
                                      		DOWN_BUTTON_GPIO_PORT, SEL_BUTTON_GPIO_PORT}; 
//Key_PIN	引脚
const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN, TAMPER_BUTTON_PIN, 
                                      KEY_BUTTON_PIN, RIGHT_BUTTON_PIN,
                                      LEFT_BUTTON_PIN, UP_BUTTON_PIN,
                                      DOWN_BUTTON_PIN, SEL_BUTTON_PIN}; 
//Key_CLK	GPIO时钟
const uint32_t BUTTON_CLK[BUTTONn] = {WAKEUP_BUTTON_GPIO_CLK, TAMPER_BUTTON_GPIO_CLK,
                                      KEY_BUTTON_GPIO_CLK, RIGHT_BUTTON_GPIO_CLK,
                                      LEFT_BUTTON_GPIO_CLK, UP_BUTTON_GPIO_CLK,
                                      DOWN_BUTTON_GPIO_CLK, SEL_BUTTON_GPIO_CLK};
//Key_EXINT_LINE	中断
const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {WAKEUP_BUTTON_EXTI_LINE,
                                            TAMPER_BUTTON_EXTI_LINE, 
                                            KEY_BUTTON_EXTI_LINE,
                                            RIGHT_BUTTON_EXTI_LINE,
                                            LEFT_BUTTON_EXTI_LINE,
                                            UP_BUTTON_EXTI_LINE,
                                            DOWN_BUTTON_EXTI_LINE,
                                            SEL_BUTTON_EXTI_LINE};
//端口和引脚中断
const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PORT_SOURCE,
                                              TAMPER_BUTTON_EXTI_PORT_SOURCE, 
                                              KEY_BUTTON_EXTI_PORT_SOURCE,
                                              RIGHT_BUTTON_EXTI_PORT_SOURCE,
                                              LEFT_BUTTON_EXTI_PORT_SOURCE,
                                              UP_BUTTON_EXTI_PORT_SOURCE,
                                              DOWN_BUTTON_EXTI_PORT_SOURCE,
                                              SEL_BUTTON_EXTI_PORT_SOURCE};
				 
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PIN_SOURCE,
                                             TAMPER_BUTTON_EXTI_PIN_SOURCE, 
                                             KEY_BUTTON_EXTI_PIN_SOURCE,
                                             RIGHT_BUTTON_EXTI_PIN_SOURCE,
                                             LEFT_BUTTON_EXTI_PIN_SOURCE,
                                             UP_BUTTON_EXTI_PIN_SOURCE,
                                             DOWN_BUTTON_EXTI_PIN_SOURCE,
                                             SEL_BUTTON_EXTI_PIN_SOURCE}; 
//中断源
const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn, TAMPER_BUTTON_EXTI_IRQn, 
                                       KEY_BUTTON_EXTI_IRQn, RIGHT_BUTTON_EXTI_IRQn,
                                       LEFT_BUTTON_EXTI_IRQn, UP_BUTTON_EXTI_IRQn,
                                       DOWN_BUTTON_EXTI_IRQn, SEL_BUTTON_EXTI_IRQn};

void LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  // Enable the GPIO_LED Clock 	使能时钟
  RCC_APB2PeriphClockCmd(GPIO_CLK[Led], ENABLE);

  // Configure the GPIO_LED pin	引脚配置(推挽输出)
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void LED_On(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];     
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void LED_Off(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];    
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void LED_Toggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_WAKEUP: Wakeup Push Button
  *     @arg BUTTON_TAMPER: Tamper Push Button  
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  * @retval None
  */
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON Clock */
  //使能IO时钟;使能IO引脚复用时钟
  RCC_APB2PeriphClockCmd(BUTTON_CLK[Button] | RCC_APB2Periph_AFIO, ENABLE);

  /* Configure Button pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);


  if (Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
	//将中断IO引脚映射到中断源(EXTI Line)
    GPIO_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

    /* Configure Button EXTI line */
	//配置中断线
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//设置触发沿
    if(Button != BUTTON_WAKEUP)
    {
      	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    }
    else
    {
      	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    }
	//使能中断
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
	//配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); 
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:    
  *     @arg BUTTON_WAKEUP: Wakeup Push Button
  *     @arg BUTTON_TAMPER: Tamper Push Button  
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button    
  * @retval The Button GPIO pin value.
  */
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button)
{
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

