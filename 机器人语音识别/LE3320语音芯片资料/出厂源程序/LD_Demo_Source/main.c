/************************************************************************************/
//	版权所有：Copyright (c) 2005 - 2010 ICRoute INC.
/************************************************************************************/

#include "STC10F08XE.H"
#include "LDchip.h"
#include "Reg_RW.h"
#include "FlashDef.h"

sbit LED1=P3^4;
sbit LED2=P3^5;

/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
uint8 idata nAsrStatus=0;	


/************************************************************************************/
//	以下定义是在示范程序中，用来播放的声音数据的起始位置和长度
//	这些声音是事先在PC机上录制好的MP3文件，在PC机上合成到一个文件 voice.dat中
//	可以把这个voide.dat存储到用户系统中的存储芯片中，诸如 spi-flash中
//	在需要播放时，用户的主控MCU可以到spi-flash中根据要播放文件的起始地址无读取MP3数据
//	并送入LD3320进行播放
/************************************************************************************/
#define MP3_BEIJING_START	0x0000;
#define MP3_BEIJING_SIZE	0x08b8;
#define MP3_SHANGHAI_START	0x1000;
#define MP3_SHANGHAI_SIZE	0x0ab0;
#define MP3_TIANJIN_START	0x2000;
#define MP3_TIANJIN_SIZE	0x0a20;
#define MP3_CHONGQING_START	0x3000;
#define MP3_CHONGQING_SIZE	0x0990;
#define MP3_DING_START	0x4000;
#define MP3_DING_SIZE	0x0828;
#define MP3_NIHAO_START	0x5000;
#define MP3_NIHAO_SIZE	0x1170;


extern void          _nop_     (void);

void MCU_init();
void FlashLED(uint8 nTimes);
void PlaySound(uint8 nCode);
uint8 RunASR();
void ProcessInt0();


/************************************************************************************/
//	这个示范程序是基于STC10L08XE编译的完整地，可以执行的程序
//	事先了识别和播放的功能
//	根据用户说出不同的关键词语，识别后播放对应的mp3声音
//
//	与LD3320芯片有关的函数功能，都在"开发手册.pdf"中有详细说明
//	请开发者对照"开发手册.pdf“阅读
//	
//	开发者在学习LD3320开始时，可以直接把在这个main函数拷贝到自己单片机中编译运行
//	如果只实现ASR语音识别功能，可以把程序中PlaySound()函数的调用注释掉就可以
//	
//	当然，用户要根据自己实际的单片机去修改 mcu_init ，以及对应的管脚连接的定义，中断定义
/************************************************************************************/

void  main()
{
	uint8 idata nAsrRes;

	FlashLED(3);

	MCU_init();
	LD_reset();

	nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR
	PlaySound(CODE_DEFAULT);		//	播放提示音
	while(1)
	{
		if (bMp3Play!=0)			//	如果还在播放MP3中，则等待，直到MP3播放完毕 即bMp3Play==0
			continue;				//	bMp3Play 是定义的一个全局变量用来记录MP3播放的状态，不是LD3320芯片内部的寄存器

		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				FlashLED(4);
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	//	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算
				{
					nAsrStatus = LD_ASR_ERROR;
					LED1=0;
					LED2=0;
				}
				break;
			}
			case LD_ASR_FOUNDOK:
			{
				FlashLED(2);
				nAsrRes = LD_GetResult();	//	一次ASR识别流程结束，去取ASR识别结果
				PlaySound(nAsrRes);
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				FlashLED(1);
				PlaySound(CODE_DEFAULT);
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}// switch
	}// while

}

