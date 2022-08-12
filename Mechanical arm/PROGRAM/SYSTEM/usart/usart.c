#include "usart.h"
#include "dma.h"
#include "lcd.h"
#include "servo.h"
u8 Receive_cnt=0;
u8 Receive_data[10]={0}; //½ÓÊÜµ½µÄÊý¾Ý
////////////////////////////////////////////////////////////////////////////////// 	 
//Èç¹ûÊ¹ÓÃos,Ôò°üÀ¨ÏÂÃæµÄÍ·ÎÄ¼þ¼´¿É.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os Ê¹ÓÃ	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//²ÉÓÃUSART3×÷Îª¶æ»úÊÕ·¢Êý¾Ý´®¿Ú
//********************************************************************************
//V1.0ÐÞ¸ÄËµÃ÷ 
////////////////////////////////////////////////////////////////////////////////// 	  
//¼ÓÈëÒÔÏÂ´úÂë,Ö§³Öprintfº¯Êý,¶ø²»ÐèÒªÑ¡Ôñuse MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
#pragma import(__use_no_semihosting)             
//±ê×¼¿âÐèÒªµÄÖ§³Öº¯Êý                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//ÖØ¶¨Òåfputcº¯Êý 
int fputc(int ch, FILE *f)
{ 	
	while((USART2->ISR&0X40)==0);//Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
  USART2->TDR=(u8)ch;	
	return ch;
}
#endif 

//#if EN_USART2_RX   //Èç¹ûÊ¹ÄÜÁË½ÓÊÕ
//´®¿Ú2ÖÐ¶Ï·þÎñ³ÌÐò
//×¢Òâ,¶ÁÈ¡USARTx->SRÄÜ±ÜÃâÄªÃûÆäÃîµÄ´íÎó   	

//½ÓÊÕ×´Ì¬
//bit15£¬	½ÓÊÕÍê³É±êÖ¾
//bit14£¬	½ÓÊÕµ½0x0d
//bit13~0£¬	½ÓÊÕµ½µÄÓÐÐ§×Ö½ÚÊýÄ¿

UART_HandleTypeDef UART2_Handler; //UART¾ä±ú
//³õÊ¼»¯IO ´®¿Ú2 
//bound:²¨ÌØÂÊ
void uart_init(u32 bound)
{		
 	//UART2 ³õÊ¼»¯ÉèÖÃ   
	UART2_Handler.Instance=USART2;					    //USART2
	UART2_Handler.Init.BaudRate=bound;				    //²¨ÌØÂÊ
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //Ò»¸öÍ£Ö¹Î»
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //ÎÞÆæÅ¼Ð£ÑéÎ»
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //ÎÞÓ²¼þÁ÷¿Ø
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //ÊÕ·¢Ä£Ê½
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()»áÊ¹ÄÜUART1
}

//UARTµ×²ã³õÊ¼»¯£¬Ê±ÖÓÊ¹ÄÜ£¬Òý½ÅÅäÖÃ£¬ÖÐ¶ÏÅäÖÃ
//´Ëº¯Êý»á±»HAL_UART_Init()µ÷ÓÃ
//huart:´®¿Ú¾ä±ú

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIOB¶Ë¿ÚÉèÖÃ
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART2)//Èç¹ûÊÇ´®¿Ú2£¬½øÐÐ´®¿Ú2 MSP³õÊ¼»¯
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//Ê¹ÄÜGPIOAÊ±ÖÓ
		__HAL_RCC_USART2_CLK_ENABLE();			//Ê¹ÄÜUSART2Ê±ÖÓ
	  
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//ÍÆÍìÊä³ö
		GPIO_Initure.Pull=GPIO_PULLUP;			//ÉÏÀ­
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//¸ßËÙ
		GPIO_Initure.Alternate=GPIO_AF7_USART2;	//¸´ÓÃÎªUSART2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//³õÊ¼»¯PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3¡¢
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//³õÊ¼»¯PA3
		#if EN_USART2_RX
	 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);		//¿ªÆô½ÓÊÕÖÐ¶
		 __HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//¿ªÆô½ÓÊÕÖÐ¶ÏÏ
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//Ê¹ÄÜUSART3ÖÐ¶ÏÍ¨µÀ
		HAL_NVIC_SetPriority(USART2_IRQn,3,4);			//ÇÀÕ¼ÓÅÏÈ¼¶3£¬×ÓÓÅÏÈ¼¶3
#endif	
	}	
   }


//´®¿Ú3ÖÐ¶Ï·þÎñ³ÌÐò
void USART2_IRQHandler(void)                	
{  
#if SYSTEM_SUPPORT_OS	 	//Ê¹ÓÃOS
  	OSIntEnter();    
#endif
if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //¿ÕÏÐÖÐ¶Ï	
{
    HAL_UART_Receive(&UART2_Handler,&Receive_data[Receive_cnt], 1, 0xfff);
	   Receive_cnt++;

}
if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_IDLE)!=RESET))  //¿ÕÏÐÖÐ¶Ï
{
   	Receive_cnt=0;
	  __HAL_UART_CLEAR_IT(&UART2_Handler, UART_CLEAR_IDLEF);//Çå³ýÖÐ¶Ï±êÖ¾Î»
//	  Check_Receivedata(&Receive_data[0],&Servo_State[0][0]);                                 //½«²éÑ¯»ØÀ´µÄ¶æ»úµÄ²ÎÊý·ÅÈë¶æ»úpositionÖÐ
}
	  
#if SYSTEM_SUPPORT_OS	 	//Ê¹ÓÃOS
	OSIntExit(); 									 
#endif
}
//#endif
//´®¿Ú2ÖÐ¶Ï·þÎñ³ÌÐò

void Check_Receivedata(u8 *ReceiveStata,u8 *ServoStata)  //½«·µ»ØµÄÎ»ÖÃÊý¾Ý·ÅÈë¶æ»úÎ»ÖÃ¿â
{
	u8 mid;
	u8 *RECEIVE_DATA[10],*SERVODATA[11][7];
	RECEIVE_DATA[0]=ReceiveStata;
	SERVODATA[0][0]=ServoStata;
	
	if(*RECEIVE_DATA[3]==0x04)//·µ»ØÊý¾Ý³¤¶È
	{
		mid=*RECEIVE_DATA[2];    //ID
		mid--;
		*SERVODATA[mid][1]=*RECEIVE_DATA[5];  
		*SERVODATA[mid][2]=*RECEIVE_DATA[6];
	}
}
