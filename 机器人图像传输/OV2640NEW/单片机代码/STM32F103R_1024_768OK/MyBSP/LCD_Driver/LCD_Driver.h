# ifndef LCD_DRIVER_H_H_
# define LCD_DRIVER_H_H_

#include "OnChip_Driver_Inc.h"

////////////////////////////////////////
#define R61514_EN		0
#define LCD_8_BIT_EN	1 
////////////////////////////////////////
////////////////////////////////////////
//i80控制端口宏定义						
//视硬件连接进行更改										    
#define LCD_CS_BIT		PC8		//片选端口 
#define LCD_CS_PORT		GPIOC
 
#define LCD_RS_BIT		PC9		//数据/命令 
#define LCD_RS_PORT		GPIOC

#define LCD_WR_BIT		PC10	//写数据
#define LCD_WR_PORT		GPIOC

#define LCD_RD_BIT		PC11	//读数据
#define LCD_RD_PORT		GPIOC

#define LCD_REST_BIT	PC12	//LCD 硬件复位
#define LCD_REST_PORT	GPIOC

#define LCD_LED_BIT		PC13	//LCD背光 
#define LCD_LED_PORT	GPIOC


# define LCD_CS_DDR		LCD_CS_PORT->CRH
# define LCD_RS_DDR		LCD_RS_PORT->CRH
# define LCD_WR_DDR		LCD_WR_PORT->CRH
# define LCD_RD_DDR		LCD_RD_PORT->CRH
# define LCD_REST_DDR	LCD_REST_PORT->CRH

////////////////(1)/////////////////////
//控制端口动作宏定义								
# define LCD_CS_L		SET_PORT_L(LCD_CS_PORT, LCD_CS_BIT)//LCD_CS_PORT &= ~BIT(LCD_CS_BIT)
# define LCD_CS_H		SET_PORT_H(LCD_CS_PORT, LCD_CS_BIT)//LCD_CS_PORT |= BIT(LCD_CS_BIT)

# define LCD_RS_L		SET_PORT_L(LCD_RS_PORT, LCD_RS_BIT)//LCD_RS_PORT &= ~BIT(LCD_RS_BIT)
# define LCD_RS_H		SET_PORT_H(LCD_RS_PORT, LCD_RS_BIT)//LCD_RS_PORT |= BIT(LCD_RS_BIT)

# define LCD_WR_L		SET_PORT_L(LCD_WR_PORT, LCD_WR_BIT)//LCD_WR_PORT &= ~BIT(LCD_WR_BIT)
# define LCD_WR_H		SET_PORT_H(LCD_WR_PORT, LCD_WR_BIT)//LCD_WR_PORT |= BIT(LCD_WR_BIT)

# define LCD_RD_L		SET_PORT_L(LCD_RD_PORT, LCD_RD_BIT)//LCD_RD_PORT &= ~BIT(LCD_RD_BIT)
# define LCD_RD_H		SET_PORT_H(LCD_RD_PORT, LCD_RD_BIT)//LCD_RD_PORT |= BIT(LCD_RD_BIT)

# define LCD_REST_L		SET_PORT_L(LCD_REST_PORT, LCD_REST_BIT)//LCD_REST_PORT &= ~BIT(LCD_REST_BIT)
# define LCD_REST_H		SET_PORT_H(LCD_REST_PORT, LCD_REST_BIT)//LCD_REST_PORT |= BIT(LCD_REST_BIT)

# define LCD_LED_ON		SET_PORT_L(LCD_LED_PORT, LCD_LED_BIT)
# define LCD_LED_OFF	SET_PORT_L(LCD_LED_PORT, LCD_LED_BIT)
////////////////////////////////////////

/////////////////(2)////////////////////
//数据总线端口初始化宏定义				
//有8位和16位模式,根据需要进行更改	
//PB8-15	
# define DATA_L_PORT	GPIOB
# define DATA_L_DDR		DATA_L_PORT->CRH
//从数据端口读取数据
# define DATA_L_PIN		((DATA_L_PORT->IDR & 0xFF00)>>8)
//设置数据端口方向为输入
# define DATA_L_IN		DATA_L_DDR = 0x88888888
//设置数据端口方向为输出
# define DATA_L_OUT		DATA_L_DDR = 0x33333333