void MCU_init()
{
	P1M0 |= 1;
	P3M0 |= 8;

	LED1=0;
	LED2=0;
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xf7;
	P4 = 0x0f;

#if defined (SOFT_SPI_PORT)		//	软件模拟SPI读写
	LD_MODE = 1;				//	设置MD管脚为高
#elif defined (HARD_SPI_PORT)	//	硬件实现SPI读写
	LD_MODE = 1;				//	设置MD管脚为高
#else							//	并行读写 （硬件实现或者软件模拟）
	LD_MODE = 0;				//	设置MD管脚为低
#endif


	IP=0;
	IPH=0;

	PX0=1; 
	PT0=1;
	PS=1;
	IPH |= 1;	
	
	EX0=0;
	EX1=0;
	EA=1;
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

/*********************************************************************
//为了消除编译时的 警告 *** WARNING L15: MULTIPLE CALL TO SEGMENT
//把在中断函数中需要调用的函数重新复制并命名
//消除警告 Warning L15，并且避免由于函数重入可能带来的隐藏Bug
/*********************************************************************/
void  delay_2(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

void FlashLED(uint8 nTimes)
{
	uint8 k;
	for (k=0; k<nTimes; k++)
	{
		LED1=0;
		LED2=0;
		delay(15000);
		LED1=1;
		LED2=1;
		delay(15000);
	}
}

void PlaySound(uint8 nCode)
{
	switch(nCode)
	{
	case CODE_BEIJING:
		nMp3StartPos = MP3_BEIJING_START;
		nMp3Size = MP3_BEIJING_SIZE;
		break;
	case CODE_SHANGHAI:
		nMp3StartPos = MP3_SHANGHAI_START;
		nMp3Size = MP3_SHANGHAI_SIZE;
		break;
	case CODE_TIANJIN:
		nMp3StartPos = MP3_TIANJIN_START;
		nMp3Size = MP3_TIANJIN_SIZE;
		break;
	case CODE_CHONGQING:
		nMp3StartPos = MP3_CHONGQING_START;
		nMp3Size = MP3_CHONGQING_SIZE;
		break;
	default:
		nMp3StartPos = MP3_NIHAO_START;
		nMp3Size = MP3_NIHAO_SIZE;
		break;		
	}

	LD_Init_MP3();
	LD_AdjustMIX2SPVolume(15);
	LD_play();
}


/************************************************************************************/
//	IO_Send_Byte()是主控MCU向spi-flash (型号为华邦的 W25X40)发送指令
//	开发者应该根据自己使用的存储芯片去写具体的函数
//
//	ICroute公司无法对存储芯片的读写提供技术支持，
//	开发者需要自己向自己使用的存储芯片的厂商获得技术支持
//	或者在网络上搜索相关代码和文档
//
//	华邦的spi-flash的技术支持的文档页面在：
//	http://www.winbond.com.tw/hq/cht/ProductAndSales/ProductLines/FlashMemory/SerialFlash/
//	http://www.xtdpj.com/show_hdr.php?xname=915RL41&dname=23T0M41&xpos=84
/************************************************************************************/

void IO_Send_Byte(uint8 dataout)
{
	 uint8 i = 0; 
	 FLASH_CS = 0;
	 for (i=0; i<8; i++)
	 {
		  if ((dataout & 0x80) == 0x80) 
			   FLASH_DIO = 1;
		  else
			   FLASH_DIO = 0;
		  FLASH_CLK = 1;
		  dataout = (dataout << 1); 
		  FLASH_CLK = 0;   
	 }
}


/************************************************************************************/
//	RunASR()函数实现了一次完整的ASR语音识别流程
//	LD_AsrStart() 函数实现了ASR初始化
//	LD_AsrAddFixed() 函数实现了添加关键词语到LD3320芯片中
//	LD_AsrRun()	函数启动了一次ASR语音识别流程
//
//	任何一次ASR识别流程，都需要按照这个顺序，从初始化开始进行
/************************************************************************************/

uint8 RunASR()
{
	uint8 i=0;
	uint8 asrflag=0;
	for (i=0; i<5; i++)			//	防止由于硬件原因导致LD3320芯片工作不正常，所以一共尝试5次启动ASR识别流程
	{
		LD_AsrStart();
		delay(100);
		if (LD_AsrAddFixed()==0)
		{
			LD_reset();			//	LD3320芯片内部出现不正常，立即重启LD3320芯片
			delay(100);			//	并从初始化开始重新ASR识别流程
			continue;
		}
		delay(10);
		if (LD_AsrRun() == 0)
		{
			LD_reset();			//	LD3320芯片内部出现不正常，立即重启LD3320芯片
			delay(100);			//	并从初始化开始重新ASR识别流程
			continue;
		}

		asrflag=1;
		break;					//	ASR流程启动成功，退出当前for循环。开始等待LD3320送出的中断信号
	}

	return asrflag;
}

void ExtInt0Handler(void) interrupt 0  
{
	ProcessInt0();				//	LD3320 送出中断信号，包括ASR和播放MP3的中断，需要在中断处理函数中分别处理
}



