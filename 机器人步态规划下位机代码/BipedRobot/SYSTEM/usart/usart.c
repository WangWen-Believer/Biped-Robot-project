#include "usart.h"
#include "dma.h"
#include "lcd.h"
#include "servo.h"
#include "led.h"
u8 Receive_cnt=0,Receive_PC_cnt=0;uint8_t Receive_PC_Data[400]={0}; 
u8 Receive_data[10]={0}; //Ω” ‹µΩµƒ ˝æ›
uint8_t TxBuffer3[400]={0};  
uint8_t RxBuffer4[400]={0};
uint8_t TxCounter4;
uint8_t RxCounter4=0;
uint8_t TxBuffer1[400]; 
uint8_t Rec_Len;


 
 
 
uint8_t rec_f,tx_flag,flash_led;
////////////////////////////////////////////////////////////////////////////////// 	 
//»Áπ˚ π”√os,‘Ú∞¸¿®œ¬√ÊµƒÕ∑Œƒº˛º¥ø….
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os  π”√	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//≤…”√USART2◊˜Œ™∂Êª˙ ’∑¢ ˝æ›¥Æø⁄

//º”»Î“‘œ¬¥˙¬Î,÷ß≥÷printf∫Ø ˝,∂¯≤ª–Ë“™—°‘Òuse MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
#pragma import(__use_no_semihosting)             
//±Í◊ºø‚–Ë“™µƒ÷ß≥÷∫Ø ˝                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//∂®“Â_sys_exit()“‘±‹√‚ π”√∞Î÷˜ª˙ƒ£ Ω    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//÷ÿ∂®“Âfputc∫Ø ˝ 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->ISR&0X40)==0);//—≠ª∑∑¢ÀÕ,÷±µΩ∑¢ÀÕÕÍ±œ   
  USART1->TDR=(u8)ch;	
	return ch;
}
#endif 
u8 USART_RX_BUF[USART_REC_LEN];     //Ω” ’ª∫≥Â,◊Ó¥ÛUSART_REC_LEN∏ˆ◊÷Ω⁄.
//Ω” ’◊¥Ã¨
//bit15£¨	Ω” ’ÕÍ≥…±Í÷æ
//bit14£¨	Ω” ’µΩ0x0d
//bit13~0£¨	Ω” ’µΩµƒ”––ß◊÷Ω⁄ ˝ƒø
u16 USART_RX_STA=0;       //Ω” ’◊¥Ã¨±Íº«	

u8 aRxBuffer[RXBUFFERSIZE];//HALø‚ π”√µƒ¥Æø⁄Ω” ’ª∫≥Â
//#if EN_USART2_RX   //»Áπ˚ πƒ‹¡ÀΩ” ’
//¥Æø⁄2÷–∂œ∑˛ŒÒ≥Ã–Ú
//◊¢“‚,∂¡»°USARTx->SRƒ‹±‹√‚ƒ™√˚∆‰√Óµƒ¥ÌŒÛ   	

//Ω” ’◊¥Ã¨
//bit15£¨	Ω” ’ÕÍ≥…±Í÷æ
//bit14£¨	Ω” ’µΩ0x0d
//bit13~0£¨	Ω” ’µΩµƒ”––ß◊÷Ω⁄ ˝ƒø
UART_HandleTypeDef UART1_Handler;
UART_HandleTypeDef UART2_Handler; //UARTæ‰±˙
UART_HandleTypeDef UART3_Handler; 
UART_HandleTypeDef UART7_Handler; 
UART_HandleTypeDef UART5_Handler;
//≥ı ºªØIO ¥Æø⁄2 
//bound:≤®Ãÿ¬ 
void uart_init(void)
{
	uart1_init(128000);  //connect pc
	uart2_init(1000000); //servo
//	uart3_init(9600);
//	uart7_init(9600);//gps “˝Ω≈±ª”√

}
void uart1_init(u32 bound)
{	
	//UART ≥ı ºªØ…Ë÷√
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //≤®Ãÿ¬ 
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //◊÷≥§Œ™8Œª ˝æ›∏Ò Ω
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //“ª∏ˆÕ£÷πŒª
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //Œﬁ∆Ê≈º–£—ÈŒª
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //Œﬁ”≤º˛¡˜øÿ
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    // ’∑¢ƒ£ Ω
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()ª· πƒ‹UART1
	
	//HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//∏√∫Ø ˝ª·ø™∆ÙΩ” ’÷–∂œ£∫±Í÷æŒªUART_IT_RXNE£¨≤¢«“…Ë÷√Ω” ’ª∫≥Â“‘º∞Ω” ’ª∫≥ÂΩ” ’◊Ó¥Û ˝æ›¡ø
  
}

