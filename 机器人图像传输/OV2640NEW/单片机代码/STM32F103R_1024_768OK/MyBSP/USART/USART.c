#include "USART.h"          
#include <stdio.h>

static USART_TypeDef* COM_USART[COMn] = {USART_COM1, USART_COM2}; 

static GPIO_TypeDef* COM_TX_PORT[COMn] = {USART_COM1_TX_GPIO_PORT, USART_COM2_TX_GPIO_PORT};
 
static GPIO_TypeDef* COM_RX_PORT[COMn] = {USART_COM1_RX_GPIO_PORT, USART_COM2_RX_GPIO_PORT};
 
const uint32_t COM_USART_CLK[COMn] = {USART_COM1_CLK, USART_COM2_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {USART_COM1_TX_GPIO_CLK, USART_COM2_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {USART_COM1_RX_GPIO_CLK, USART_COM2_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {USART_COM1_TX_PIN, USART_COM2_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {USART_COM1_RX_PIN, USART_COM2_RX_PIN};

const uint16_t COM_IRQn[COMn] = {USART_COM1_IRQn, USART_COM2_IRQn};

const uint8_t COM_Priority[COMn] = {USART_COM1_Prio, USART_COM2_Prio};


/////////////////////////////////////////////////////////////////////////////////
///////使用标准printf的串口字节发送重定义///////////
//第一步：
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
//第二步：
#pragma import(__use_no_semihosting) 
_sys_exit(int x) 
{ 
x = x; 
} 
struct __FILE 
{ 
int handle; 
/* Whatever you require here. If the only file you are using is */ 
/* standard output using printf() for debugging, no file handling */ 
/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;
//第三步：
//默认使用COM1
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  	/* Place your implementation of fputc here */
  	/* e.g. write a character to the USART */
  
  	/* Loop until the end of transmission */
  	while (USART_GetFlagStatus(USART_COM1, USART_FLAG_TC) == RESET)
  	{}
 	USART_SendData(USART_COM1, (uint8_t) ch);
  	return ch;
}
////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
static void USART_NvicCfg(uint16_t IRQn, uint8_t prio)
{
	NVIC_InitTypeDef NVIC_InitStructure;

  	/* Configure the NVIC Preemption Priority Bits */  
   	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the USARTz Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART_NVIC_PREE_PRI;	//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = prio;						//响应优先级
   	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}

static void USART_HardwareInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//初始化NVIC
	USART_NvicCfg(COM_IRQn[COM], COM_Priority[COM]);	
	
	//端口初始化,
	// Enable GPIO clock ,AFIO时钟只有在使用USART3重映射时才开启->RCC_APB2Periph_AFIO
	RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);
	
	//USART时钟使能 Enable UART clock 
	if (COM == COM1)
	{	//USART1  为APB2
		RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
	}
	else
	{	//USART2-3为APB1
		RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
	}
	
	//配置USART Tx端口 Configure USART Tx as alternate function push-pull
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
	
	//配置USART Rx端口 Configure USART Rx as input floating 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
	GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
	
	
		
	//USART初始化
	USART_Init(COM_USART[COM], USART_InitStruct);
	
	//接收中断使能
  	USART_ITConfig(COM_USART[COM], USART_IT_RXNE, ENABLE);
   	//USART_ITConfig(USART_COM1, USART_IT_TXE, ENABLE);
	
	//使能USART
	USART_Cmd(COM_USART[COM], ENABLE);
}
void USART_SendChar(COM_TypeDef COM, u8 ch_data)
{
  	/* Loop until the end of transmission */
  	while (USART_GetFlagStatus(COM_USART[COM], USART_FLAG_TC) == RESET)
  	{
		;
	}
	USART_SendData(COM_USART[COM], (u8)ch_data);
}

void USART1_Init(u32 baud_rate)
{
	/* USARTx configured as follow:
        - BaudRate = baud_rate baud  
        - 8位 Word Length = 8 Bits
        - 1位停止位 One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = baud_rate;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_HardwareInit(COM1, &USART_InitStructure);
}
void USART2_Init(u32 baud_rate)
{
	/* USARTx configured as follow:
        - BaudRate = baud_rate baud  
        - 8位 Word Length = 8 Bits
        - 1位停止位 One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = baud_rate;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_HardwareInit(COM2, &USART_InitStructure);
}

static u8 COM1_RxBuff[30]={0};
static u8 Index=0;
static u8 Frame_Length = 0;

static u8 RxBuffer2[10];
static u8 RxCounter2 = 0;
/////////////////////////////////////////////////////////////////////////////////////////////
void USART1_RxIntHandler(void)
{
	if(USART_GetITStatus(USART_COM1, USART_IT_RXNE) != RESET)
	{
		//Read one byte from the receive data register 
		COM1_RxBuff[Index] = USART_ReceiveData(USART_COM1);
	}
	if(Index < Frame_Length)
	{
		Index ++;
	}
	//if(USART_GetITStatus(USART_COM1, USART_IT_TXE) != RESET)
	//{   
		
	//}
}
void USART2_RxIntHandler(void)
{
	if(USART_GetITStatus(USART_COM2, USART_IT_RXNE) != RESET)
	{
		//Read one byte from the receive data register 
		RxBuffer2[RxCounter2++] = USART_ReceiveData(USART_COM2);
	}
	//if(USART_GetITStatus(USART_COM1, USART_IT_TXE) != RESET)
	//{   
		
	//}
}
void USART1_Transmit(u8 ch_data)
{
	// Loop until the end of transmission
  	while (USART_GetFlagStatus(USART_COM1, USART_FLAG_TC) == RESET)
  	{
		;
	}
	USART_SendData(USART_COM1, (u8)ch_data);
}

void USART2_Transmit(u8 ch_data)
{
	// Loop until the end of transmission 
  	while (USART_GetFlagStatus(USART_COM2, USART_FLAG_TC) == RESET)
  	{
		;
	}
	USART_SendData(USART_COM2, (u8)ch_data);
}

//////////////////////////////上层应用函数/////////////////////////////////////
void USART_Debug(u8 debug_data)
{
	USART_Transmit(0xaa);
	USART_Transmit(debug_data);
	USART_Transmit(0x55);
}
void USART_SendLine(s32 Data ,
					u8 Is_H, 
				    u8 Line_ID)
{
	u8 Temp_A_L;				
	u8 Temp_A_H;
	u8 Temp_B_L;
	s8 Temp_B_H;
	
	u8 ch_XOR = 0;
	
	Temp_A_L = Data;
	Temp_A_H = Data>>8;
	Temp_B_L = Data >> 16;
	Temp_B_H = Data >> 24;
	
	ch_XOR ^= 0x09;
	ch_XOR ^= Line_ID;
	
	ch_XOR ^= Temp_B_H;
	ch_XOR ^= Temp_B_L;
	ch_XOR ^= Temp_A_H;
	ch_XOR ^= Temp_A_L;
	
	USART_Transmit(0xaa);
	USART_Transmit(0x09);
	USART_Transmit(Line_ID);
	
	if(Is_H)							//是否是先发高字节？					
	{
		USART_Transmit(Temp_B_H);		//是									
		USART_Transmit(Temp_B_L);
		USART_Transmit(Temp_A_H);
		USART_Transmit(Temp_A_L);
	}
	else
	{
		USART_Transmit(Temp_A_L);		//不是									
		USART_Transmit(Temp_A_H);
		USART_Transmit(Temp_B_L);
		USART_Transmit(Temp_B_H);
	}
	
	USART_Transmit(ch_XOR);
	USART_Transmit(0x55);
}
void USART_SendString(unsigned char *p_STR)
{
	while(*p_STR)
	{
		USART_Transmit(*p_STR ++);
	}
}
//////////////接收///////////////////
u8 USART_GetChar(u8* p_array, u8 frame_len)
{
	u8 i = 0;
	if(Frame_Length != frame_len)
	{
		Frame_Length = frame_len;
	}
	if(Index == Frame_Length)
	{
		for(i=0; i< Frame_Length; i++)
		{
			p_array[i] = COM1_RxBuff[i];
		}
		Index = 0;
		return 1;
	}
	return 0;
}
u8 USART_GetRate(s32* p_rate)
{
	u8 temp_array[9] = {0};
	u8 i =0;										
	s32 temp_rate = 0;
	static u8 ch_cmd = 0;					//命令位用静态变量，保证数据能保持在
											//上一次接收到的值（即不丢失）		
	if(USART_GetChar(temp_array, 9))		//如果收到新数据才进行数据校验与恢复
	{										//这样提高了查询速度				
		if((temp_array[0] == 0xaa)&&(temp_array[8] == 0x55))
		{
			for(i = 3; i < 7; i ++)
			{
				temp_rate |= temp_array[i]<<((i-3)<<3);//8*(i-3)				
			}
			ch_cmd = temp_array[2];			//获取命令位						
			*p_rate = temp_rate;			//获取数据位						
		}
	}
	return ch_cmd;
}

/////////////////////////////////////////////////////////////////////
//调试用串口打印函数
# define UartPutChar	USART_Transmit
# define Printc			USART_Transmit

/********************************************************************
函数功能：发送一个字符串。
入口参数：pd：要发送的字符串指针。
返    回：无。
备    注：无。
********************************************************************/
void Prints(const u8 * pd)
{
	while((*pd)!='\0') //发送字符串，直到遇到0才结束
	{
		UartPutChar(*pd); //发送一个字符
		pd++;  //移动到下一个字符
	}
}
////////////////////////End of function//////////////////////////////
/********************************************************************
函数功能：将整数转按十进制字符串发送。
入口参数：x：待显示的整数。
返    回：无。
备    注：无。
********************************************************************/
void PrintLongInt(u32 x)
{
 	s8 i;
 	u8 display_buffer[10];

	for(i=9;i>=0;i--)
	{
		display_buffer[i]='0'+x%10;
		x/=10;
	}
	for(i=0;i<9;i++)
	{
		if(display_buffer[i]!='0')
		{
			break;	
		}
	}
	for(;i<10;i++)
	{
		UartPutChar(display_buffer[i]);	
	}
}
////////////////////////End of function//////////////////////////////
const u8 HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/********************************************************************
函数功能：将短整数按十六进制发送。
入口参数：待发送的整数。
返    回：无。
备    注：无。
********************************************************************/
void PrintShortIntHex(u16 x)
{
 	u8 i;
 	u8 display_buffer[7];
 	display_buffer[6]=0;
 	display_buffer[0]='0';
 	display_buffer[1]='x';
 	for(i=5;i>=2;i--) //将整数转换为4个字节的HEX值
 	{
	  	display_buffer[i]=HexTable[(x&0xf)];
	  	x>>=4;
 	}
 	Prints(display_buffer);
}

/********************************************************************
函数功能：以HEX格式发送一个byte的数据。
入口参数：待发送的数据
返    回：无。
备    注：无。
********************************************************************/
void PrintHex(u8 x)
{
	Printc('0');
	Printc('x');
	Printc(HexTable[x>>4]);
	Printc(HexTable[x&0xf]);
	Printc(' ');
}
////////////////////////End of function//////////////////////////////
