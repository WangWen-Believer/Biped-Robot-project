#include "nandtester.h"
#include "nand.h"
#include "ftl.h"
#include "string.h"
#include "usart.h"
#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//NAND FLASH USMART测试代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	  


//向NAND某一页写入指定大小的数据
//pagenum:要写入的页地址
//colnum:要写入的开始列地址(页内地址)
//writebytes:要写入的数据大小，MT29F16G最大为4320，MT29F4G最大为2112
u8 test_writepage(u32 pagenum,u16 colnum,u16 writebytes)
{
	u8 *pbuf;
	u8 sta=0;
    u16 i=0;
	pbuf=mymalloc(SRAMIN,5000);  
    for(i=0;i<writebytes;i++)//准备要写入的数据,填充数据,从0开始增大
    { 
        pbuf[i]=i;	
    }
	sta=NAND_WritePage(pagenum,colnum,pbuf,writebytes);	//向nand写入数据	
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}

//读取NAND某一页指定大小的数据
//pagenum:要读取的页地址
//colnum:要读取的开始列地址(页内地址)
//readbytes:要读取的数据大小，MT29F16G最大为4320，MT29F4G最大为2112
u8 test_readpage(u32 pagenum,u16 colnum,u16 readbytes)
{
	u8 *pbuf;
	u8 sta=0;
    u16 i=0;
	pbuf=mymalloc(SRAMIN,5000);  
	sta=NAND_ReadPage(pagenum,colnum,pbuf,readbytes);	//读取数据
	if(sta==0||sta==NSTA_ECC1BITERR||sta==NSTA_ECC2BITERR)//读取成功
	{ 
		printf("read page data is:\r\n");
		for(i=0;i<readbytes;i++)	 
		{ 
			printf("%x ",pbuf[i]);  //串口打印读取到的数据
		}
		printf("\r\nend\r\n");
	}
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}

//将一页数据拷贝到另外一页,并写入一部分内容.
//注意:源页和目标页要在同一个Plane内！(同为奇数/同为偶数)
//spnum:源页地址
//epnum:目标页地址
//colnum:要写入的开始列地址(页内地址)
//writebytes:要写入的数据大小，不能超过页大小
u8 test_copypageandwrite(u32 spnum,u32 dpnum,u16 colnum,u16 writebytes)
{
	u8 *pbuf;
	u8 sta=0;
    u16 i=0;
	pbuf=mymalloc(SRAMIN,5000);  
    for(i=0;i<writebytes;i++)//准备要写入的数据,填充数据,从0X80开始增大
    { 
        pbuf[i]=i+0X80;	
    }
	sta=NAND_CopyPageWithWrite(spnum,dpnum,colnum,pbuf,writebytes);	//向nand写入数据	
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}
 
//读取NAND某一页Spare区指定大小的数据
//pagenum:要读取的页地址
//colnum:要读取的spare区开始地址
//readbytes:要读取的数据大小，MT29F16G最大为64，MT29F4G最大为224
u8 test_readspare(u32 pagenum,u16 colnum,u16 readbytes)
{
	u8 *pbuf;
	u8 sta=0;
    u16 i=0;
	pbuf=mymalloc(SRAMIN,512);  
	sta=NAND_ReadSpare(pagenum,colnum,pbuf,readbytes);	//读取数据
	if(sta==0)//读取成功
	{ 
		printf("read spare data is:\r\n");
		for(i=0;i<readbytes;i++)	 
		{ 
			printf("%x ",pbuf[i]);  //串口打印读取到的数据
		}
		printf("\r\nend\r\n");
	}
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}

//从指定位置开始,读取整个NAND,每个BLOCK的第一个page的前5个字节
//sblock:指定开始的block编号
void test_readallblockinfo(u32 sblock)
{
    u8 j=0;
    u32 i=0;
	u8 sta;
    u8 buffer[5];
    for(i=sblock;i<nand_dev.block_totalnum;i++)
    {
        printf("block %d info:",i);
        sta=NAND_ReadSpare(i*nand_dev.block_pagenum,0,buffer,5);//读取每个block,第一个page的前5个字节
        if(sta)printf("failed\r\n");
		for(j=0;j<5;j++)
        {
            printf("%x ",buffer[j]);
        }
        printf("\r\n");
    }	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//FTL层测试代码

//从某个扇区开始,写入seccnt个扇区的数据
//secx:开始的扇区编号
//secsize:扇区大小
//seccnt:要写入的扇区个数
u8 test_ftlwritesectors(u32 secx,u16 secsize,u16 seccnt)
{
	u8 *pbuf;
	u8 sta=0;
    u32 i=0;
	pbuf=mymalloc(SRAMIN,secsize*seccnt);  
    for(i=0;i<secsize*seccnt;i++)	//准备要写入的数据,填充数据,从0开始增大
    { 
        pbuf[i]=i;	
    }
	sta=FTL_WriteSectors(pbuf,secx,secsize,seccnt);	//向nand写入数据	
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}


//从某个扇区开始,读出seccnt个扇区的数据
//secx:开始的扇区编号
//secsize:扇区大小
//seccnt:要读取的扇区个数
u8 test_ftlreadsectors(u32 secx,u16 secsize,u16 seccnt)
{
	u8 *pbuf;
	u8 sta=0;
    u32 i=0;
	pbuf=mymalloc(SRAMIN,secsize*seccnt);   
	sta=FTL_ReadSectors(pbuf,secx,secsize,seccnt);	//读取数据
	if(sta==0)
	{
		printf("read sec %d data is:\r\n",secx); 
		for(i=0;i<secsize*seccnt;i++)	//准备要写入的数据,填充数据,从0开始增大
		{ 
			printf("%x ",pbuf[i]);  //串口打印读取到的数据
		}
		printf("\r\nend\r\n");
	}
	myfree(SRAMIN,pbuf);	//释放内存
	return sta;
}





