void uart2_init(u32 bound)
{		
 	//UART2 ≥ı ºªØ…Ë÷√   
	UART2_Handler.Instance=USART2;					    //USART2
	UART2_Handler.Init.BaudRate=bound;				    //≤®Ãÿ¬ 
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //◊÷≥§Œ™8Œª ˝æ›∏Ò Ω
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //“ª∏ˆÕ£÷πŒª
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //Œﬁ∆Ê≈º–£—ÈŒª
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //Œﬁ”≤º˛¡˜øÿ
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    // ’∑¢ƒ£ Ω
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()ª· πƒ‹UART2
}
void uart3_init(u32 bound)
{		
 	//UART3 ≥ı ºªØ…Ë÷√   
	UART3_Handler.Instance=USART3;					    //USART3
	UART3_Handler.Init.BaudRate=bound;				    //≤®Ãÿ¬ 
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //◊÷≥§Œ™8Œª ˝æ›∏Ò Ω
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	    //“ª∏ˆÕ£÷πŒª
	UART3_Handler.Init.Parity=UART_PARITY_NONE;		    //Œﬁ∆Ê≈º–£—ÈŒª
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //Œﬁ”≤º˛¡˜øÿ
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		    // ’ƒ£ Ω
	HAL_UART_Init(&UART3_Handler);					    //HAL_UART_Init()ª· πƒ‹UART3
}

void uart7_init(u32 bound)
{		
 	//UART2 ≥ı ºªØ…Ë÷√   
	UART7_Handler.Instance=UART7;					    //USART2
	UART7_Handler.Init.BaudRate=bound;				    //≤®Ãÿ¬ 
	UART7_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //◊÷≥§Œ™8Œª ˝æ›∏Ò Ω
	UART7_Handler.Init.StopBits=UART_STOPBITS_1;	    //“ª∏ˆÕ£÷πŒª
	UART7_Handler.Init.Parity=UART_PARITY_NONE;		    //Œﬁ∆Ê≈º–£—ÈŒª
	UART7_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //Œﬁ”≤º˛¡˜øÿ
	UART7_Handler.Init.Mode=UART_MODE_TX_RX;		    // ’∑¢ƒ£ Ω
	HAL_UART_Init(&UART7_Handler);					    //HAL_UART_Init()ª· πƒ‹UART1
}


//UARTµ◊≤„≥ı ºªØ£¨ ±÷” πƒ‹£¨“˝Ω≈≈‰÷√£¨÷–∂œ≈‰÷√
//¥À∫Ø ˝ª·±ªHAL_UART_Init()µ˜”√
//huart:¥Æø⁄æ‰±˙

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIOB∂Àø⁄…Ë÷√
	GPIO_InitTypeDef GPIO_Initure;
		if(huart->Instance==USART1)//»Áπ˚ «¥Æø⁄1£¨Ω¯––¥Æø⁄1 MSP≥ı ºªØ
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			// πƒ‹GPIOA ±÷”
		__HAL_RCC_USART1_CLK_ENABLE();			// πƒ‹USART1 ±÷”
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//∏¥”√Õ∆ÕÏ ‰≥ˆ
		GPIO_Initure.Pull=GPIO_PULLUP;			//…œ¿≠
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//∏ﬂÀŸ
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//∏¥”√Œ™USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//≥ı ºªØPA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//≥ı ºªØPA10
		
#if EN_USART1_RX
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//ø™∆ÙΩ” ’÷–∂œ
		__HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);		//ø™∆Ùø’œ–÷–∂œ
		HAL_NVIC_EnableIRQ(USART1_IRQn);				// πƒ‹USART1÷–∂œÕ®µ¿
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//«¿’º”≈œ»º∂3£¨◊””≈œ»º∂3
#endif	
	}
	if(huart->Instance==USART2)//»Áπ˚ «¥Æø⁄2£¨Ω¯––¥Æø⁄2 MSP≥ı ºªØ
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			// πƒ‹GPIOA ±÷”
		__HAL_RCC_USART2_CLK_ENABLE();			// πƒ‹USART2 ±÷”
	  
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//Õ∆ÕÏ ‰≥ˆ
		GPIO_Initure.Pull=GPIO_PULLUP;			//…œ¿≠
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//∏ﬂÀŸ
		GPIO_Initure.Alternate=GPIO_AF7_USART2;	//∏¥”√Œ™USART2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//≥ı ºªØPA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3°¢
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//≥ı ºªØPA3
		#if EN_USART2_RX
	 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);		//ø™∆ÙΩ” ’÷–∂
		 __HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//ø™∆ÙΩ” ’÷–∂œœ
		HAL_NVIC_EnableIRQ(USART2_IRQn);				// πƒ‹USART3÷–∂œÕ®µ¿
		HAL_NVIC_SetPriority(USART2_IRQn,3,2);			//«¿’º”≈œ»º∂3£¨◊””≈œ»º∂3
