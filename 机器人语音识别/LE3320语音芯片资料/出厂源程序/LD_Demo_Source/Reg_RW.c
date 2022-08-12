/************************************************************************************/
//	版权所有：Copyright (c) 2005 - 2010 ICRoute INC.
/************************************************************************************/

#include "STC10F08XE.H"
#include "Reg_RW.h"

extern void _nop_(void);

/************************************************************************************/
//	主控MCU对于LD3320读写寄存器的实现有四种：
//	#define SOFT_PARA_PORT		//	软件模拟并行读写
//	#define HARD_PARA_PORT		//	硬件实现并行读写 （需要主控MCU有硬件的WR/RD端口）
//	#define SOFT_SPI_PORT		//	软件模拟SPI读写
//	#define HARD_SPI_PORT		//	硬件实现SPI读写	  （需要主控MCU有硬件SPI接口）
/************************************************************************************/


#ifdef SOFT_PARA_PORT

		#define DELAY_NOP	_nop_();_nop_();_nop_();
		sbit	LD_WR 	= P3^6;
		sbit	LD_RD	= P3^7;
		sbit	LD_CS	= P2^6;
		sbit	LD_A0	= P2^0;
		void LD_WriteReg( unsigned char address, unsigned char dataout )
		{
			P0 = address;
			LD_A0 = 1;
			LD_CS = 0;
			LD_WR = 0;
			DELAY_NOP;
		
			LD_WR = 1;
			LD_CS = 1;
			DELAY_NOP;
		
			P0 = dataout;
			LD_A0 = 0;
			LD_CS = 0;
			LD_WR = 0;
			DELAY_NOP;
		
			LD_WR = 1;
			LD_CS = 1;
			DELAY_NOP;
		}
		
		unsigned char LD_ReadReg( unsigned char address )
		{
			unsigned char datain;
		
			P0 = address;
			LD_A0 = 1;
			LD_CS = 0;
			LD_WR = 0;
			DELAY_NOP;
		
			LD_WR = 1;
			LD_CS = 1;
			DELAY_NOP;
		
			LD_A0 = 0;
			LD_CS = 0;
			LD_RD = 0;
			DELAY_NOP;

			datain = P0;
			LD_RD = 1;
			LD_CS = 1;
			DELAY_NOP;
		
			return datain;
		}
#endif

#ifdef HARD_PARA_PORT

		#define LD_INDEX_PORT		(*((volatile unsigned char xdata*)(0x8100))) 
		#define LD_DATA_PORT		(*((volatile unsigned char xdata*)(0x8000))) 
		
		//评估板上 MCU的A8 连接到 LD芯片的AD
		//         MCU的A14 连接到 LD芯片的CSB
		//         MCU的RD、WR 连接 LD芯片的RD、WR (xdata 读写时自动产生低信号)
		//
		//0x8100的二进制是10000001 00000000		CSB=0 AD=1
		//                 ^     ^
		//0x8000的二进制是10000000 00000000		CSB=0 AD=0
		//                 ^     ^
		
		void LD_WriteReg( unsigned char address, unsigned char dataout )
		{
			LD_INDEX_PORT  = address;         
			LD_DATA_PORT = dataout;          
		}
		
		unsigned char LD_ReadReg( unsigned char address )
		{
			LD_INDEX_PORT = address;         
			return (unsigned char)LD_DATA_PORT;     
		}
#endif

#ifdef SOFT_SPI_PORT
		#define DELAY_NOP	_nop_();_nop_();_nop_();
		
		sbit SCS=P2^6;    //芯片片选信号
		sbit SDCK=P0^2;   //SPI 时钟信号
		sbit SDI=P0^0;    //SPI 数据输入
		sbit SDO=P0^1;    //SPI 数据输出
		sbit SPIS=P3^6;   //SPI模式设置：低有效。

		void LD_WriteReg(unsigned char address,unsigned char dataout)
		{
			unsigned char i = 0;
			unsigned char command=0x04;
			SPIS =0;
			SCS = 0;
			DELAY_NOP;
		
			//write command
			for (i=0;i < 8; i++)
			{
				if ((command & 0x80) == 0x80) 
					SDI = 1;
				else
					SDI = 0;
				
				DELAY_NOP;
				SDCK = 0;
				command = (command << 1);  
				DELAY_NOP;
				SDCK = 1;  
			}
			//write address
			for (i=0;i < 8; i++)
			{
				if ((address & 0x80) == 0x80) 
					SDI = 1;
				else
					SDI = 0;
				DELAY_NOP;
				SDCK = 0;
				address = (address << 1); 
				DELAY_NOP;
				SDCK = 1;  
			}
			//write data
			for (i=0;i < 8; i++)
			{
				if ((dataout & 0x80) == 0x80) 
					SDI = 1;
				else
					SDI = 0;
				DELAY_NOP;
				SDCK = 0;
				dataout = (dataout << 1); 
				DELAY_NOP;
				SDCK = 1;  
			}
			DELAY_NOP;
			SCS = 1;
		}

		unsigned char LD_ReadReg(unsigned char address)
		{
			unsigned char i = 0; 
			unsigned char datain =0 ;
			unsigned char temp = 0; 
			unsigned char command=0x05;
			SPIS =0;
			SCS = 0;
			DELAY_NOP;
		
			//write command
			for (i=0;i < 8; i++)
			{
				if ((command & 0x80) == 0x80) 
					SDI = 1;
				else
					SDI = 0;
				DELAY_NOP;
				SDCK = 0;
				command = (command << 1);  
				DELAY_NOP;
				SDCK = 1;  
			}

			//write address
			for (i=0;i < 8; i++)
			{
				if ((address & 0x80) == 0x80) 
					SDI = 1;
				else
					SDI = 0;
				DELAY_NOP;
				SDCK = 0;
				address = (address << 1); 
				DELAY_NOP;
				SDCK = 1;  
			}
			DELAY_NOP;

			//Read data
			for (i=0;i < 8; i++)
			{
				datain = (datain << 1);
				temp = SDO;
				DELAY_NOP;
				SDCK = 0;  
				if (temp == 1)  
					datain |= 0x01; 
				DELAY_NOP;
				SDCK = 1;  
			}
		
			DELAY_NOP;
			SCS = 1;
			return datain;
		}

#endif

#ifdef HARD_SPI_PORT
		/*
		STC单片机（带SPI口的种类）兼顾读写的函数例程
		unsigend char SPI_TR( unsigned char x ) 
		{ 
			SPSTAT=0xC0;  
			SPDAT=x;  
			while(!(SPSTAT&0x80));  
			return SPDAT;
		}
		
		--------------------------------------------------
		AVR单片机（带SPI口的种类）兼顾读写的函数例程
		unsigend char SPI_TR( unsigned char x ) 
		{ 
			SPDR=x;  
			while(!(SPSR & (1<<SPIF)));  
			return SPDR;
		}

		*/
		void LD_WriteReg( unsigned char address, unsigned char dataout )
		{
			// 这里添加硬件SPI口的操作代码：
			SPI_TR(0x04); // 发送 0x04
			SPI_TR(address); // 发送 address
			SPI_TR(dataout); // 发送 dataout
		}
		unsigned char LD_ReadReg( unsigned char address )
		{
			// 这里添加硬件SPI口的操作代码：
			SPI_TR(0x05); // 发送 0x05
			SPI_TR(address); // 发送 address
			return (SPI_TR(0)); // 读出数据, 并返回
		}
#endif




