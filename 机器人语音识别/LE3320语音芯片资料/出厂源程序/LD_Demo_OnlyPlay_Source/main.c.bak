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

uint8 idata nDemoFlag=0;


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

void PlayDemoSound_Once();
void PlayDemoSound_Continue();


/************************************************************************************/
//	这个示范程序是基于STC10L08XE编译的完整地，可以执行的程序
//	实现了从数组中播放的功能
//  
//  verygood_withHead.mp3(verygood_withoutHead)是一段MP3格式的声音文件，播放内容为英文单词"very good"
//	demosound.h 中定义了数组 bpDemoSound[]，
//  数组的内容就是 verygood_withHead.mp3(verygood_withoutHead)文件的内容
//  用户可以用16进制阅读器（比如 UltraEdit ）打开verygood_withHead.mp3文件和 bpDemoSound 数组相对照
//
//	关于两个MP3文件的差异：  
//	这两个MP3文件只差有没有ID3文件头，MP3的数据都是一样的，
//	ID3文件头传入LD芯片与否不影响播放
//  用Windows自带的MediaPlayer播放没有ID3头的vertygood_withoutHead.mp3 后，会自动加上ID3文件头
//  PlayDemoSound_Once/PlayDemoSound_Continue 函数就是把 bpDemoSound数组中的数据依次传入LD3320芯片进行播放
//
//  与LD3320芯片有关的函数功能，都在"开发手册.pdf"中有详细说明
//	请开发者对照"开发手册.pdf“阅读
//	
//	开发者在学习LD3320开始时，可以直接把在这个main函数拷贝到自己单片机中编译运行
//	
//	当然，用户要根据自己实际的单片机去修改 mcu_init ，以及对应的管脚连接的定义，中断定义
/************************************************************************************/

void  main()
{
//	uint8 idata nAsrRes;
	uint8 nTemp;

	FlashLED(3);

	MCU_init();
	LD_reset();

	// 以下2行只能有一条有效，
	// 功能分别是播放一次和连续不停播放。
	//PlayDemoSound_Once();		//	之播放一次
	PlayDemoSound_Continue();	//	连续循环播放

	while(1)
	{
		nTemp++;
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

/************************************************************************************/
// 这2个函数结构相同，只是对终止条件有一点区别。
// nDemoFlag 是一个标志值，如果=1就是执行从内存里读数据，而不去读Flash了。
// 载入数据函数LD_ReloadMp3Data()里，有以下代码：
//			val = bpDemoSound[nMp3Pos++];
//			LD_WriteReg(0x01,val);
//			if (nMp3Pos == DEMO_SOUND_SIZE)
//				nMp3Pos = 0;
// 这里，当 nMp3Pos 累加后等于 DEMO_SOUND_SIZE 时，就设为0；
// 所以如果 nMp3Size 设为 DEMO_SOUND_SIZE， 就永远不会满足
//		 if(nMp3Pos>=nMp3Size) {
//			// B. 声音数据已发送完毕。
// 声音就会一直播放下去。
//
// 如果 nMp3Size 减小，第一次播放完后就满足条件了，播放就停止了。
/************************************************************************************/

//#define DEMO_SOUND_SIZE 851	// 对应vertygood_withoutHead.mp3 这个MP3文件没有ID3的文件头
#define DEMO_SOUND_SIZE 1235	// 对应verygood_withHead.mp3 这个MP3文件有ID3的文件头
								//	这两个MP3文件只差有没有ID3文件头，MP3的数据都是一样的，
								//	ID3文件头传入LD芯片与否不影响播放
								//  用Windows自带的MediaPlayer播放没有ID3头的vertygood_withoutHead.mp3 后，会自动加上ID3文件头

void PlayDemoSound_Once()
{
	nDemoFlag = 1;
	nMp3StartPos = 0;
	nMp3Size = DEMO_SOUND_SIZE-1;
	LD_Init_MP3();
	LD_AdjustMIX2SPVolume(7);
	LD_play();
}

void PlayDemoSound_Continue()
{
	nDemoFlag = 1;
	nMp3StartPos = 0;
	nMp3Size = DEMO_SOUND_SIZE;
	LD_Init_MP3();
	LD_AdjustMIX2SPVolume(7);
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


void ExtInt0Handler(void) interrupt 0  
{
	ProcessInt0();				//	LD3320 送出中断信号，包括ASR和播放MP3的中断，需要在中断处理函数中分别处理
}