#endif	
	}	

	
	if(huart->Instance==UART7)//»Áπ˚ «¥Æø⁄7£¨Ω¯––¥Æø⁄4 MSP≥ı ºªØ
	{
		__HAL_RCC_GPIOF_CLK_ENABLE();			// πƒ‹GPIOA ±÷”
		__HAL_RCC_UART7_CLK_ENABLE();			// πƒ‹USART2 ±÷”
	  
		GPIO_Initure.Pin=GPIO_PIN_6;			//PF6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//Õ∆ÕÏ ‰≥ˆ
		GPIO_Initure.Pull=GPIO_PULLUP;			//…œ¿≠
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//∏ﬂÀŸ
		GPIO_Initure.Alternate=GPIO_AF8_UART7;	//∏¥”√Œ™UART7
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);	   	//≥ı ºªØPF6
		
		GPIO_Initure.Pin=GPIO_PIN_7;			//PF7		
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);	   	//≥ı ºªØPF7
	#if EN_UART7_RX
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//ø™∆ÙΩ” ’÷–∂œœ
		HAL_NVIC_EnableIRQ(UART7_IRQn);				// πƒ‹USART4÷–∂œÕ®µ¿
		HAL_NVIC_SetPriority(UART7_IRQn,4,2);			//«¿’º”≈œ»º∂4£¨◊””≈œ»º2
#endif	
	}


 }



//¥Æø⁄1÷–∂œ∑˛ŒÒ≥Ã–Ú
void USART1_IRQHandler(void)                	
{ 
	OS_ERR err;
#if SYSTEM_SUPPORT_OS	 	// π”√OS
	OSIntEnter();    
#endif
	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //Ω” ’÷–∂œ
	{
    HAL_UART_Receive(&UART1_Handler,&Receive_PC_Data[Receive_PC_cnt], 1, 0xfff);
		Receive_PC_cnt++;
	}
		if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_IDLE)!=RESET))  //Ω” ’÷–∂œ
	{
    Receive_PC_cnt=0;
		__HAL_UART_CLEAR_IT(&UART1_Handler, UART_CLEAR_IDLEF);//«Â≥˝÷–∂œ±Í÷æŒª
		OSSemPost(&PC_SEM,OS_OPT_POST_1,&err);//∑¢ÀÕ–≈∫≈¡ø
		
	}
	
#if SYSTEM_SUPPORT_OS	 	// π”√OS
	OSIntExit();  											 
#endif
}  
 //¥Æø⁄2÷–∂œ∑˛ŒÒ≥Ã–Ú   servo data
void USART2_IRQHandler(void)                	
{  

		OS_ERR err;
#if SYSTEM_SUPPORT_OS	 	// π”√OS
  	OSIntEnter();    
#endif
if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //ø’œ–÷–∂œ	
{
    HAL_UART_Receive(&UART2_Handler,&Receive_data[Receive_cnt], 1, 0xfff);
	   Receive_cnt++;
}
if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_IDLE)!=RESET))  //ø’œ–÷–∂œ
{
   	Receive_cnt=0;
	  __HAL_UART_CLEAR_IT(&UART2_Handler, UART_CLEAR_IDLEF);//«Â≥˝÷–∂œ±Í÷æŒª
		OSSemPost(&SERVO_SEM,OS_OPT_POST_1,&err);//∑¢ÀÕ–≈∫≈¡ø

//	  Check_Receivedata(&Receive_data[0],&Servo_State[0][0]);                                 //Ω´≤È—Øªÿ¿¥µƒ∂Êª˙µƒ≤Œ ˝∑≈»Î∂Êª˙position÷–
}
	  
#if SYSTEM_SUPPORT_OS	 	// π”√OS
	OSIntExit(); 									 
#endif
}




void UART7_IRQHandler(void)    //GPS            	
{  
	OS_ERR err;
#if SYSTEM_SUPPORT_OS	 	// π”√OS
  	OSIntEnter();    
#endif
if((__HAL_UART_GET_FLAG(&UART7_Handler,UART_FLAG_RXNE)!=RESET))  
{
    HAL_UART_Receive(&UART7_Handler,&RxBuffer4[RxCounter4], 1, 0xfff);
	  RxCounter4++;
		if(RxBuffer4[RxCounter4-1]=='$')  //≈–∂œ∆ º±Í÷æ
    {
	   	RxBuffer4[0]='$';
			RxCounter4=1; 
		}    
		if(RxBuffer4[RxCounter4-1]==0x0a) //≈–∂œΩ· ¯±Í÷æ «∑Ò «0x0d 0x0a
		{	  	
	  		Rec_Len=RxCounter4;
	  		RxCounter4=0; 														 
				OSSemPost(&GPS_SEM,OS_OPT_POST_1,&err);//∑¢ÀÕ–≈∫≈¡ø
    }
}

#if SYSTEM_SUPPORT_OS	 	// π”√OS
  	OSIntExit(); 									 
#endif
}

void Check_Receivedata(u8 *ReceiveStata,u8 *ServoStata)  //Ω´∑µªÿµƒŒª÷√ ˝æ›∑≈»Î∂Êª˙Œª÷√ø‚
{
	u8 mid;
	u8 *RECEIVE_DATA[10],*SERVODATA[11][7];
	RECEIVE_DATA[0]=ReceiveStata;
	SERVODATA[0][0]=ServoStata;
	
	if(*RECEIVE_DATA[3]==0x04)//∑µªÿ ˝æ›≥§∂»
	{
		mid=*RECEIVE_DATA[2];    //ID
		mid--;
		*SERVODATA[mid][1]=*RECEIVE_DATA[5];  
		*SERVODATA[mid][2]=*RECEIVE_DATA[6];
	}
}