//8位模式,低8位不使用
//PC0-7		
# define DATA_H_PORT	GPIOC
# define DATA_H_DDR		DATA_H_PORT->CRL
//从数据端口获取数据
# define DATA_H_PIN		((DATA_H_PORT->IDR & 0x00FF))
//设置数据端口方向为输入
# define DATA_H_IN		DATA_H_DDR = 0x88888888
//设置数据端口方向为输出
# define DATA_H_OUT		DATA_H_DDR = 0x33333333
////////////////////////////////////////

////////////////(3)/////////////////////
//关闭使能,以结束一次读写操作			
# define LCD_WR_END()	LCD_CS_H
//读GRAM时需要一个虚晃的读(Dummy Read)	
#if LCD_8_BIT_EN		> 0
	#define DUMMY_READ()	LCD_RD_L;LCD_RD_H;LCD_RD_L;LCD_RD_H;
#else
	#define DUMMY_READ()	LCD_RD_L;LCD_RD_H;//LCD_RD_L;LCD_RD_H;
#endif
////////////////////////////////////////

////////////////(4)/////////////////////
//16位模式下从数据端口获取数据
#define DATA_16BIT_IN  ((DATA_H_PIN<<8)| DATA_L_PIN) 
//8位模式下从数据端口获取数据
#define DATA_8BIT_IN	DATA_H_PIN
////////////////////////////////////////

////////////////(5)/////////////////////
#define DATA_16BIT_OUT(x)	{\
								DATA_L_PORT->ODR &= 0x00FF;	\
								DATA_L_PORT->BSRR = x<<8;	\
								DATA_H_PORT->ODR &= 0xFF00;	\
								DATA_H_PORT->BSRR = x>>8; 	\
							} 
#define DATA_8BIT_OUT(x)	{\
								DATA_H_PORT->ODR &= 0xFF00;	\
								DATA_H_PORT->ODR |= (u8)x;	\
							} 
////////////////////////////////////////
		
///////////屏显示参数设置///////////////

# define LCD_CHAR_HORIZONTAL		0
//设置屏显示像素大小					
# define X_SIZE			240
# define Y_SIZE			320
//x和y的最大坐标值,坐标原点为(0, 0)		
# define X_END			(X_SIZE - 1)
# define Y_END			(Y_SIZE - 1)
//一个字符x*y的分别大小		
#if LCD_CHAR_HORIZONTAL > 0			
	# define CHAR_X_SIZE	8
	# define CHAR_Y_SIZE	16
	
	//横坐标能显示的字符数X_SIZE/CHAR_X_SIZE
	# define CHAR_X_NUM		30
	//纵坐标能显示的字符数Y_SIZE/CHAR_Y_SIZE
	# define CHAR_Y_NUM		20
#else
	# define CHAR_X_SIZE	16
	# define CHAR_Y_SIZE	8
		
	//横坐标能显示的字符数X_SIZE/CHAR_X_SIZE
	# define CHAR_X_NUM		15
	//纵坐标能显示的字符数Y_SIZE/CHAR_Y_SIZE
	# define CHAR_Y_NUM		40
#endif


////////////////////////////////////////
void LCD_DATA_OUT(u16 data);
u16 LCD_DATA_IN(void);
void LCD_WriteGRAM_EN(void);
void LCD_WriteRegister(u16 index, u16 data);
void LCD_DrawPoint(u16 x, u16 y, u16 color);
u16 LCD_GetPoint(u16 x, u16 y);
void LCD_SetWindow(u16 start_x,u16 start_y,
					u16 end_x,u16 end_y);
void LCD_SetCursor(u16 x,u16 y);
//LCD清屏函数						
void LCD_Clear(u16 color);
//液晶端口初始化,外部无需调用			
void LCD_PortInit(void);
//液晶驱动初始化						
void LCD_DriverInit(void);
# endif
