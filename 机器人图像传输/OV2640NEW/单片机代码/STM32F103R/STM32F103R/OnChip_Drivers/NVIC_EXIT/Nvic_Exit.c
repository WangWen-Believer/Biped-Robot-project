#include "Nvic_Exit.h"

#define PORTA	0
#define PORTB	1
#define PORTC	2
#define PORTD	3
#define PORTE	4
#define PORTF	5
#define PORTG	6

#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define PIN8	8
#define PIN9	9
#define PIN10	10
#define PIN11	11
#define PIN12	12
#define PIN13	13
#define PIN14	14
#define PIN15	15


GPIO_TypeDef* GPIO_PORT[] = 
{
	GPIOA, GPIOB, GPIOC, 
	GPIOD, GPIOE, GPIOF, GPIOG,
};
const u16 GPIO_Pin[]= 
{
	GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, 
	GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, 
	GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10,GPIO_Pin_11,
	GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15,
};
const u32 GPIO_PortClk[] = 
{
	RCC_APB2Periph_GPIOA,
	RCC_APB2Periph_GPIOB,
	RCC_APB2Periph_GPIOC,
	RCC_APB2Periph_GPIOD,
	RCC_APB2Periph_GPIOE,
	RCC_APB2Periph_GPIOF,
	RCC_APB2Periph_GPIOG,
};
const u8 GPIO_PortSuorce[] = 
{
	GPIO_PortSourceGPIOA,
	GPIO_PortSourceGPIOB,
	GPIO_PortSourceGPIOC,
	GPIO_PortSourceGPIOD,
	GPIO_PortSourceGPIOE,
	GPIO_PortSourceGPIOF,
	GPIO_PortSourceGPIOG,
};
const u8 GPIO_PinSource[] = 
{
	GPIO_PinSource0, GPIO_PinSource1, GPIO_PinSource2, GPIO_PinSource3,
	GPIO_PinSource4, GPIO_PinSource5, GPIO_PinSource6, GPIO_PinSource7,
	GPIO_PinSource8, GPIO_PinSource9, GPIO_PinSource10,GPIO_PinSource11,
	GPIO_PinSource12,GPIO_PinSource13,GPIO_PinSource14,GPIO_PinSource15,
};
const u32 EXINT_Line[] = 
{
	EXTI_Line0, EXTI_Line1, EXTI_Line2, EXTI_Line3,
	EXTI_Line4, EXTI_Line5, EXTI_Line6, EXTI_Line7, 
	EXTI_Line8, EXTI_Line9, EXTI_Line10,EXTI_Line11,
	EXTI_Line12,EXTI_Line13,EXTI_Line14,EXTI_Line15,
};
const IRQn_Type Exit_IRQn[] =
{
	EXTI0_IRQn,  		// EXTI Line0 Interrupt                                
	EXTI1_IRQn,         // EXTI Line1 Interrupt
	EXTI2_IRQn,         // EXTI Line2 Interrupt         
	EXTI3_IRQn,         // EXTI Line3 Interrupt     
	EXTI4_IRQn,         // EXTI Line4 Interrupt   
	EXTI9_5_IRQn,		// 5
	EXTI9_5_IRQn,		// 6
	EXTI9_5_IRQn,		// 7
	EXTI9_5_IRQn,		// 8
	EXTI9_5_IRQn,       // External Line[9:5] Interrupts  
	EXTI15_10_IRQn,		// 10
	EXTI15_10_IRQn,		// 11
	EXTI15_10_IRQn,		// 12 
	EXTI15_10_IRQn,		// 13
	EXTI15_10_IRQn,		// 14
	EXTI15_10_IRQn,     // External Line[15:10] Interrupts
};

//系统中断管理
void NVIC_Config(uint32_t NVIC_PriorityGroup)
{ 
	//设置优先级分组：先占优先级0位,从优先级4位,芯片复位后默认为分组0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
	//设置向量表的位置和偏移,芯片复位后向量表默认在Flah中
#ifdef  VECT_TAB_RAM  
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 	//向量表位于RAM
#else  /* VECT_TAB_FLASH  */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   //向量表位于FLASH
#endif
}

