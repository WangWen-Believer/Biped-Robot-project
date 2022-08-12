/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : memory.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Memory management layer
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/////////////////////////////////
//memory的下一层为mass_mal
/////////////////////////////////
/* Includes ------------------------------------------------------------------*/

#include "memory.h"
#include "usb_scsi.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "hw_config.h"
#include "mass_mal.h"
#include "usb_lib.h"

//#include "stm32_eval.h"

#include "sd_driver.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Block_Read_count = 0;
__IO uint32_t Block_offset;
__IO uint32_t Counter = 0;
uint32_t  Idx;
uint32_t Data_Buffer[BULK_MAX_PACKET_SIZE *2]; /* 512 bytes*/
uint8_t TransferState = TXFR_IDLE;
/* Extern variables ----------------------------------------------------------*/
extern uint8_t Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
extern uint16_t Data_Len;
extern uint8_t Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;
extern uint32_t Mass_Memory_Size[2];
extern uint32_t Mass_Block_Size[2];

////////////////////////////////////////
#define SECTOR_SIZE		512
#define SECTOR_CNT		8
#define BUF_SIZE		SECTOR_SIZE*SECTOR_CNT
static u8 SD_Buffer[BUF_SIZE];
///////////////////////////////////////

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Read_Memory1(uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{
  static uint32_t Offset, Length;

  if (TransferState == TXFR_IDLE )
  {
    Offset = Memory_Offset * Mass_Block_Size[lun];	//扇区地址转化为字节地址(SDHC 需要修改)
    Length = Transfer_Length * Mass_Block_Size[lun];//块长度转化为字节长度
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {
    if (!Block_Read_count)			//Block_Read_count = 0
    {								//读取一个块(对SD来说块大小为一个扇区的大小)	
      MAL_Read(lun ,
               Offset ,
               Data_Buffer,
               Mass_Block_Size[lun]);
	//批量输出BULK_MAX_PACKET_SIZE(64)个字节数据
      USB_SIL_Write(EP1_IN, (uint8_t *)Data_Buffer, BULK_MAX_PACKET_SIZE);
	//512-64
      Block_Read_count = Mass_Block_Size[lun] - BULK_MAX_PACKET_SIZE;
      Block_offset = BULK_MAX_PACKET_SIZE;	//发送偏移增加64
    }
    else
    {//继续发送剩余的(512-64)字节数据
      USB_SIL_Write(EP1_IN, (uint8_t *)Data_Buffer + Block_offset, BULK_MAX_PACKET_SIZE);

      Block_Read_count -= BULK_MAX_PACKET_SIZE;
      Block_offset += BULK_MAX_PACKET_SIZE;
    }
	//设置批量传输端点大小
    SetEPTxCount(ENDP1, BULK_MAX_PACKET_SIZE);
#ifndef USE_STM3210C_EVAL
    SetEPTxStatus(ENDP1, EP_TX_VALID);		//发送使能，开始发送数据
#endif    
    Offset += BULK_MAX_PACKET_SIZE;			//字节地址偏移增加64
    Length -= BULK_MAX_PACKET_SIZE;			//待发送长度减去64

    CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;	//修改CSW的剩余字节数
    Led_RW_ON();							//指示灯亮
  }
  if (Length == 0)
  {											//如果数据发送完毕
    Block_Read_count = 0;					//Block_Read_count 置0
    Block_offset = 0;						//发送偏移置0
    Offset = 0;								//字节地址偏移置0
    Bot_State = BOT_DATA_IN_LAST;			//BOT状态为BOT_DATA_IN_LAST,即将进入批量输入中断完成CSW
    TransferState = TXFR_IDLE;				//发送状态空闲
    Led_RW_OFF();
  }
}
void Read_Memory2(uint8_t lun, uint32_t sector, uint32_t sector_cnt)
{
  	static uint32_t Offset, Length;
	
	static u16 DataLen = 0;					//从存储器实际读出的数据大小
	static u8 Cnt = 0;						//存储缓冲区扇区数大小的整数倍
	static u8 CntLast = 0;					//存储缓冲区扇区数大小的余数
	static u8 MemorReadFlag = 0;			//读存储器标志
	static u8 TransOver = 0;				//传输完成标志
	static u8* pTemp;						
	
  	if (TransferState == TXFR_IDLE )
  	{
	    Offset = sector;					//扇区地址转化为字节地址(SDHC 需要修改)
	    
		TransferState = TXFR_ONGOING;
		
		Cnt = sector_cnt/SECTOR_CNT;		//获取扇区数整数
		CntLast = sector_cnt%SECTOR_CNT;	//获取扇区数余数
		
		MemorReadFlag = 1;					//置1,第一次要读存储器
		TransOver = 0;
	
  	}
  	if (TransferState == TXFR_ONGOING )
  	{
		if(MemorReadFlag)
		{								//读存储器
			if(Cnt)						
			{							//先读整数部分
				SD_Read(SD_Buffer, Offset, SECTOR_CNT);
				Offset += SECTOR_CNT;	//扇区偏移增加
				Cnt -= 1;				//修改整数部分的大小
				DataLen = BUF_SIZE;		//读取到的数据
				
			}
			else if(CntLast)			
			{							//接下来读余数部分
				SD_Read(SD_Buffer, Offset, CntLast);
				Offset += CntLast;
				DataLen = CntLast*512;
				CntLast = 0;			//清零
			}
			
			MemorReadFlag = 0;			//修改标志,接下来通过USB发送数据
			pTemp = SD_Buffer;
			Length = 0;
			if((Cnt == 0) && (CntLast == 0))
			{							//如果整数和余数部分都为0,说明数据已经读完
				TransOver = 1;			//标志置1
			}
		}
		if(!MemorReadFlag)
		{									//批量输出BULK_MAX_PACKET_SIZE(64)个字节数据
	      	USB_SIL_Write(EP1_IN, (u8*)pTemp, BULK_MAX_PACKET_SIZE);
			pTemp += BULK_MAX_PACKET_SIZE;	//修改指针,准备下一次传输
			
			SetEPTxCount(ENDP1, BULK_MAX_PACKET_SIZE);	//设置批量传输端点大小
		#ifndef USE_STM3210C_EVAL
			SetEPTxStatus(ENDP1, EP_TX_VALID);			//发送使能,开始发送数据
		#endif    
			CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;	//修改CSW的剩余字
			
			Length += BULK_MAX_PACKET_SIZE;				//修改已经通过USB发送的数据量
			if(Length == DataLen)
			{								//如果USB发送的数据量等于从存储器读到的数据
				MemorReadFlag = 1;			//标志置1,准备下一次从存储器读取数据
				if(TransOver == 1)			
				{							//如果已经完成了请求的数据量
					TransOver = 2;			//传输完毕
				}
			}
		}
		Led_RW_ON();
	}

	if(TransOver == 2)
	{										//传输完毕
		Bot_State = BOT_DATA_IN_LAST;		//BOT状态为BOT_DATA_IN_LAST,即将进入批量输入中断完成CSW
		TransferState = TXFR_IDLE;			//发送状态空闲
		Led_RW_OFF();
		TransOver = 0;
	}
}
/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Write_Memory1(uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{

  static uint32_t W_Offset, W_Length;

  uint32_t temp =  Counter + 64;						//64字节

  if (TransferState == TXFR_IDLE )
  {											
    W_Offset = Memory_Offset * Mass_Block_Size[lun];	//转化为字节地址(SDHC需要修改)
    W_Length = Transfer_Length * Mass_Block_Size[lun];	//转化为字节长度
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {

    for (Idx = 0 ; Counter < temp; Counter++)
    {													//从用户批量端点缓冲区读取64字节
      *((uint8_t *)Data_Buffer + Counter) = Bulk_Data_Buff[Idx++];
    }

    W_Offset += Data_Len;			//Data_Len为Bulk_Data_Buff中的有效数据长度,最大64字节
    W_Length -= Data_Len;			//待写入的长度减去Data_Len

    if (!(W_Length % Mass_Block_Size[lun]))
    {								//如果待写入长度能被512整除,则写入512字节到SD卡
      Counter = 0;					//Counter置0(Counter的值从0增加到512，以64分段)
      MAL_Write(lun ,
                W_Offset - Mass_Block_Size[lun],	//传入参数为字节偏移,应该更改为扇区偏移
                Data_Buffer,
                Mass_Block_Size[lun]);
    }
	

    CSW.dDataResidue -= Data_Len;	//修改CSW的剩余字节数
  #ifndef STM32F10X_CL				//使能下一次接收
    SetEPRxStatus(ENDP2, EP_RX_VALID); /* enable the next transaction*/   
  #endif /* STM32F10X_CL */

    Led_RW_ON();
  }

  if ((W_Length == 0) || (Bot_State == BOT_CSW_Send))//
  {									//如果数据已经接收完毕并或BOT为BOT_CSW_Send则发送CSW
    //////////////////////////////////
	if(Bot_State == BOT_CSW_Send)	//测试使用,这里BOT的状态为BOT_CSW_Send不大可能
	{
		//STM_EVAL_LEDOff(LED2);
		LED_Off(LED2);
	}
	/////////////////////////////////
	Counter = 0;
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
    TransferState = TXFR_IDLE;
    Led_RW_OFF();
	
  }
}

//中断调用
void Write_Memory2(uint8_t lun, uint32_t sector, uint32_t sector_cnt)
{
	u8 i = 0;
  	static uint32_t W_Offset, W_Length;
	static u32 DataCnt = 0;

  	if(TransferState == TXFR_IDLE )
  	{											
		W_Offset = sector;
		W_Length = sector_cnt*Mass_Block_Size[lun];	//获取字节长度
		TransferState = TXFR_ONGOING;
  	}
  	if(TransferState == TXFR_ONGOING )
  	{
		for(i = 0; i < 64; i ++)
		{											//获取一次批量传输的数据
			SD_Buffer[DataCnt + i] =  Bulk_Data_Buff[i];	
		}
		DataCnt += Data_Len;						//记录一次实际存入SD_Buffer的数据量
		W_Length -= Data_Len;						//减去一次批量传输长度
		
		if(!(W_Length % BUF_SIZE))					//判断是否拷贝了BUF_SIZE大小的数据
		{
			DataCnt /= SECTOR_SIZE;					//转换为扇区数
			SD_Write(SD_Buffer, W_Offset, DataCnt);	//往SD卡写入数据
			W_Offset += DataCnt;
			DataCnt = 0;
		}
		
		CSW.dDataResidue -= Data_Len;				//修改CSW的剩余字节数
		
		#ifndef STM32F10X_CL				
		SetEPRxStatus(ENDP2, EP_RX_VALID);			//使能下一次接收
		#endif /* STM32F10X_CL */
		
		Led_RW_ON();
  	}

  	if((W_Length == 0) || (Bot_State == BOT_CSW_Send))//
  	{									//如果数据已经接收完毕并或BOT为BOT_CSW_Send则发送CSW
    	//////////////////////////////////
		if(Bot_State == BOT_CSW_Send)	//测试使用,这里BOT的状态为BOT_CSW_Send不大可能
		{
			//STM_EVAL_LEDOff(LED2);
			LED_Off(LED2);
		}
		/////////////////////////////////
    	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
    	TransferState = TXFR_IDLE;
    	Led_RW_OFF();
  	}
}

//读memory,扇区(块)大小为512字节
void Read_Memory(uint8_t lun, uint32_t sector, uint32_t sector_cnt)
{
  	static uint32_t DataCnt;
	
	static u32 SectorCnt = 0;						
	static u32 SectorCntTemp = 0;		
	
	static u8 MemorReadFlag = 0;			//读存储器标志
	static u8 TransOver = 0;				//传输完成标志
	static u8* pTemp;						
	
  	if (TransferState == TXFR_IDLE )
  	{ 
		TransferState = TXFR_ONGOING;

		MemorReadFlag = 1;					//置1,第一次要读存储器
		TransOver = 0;
		
		SD_ReadSectorStart(sector, sector_cnt);	//发送读命令,准备读数据
		
		SectorCnt = sector_cnt;
		SectorCntTemp = sector_cnt;
  	}
  	if (TransferState == TXFR_ONGOING )
  	{
		if(MemorReadFlag)
		{								//读存储器
			SD_ReadSector(SD_Buffer);	//第二步:读memory中的数据
			
			pTemp = SD_Buffer;
			DataCnt = 0;				//计算变量置0
			MemorReadFlag = 0;			//修改标志,接下来通过USB发送数据
			
			SectorCnt --;
			if(SectorCnt == 0)
			{
				TransOver = 1;			//标志置1
			}
		}
		if(!MemorReadFlag)
		{									//批量输出BULK_MAX_PACKET_SIZE(64)个字节数据
	      	USB_SIL_Write(EP1_IN, (u8*)pTemp, BULK_MAX_PACKET_SIZE);
			pTemp += BULK_MAX_PACKET_SIZE;	//修改指针,准备下一次传输
			
			SetEPTxCount(ENDP1, BULK_MAX_PACKET_SIZE);	//设置批量传输端点大小
		#ifndef USE_STM3210C_EVAL
			SetEPTxStatus(ENDP1, EP_TX_VALID);			//发送使能,开始发送数据
		#endif    
			CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;	//修改CSW的剩余字
			
			DataCnt += BULK_MAX_PACKET_SIZE;			//修改已经通过USB发送的数据量
			if(DataCnt == 512)
			{							//如果USB发送的数据量等于从存储器读到的数据
				MemorReadFlag = 1;		//标志置1,准备下一次从存储器读取数据
				if(TransOver == 1)			
				{						//如果已经完成了请求的数据量
					TransOver = 2;		//传输完毕
				}
			}
		}
		Led_RW_ON();
	}

	if(TransOver == 2)
	{									//传输完毕
		SD_ReadSectorEnd(SectorCntTemp);//第三步:发送连续读的结束命令,关闭片选
		
		Bot_State = BOT_DATA_IN_LAST;	//BOT状态为BOT_DATA_IN_LAST,即将进入批量输入中断完成CSW
		TransferState = TXFR_IDLE;		//发送状态空闲
		Led_RW_OFF();
		TransOver = 0;
	}
}
//中断调用
void Write_Memory(uint8_t lun, uint32_t sector, uint32_t sector_cnt)
{
  	static uint32_t W_Length;
	static u16 DataCnt = 0;
	static u8 Count = 0;
	u8 i = 0;
  	if(TransferState == TXFR_IDLE )
  	{											
		W_Length = sector_cnt*Mass_Block_Size[lun];	//获取字节长度
		TransferState = TXFR_ONGOING;
		Count = sector_cnt;
		SD_WriteSectorStart(sector, sector_cnt);//第一步:计算扇区,发送写命令,开始写
  	}
  	if(TransferState == TXFR_ONGOING )
  	{
		for(i = 0; i < 64; i ++)
		{											//获取一次批量传输的数据
			SD_Buffer[DataCnt + i] =  Bulk_Data_Buff[i];	
		}
		DataCnt += Data_Len;						//记录一次实际存入SD_Buffer的数据量
		W_Length -= Data_Len;						//减去一次批量传输长度
		
		if(!(W_Length & ((1 << 9) - 1)))			//判断是否拷贝了512字节大小的数据
		{											//每次写512字节,期间不关闭片选
			DataCnt = 0;
			SD_WriteSector(SD_Buffer, Count);	//第二步:写入数据!!!
		}
		
		CSW.dDataResidue -= Data_Len;				//修改CSW的剩余字节数
		
		#ifndef STM32F10X_CL				
		SetEPRxStatus(ENDP2, EP_RX_VALID);			//使能下一次接收
		#endif /* STM32F10X_CL */
		
		Led_RW_ON();
  	}

  	if((W_Length == 0) || (Bot_State == BOT_CSW_Send))
  	{												//如果数据已经接收完毕并或BOT为BOT_CSW_Send则发送CSW
		SD_WriteSectorEnd(Count);				//第三步:发送写结束命令并关闭片选!!!
		
    	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
    	TransferState = TXFR_IDLE;
    	Led_RW_OFF();
  	}
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