static u8 GetGpioPortNumber(GPIO_TypeDef* gpio_port)
{	 
	u8 i = 0;
	//参数检查
	assert_param(IS_GPIO_PIN(gpio_port)); 
	for(i = 0; i < 6; i ++)
	{											
		if(gpio_port == GPIO_PORT[i])
		{
			return i;	
		}								
	}
	return 0;									//不会执行到这里
}
static u8 GetGpioPinNumber(u16 gpio_pin)
{	 
	u8 i = 0;
	//参数检查
	assert_param(IS_GPIO_ALL_PERIPH(gpio_pin));
	for(i = 0; i < 16; i ++)
	{											
		if(gpio_pin == GPIO_Pin[i])
		{
			return i;	
		}								
	}
	return 0;									//不会执行到这里
}
/*************************************************
gpio_pin_mode:
	GPIO_Mode_AIN 				模拟输入
	GPIO_Mode_IN_FLOATING 		浮空输入
	GPIO_Mode_IPD 				下拉输入
	GPIO_Mode_IPU 				上拉输入
	
	GPIO_Mode_Out_OD 			开漏输出
	GPIO_Mode_Out_PP 			推挽输出
	GPIO_Mode_AF_OD				复用开漏输出
	GPIO_Mode_AF_PP 			复用推挽输出
gpio_pin_speed：
	0							输入模式
	GPIO_Speed_10MHz
  	GPIO_Speed_2MHz, 
  	GPIO_Speed_50MHz
调用形式:
GpioInit(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
*************************************************/
void GpioInit(GPIO_TypeDef* gpio_port, 
			   u16 gpio_pin,
			   GPIOMode_TypeDef gpio_pin_mode,
			   GPIOSpeed_TypeDef gpio_pin_speed)
{
	u8 gpio_port_num = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	gpio_port_num = GetGpioPortNumber(gpio_port);
	
	RCC_APB2PeriphClockCmd(GPIO_PortClk[gpio_port_num], ENABLE);//使能时钟

	GPIO_InitStructure.GPIO_Mode = gpio_pin_mode;
	GPIO_InitStructure.GPIO_Pin = gpio_pin;
	if(gpio_pin_speed)
	{	//在输入模式下,该域不起作用
		GPIO_InitStructure.GPIO_Speed = gpio_pin_speed;
	}
	GPIO_Init(gpio_port, &GPIO_InitStructure);	//初始化端口
}
/*************************************************
gpio_pin_mode:
	GPIO_Mode_IN_FLOATING 		浮空输入
	GPIO_Mode_IPD 				下拉输入
	GPIO_Mode_IPU 				上拉输入
exit_type:
	EXTI_Trigger_Rising 		上升沿
	EXTI_Trigger_Falling		下降沿
	EXTI_Trigger_Rising_Falling  跳变沿(上升和下降)
调用形式:
Exit_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_IPU, EXTI_Trigger_Falling, 2, 3);
*************************************************/

void Exit_Init(GPIO_TypeDef* gpio_port,
		 	   u16 gpio_pin,
			   GPIOMode_TypeDef gpio_pin_mode,
			   EXTITrigger_TypeDef exit_type,
			   u8 pre_pri,
			   u8 sub_pri)
{

	u8 gpio_port_num = 0;
	u8 gpio_pin_num = 0;
  	EXTI_InitTypeDef EXTI_InitStructure;
  	NVIC_InitTypeDef NVIC_InitStructure;

	gpio_port_num = GetGpioPortNumber(gpio_port);
	gpio_pin_num = GetGpioPinNumber(gpio_pin);
	//引脚初始化
	GpioInit(gpio_port, gpio_pin, gpio_pin_mode, (GPIOSpeed_TypeDef)0);
  	//使能辅助时钟AFIO
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	///////////////////////////////////////
	//将中断IO引脚映射到中断源(EXTI Line)
    GPIO_EXTILineConfig(GPIO_PortSuorce[gpio_port_num], GPIO_PinSource[gpio_pin_num]);
	//配置中断线
    EXTI_InitStructure.EXTI_Line = EXINT_Line[gpio_pin_num];
	//配置为外中断
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//设置触发沿
	EXTI_InitStructure.EXTI_Trigger = exit_type; 
	//使能中断
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	///////////////////////////////////////
	//配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = Exit_IRQn[gpio_pin_num];	//引脚对应的中断IRQn
	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre_pri;	//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_pri;		//响应优先级
	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能IRQn
	
    NVIC_Init(&NVIC_InitStructure); 
}

