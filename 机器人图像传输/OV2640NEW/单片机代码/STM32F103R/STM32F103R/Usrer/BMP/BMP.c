#include "BMP.h"
#include "MyBspInc.h"
#include "string.h"

static u16 MenuBuf[1][1];	//4个字符占用量加上2个像素宽度的边框(64*4 +(16+4)*4)
u16* P_ImageBuf = (u16*)(&(MenuBuf[0][0]));

//# include "ILI9320.h"
//# include "USART.h"
//# include "integer.h"
//# include "IND_LED.h"
//				R		G		B			
//RGB555掩码为0x7C00、0x03E0、0x001F		
//RGB565掩码为0xF800、0x07E0、0x001F
#define LINE_SIZE_CNT		12			//这个值必须为偶数，小于等于16
#define LINE_PIXEL_CNT		320
#define IMAGE_BUFFER_SIZE	(LINE_SIZE_CNT*LINE_PIXEL_CNT*2)
extern u16* P_ImageBuf;
#define RGB555_R_MASK	0x7C00
#define RGB555_G_MASK	0x03E0
#define RGB555_B_MASK	0x001F

#define RGB565_R_MASK	0xF800
#define RGB565_G_MASK	0x07E0
#define RGB565_B_MASK	0x001F

#define RGB555toRGB565_(rgb555)	((((rgb555) & 0x7C00) << 1) | (((rgb555) & 0x03E0) << 1) | ((rgb555) & 0x001F))
#define RGB24toRGB565_(b, g, r)	((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#define RGB32toRGB565_(b, g, r)	((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))



typedef struct RGB_MASK{
	DWORD rMask;  											
	DWORD gMask;  					
	DWORD bMask;  																			
}RGB_MASK;

const RGB_MASK rgb555_mask={
							RGB555_R_MASK,
							RGB555_G_MASK,
							RGB555_B_MASK
};
const RGB_MASK rgb565_mask={
							RGB565_R_MASK,
							RGB565_G_MASK,
							RGB565_B_MASK
};
void Get_BmpFileHeader(BITMAPFILEHEADER* pf_header, void* pdata)
{
	u8* pbuf = (u8*)pdata;
	
	pf_header->bfType = *(u16*)pbuf;
	pbuf += 2;
	
}

//十六位的bmp读取并显示函数			
//16位的字对齐可能在每行多引入一个	
//虚点，在扫描时要跳过它			
//传入的buf_size为2的整数倍			
void BMP_Read16Clr1(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size)
{
	FRESULT res;
	u32 br = 0;
	
	u16 *p_rgb555 = 0;
	u16 temp_rgb565 = 0;
	
	u32 i = 0;		
	u16 real_pix_width = 			//字对齐后的实际宽度(16位为一个像素)
					(((p_iheader->biWidth * p_iheader->biBitCount)+31)>>5)<<1;
							
	unsigned int pix_cnt = 0;				//这个变量记录扫描过的像素点		
	buf_size -= (buf_size%2);				//以2个字节为整数倍读取
	if(p_iheader->biCompression == BI_RGB)
	{										//RGB555							
		if(p_iheader->biWidth < real_pix_width)
		{									//存在字对齐处理					
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}							//强制转换为16位的rgb数据			
				p_rgb555 = (u16 *)p_buf;
											//显示一个buf的像素					
				for(i = 0; i < (br >> 1); i ++)
				{
					pix_cnt ++;
					if(pix_cnt == real_pix_width)
					{
						pix_cnt = 0;
						continue;	
					}
					temp_rgb565 = RGB555toRGB565_(*(p_rgb555 + i));
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
		else								//不存在字对齐处理					
		{
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				p_rgb555 = (u16 *)p_buf;
				for(i = 0; i < (br  >> 1); i ++)
				{
					temp_rgb565 = RGB555toRGB565_(*(p_rgb555 + i));
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
	}										//两段代码差异不大	RGB565			
	else if(p_iheader->biCompression == BI_BITFIELDS)
	{										
		if(p_iheader->biWidth < real_pix_width)
		{									//存在字对齐处理					
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				temp_rgb565 = *(u16 *)p_buf;
			
				for(i = 0; i < (br >> 1); i ++)
				{
					pix_cnt ++;
					if(pix_cnt == real_pix_width)
					{
						pix_cnt = 0;
						continue;	
					}				
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
		else								//不存在字对齐处理					
		{
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				p_rgb555 = (u16 *)p_buf;
				for(i = 0; i < (br  >> 1); i ++)
				{
					LCD_DATA_OUT(*(p_rgb555 + i));
				}
			}
		}
	}
}
//十六位的bmp读取并显示函数			
//16位的字对齐可能在每行多引入一个	
//虚点，在扫描时要跳过它			
//传入的buf_size为2的整数倍			
void BMP_Read16Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size)
{
	FRESULT res;
	u32 br = 0;
	
	u16 *p_rgb555 = 0;
	u16 temp_rgb565 = 0;
	u16 cnt = 0;
	u16 line_cnt = 0;
	static u32 LineCnt = 0;
	u32 i = 0;		
	u32 j = 0;
	u16 real_pix_width = 			//字对齐后的实际宽度(16位为一个像素)
					(((p_iheader->biWidth * p_iheader->biBitCount)+31)>>5)<<1;
							
	unsigned int pix_cnt = 0;				//这个变量记录扫描过的像素点		
	buf_size -= (buf_size%2);				//以2个字节为整数倍读取
	if(p_iheader->biCompression == BI_RGB)
	{										//RGB555							
		if(p_iheader->biWidth < real_pix_width)
		{									//存在字对齐处理					
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}							//强制转换为16位的rgb数据			
				p_rgb555 = (u16 *)p_buf;
											//显示一个buf的像素					
				for(i = 0; i < (br >> 1); i ++)
				{
					pix_cnt ++;
					if(pix_cnt == real_pix_width)
					{
						pix_cnt = 0;
						continue;	
					}
					temp_rgb565 = RGB555toRGB565_(*(p_rgb555 + i));
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
		else								//不存在字对齐处理					
		{
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				p_rgb555 = (u16 *)p_buf;
				for(i = 0; i < (br  >> 1); i ++)
				{
					temp_rgb565 = RGB555toRGB565_(*(p_rgb555 + i));
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
	}										//两段代码差异不大	RGB565			
	else if(p_iheader->biCompression == BI_BITFIELDS)
	{										
		if(p_iheader->biWidth < real_pix_width)
		{									//存在字对齐处理					
			while(1)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				temp_rgb565 = *(u16 *)p_buf;
			
				for(i = 0; i < (br >> 1); i ++)
				{
					pix_cnt ++;
					if(pix_cnt == real_pix_width)
					{
						pix_cnt = 0;
						continue;	
					}				
					LCD_DATA_OUT(temp_rgb565);
				}
			}
		}
		else								//不存在字对齐处理					
		{
			for(j = 0; j < 240; j +=LINE_SIZE_CNT)
			{								//读取SD卡的数据					
				res = f_read(p_fbmp, p_buf, buf_size, &br);
				if(res || (br == 0))
				{
					return;
				}
				for(cnt = 0; cnt < LINE_SIZE_CNT; cnt +=2)
				{
					p_rgb555 = (u16 *)p_buf + 320*cnt;
					for(i = 0; i < 320 - 8; i += 2,p_rgb555 += 2)
					{
						LCD_DATA_OUT(*p_rgb555 );
					}
					line_cnt ++;
					if((line_cnt > (240>>1) - 5))
					{	//绘图完毕
						return;
					}
				}
			}
		}
	}
}
//二十四位的bmp读取并显示函数			
//24位的字对齐可能在每行引入1,2,或3个字	
//节,所以在扫描时不同于16位的扫描，要虑	
//除的是字节，而不是像素点				
//传入的buf_size为3的整数倍				
void BMP_Read24Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size)
{
	FRESULT res;
	u32 br = 0;
	
	u8 r,g,b;
	u16 temp_rgb565 = 0;
	
	u32 i = 0;		
	u16 real_char_width = 					//字对齐后的实际字节数,区别于16位bmp
					(((p_iheader->biWidth * p_iheader->biBitCount)+31)>>5)<<2;
											
	u16 char_cnt = 0;						//这个变量记录扫描过的字节数，区别于16位
	u16 temp = (p_iheader->biWidth)*3;	
	
																
	if(temp < real_char_width)				//以real_char_width个字节为整数倍读取
	{	buf_size = buf_size -(buf_size%real_char_width);								
		//如果一行的字节宽度存在字对齐		
		while(1)
		{
			res = f_read(p_fbmp, p_buf, buf_size, &br);
			if(res || (br == 0))
			{
				return;
			}
			for(i = 0; i < br; )
			{
											//将因字对齐而多加的字节跳过		
				if((char_cnt >= temp) && 
				   (char_cnt <= real_char_width))
				{
					char_cnt ++;
					i++;					//i必须跟着加以实现打点的跳过		
					if(char_cnt == real_char_width)
					{
						char_cnt = 0;
					}
					continue;	
				}
				
			
				char_cnt += 3;				//正常显示时一次显示三个字节		
				
				b = *(p_buf + i);			//获取一个像素的rgb					
				i++;
				g = *(p_buf + i);
				i ++;
				r = *(p_buf + i);
				i ++;
				
				temp_rgb565= RGB24toRGB565_(b, g, r);
				/*DATA_L = temp_rgb565;
				DATA_H = temp_rgb565 >> 8;
				WR_L;
				WR_H;*/
				LCD_DATA_OUT(temp_rgb565);
			}
		}
	}
	else									//以3个字节为整数倍读取
	{	buf_size = buf_size -(buf_size%3);
		while(1)
		{
			res = f_read(p_fbmp, p_buf, buf_size, &br);
			if(res || (br == 0))
			{
				return;
			}
			for(i = 0; i < br; )
			{
				b = *(p_buf + i);
				i++;
				g = *(p_buf + i);
				i ++;
				r = *(p_buf + i);
				i ++;
				
				temp_rgb565= RGB24toRGB565_(b, g, r);
				/*DATA_L = temp_rgb565;
				DATA_H = temp_rgb565 >> 8;
				WR_L;
				WR_H;*/
				LCD_DATA_OUT(temp_rgb565);
				
			}
		}
	}
}

//三十二位的bmp读取并显示函数			
//32为的bmp不会因字对齐在每行引入多的字	
//节，因为32位天然的字对齐				
//传入的buf_size为4的整数倍				
void BMP_Read32Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size)
{
	FRESULT res;
	u32 br = 0;
	
	u8 r,g,b;
	u16 temp_rgb565 = 0;
	
	u32 i = 0;		
	buf_size -= (buf_size%4);					//以4个字节为整数倍读取
	p_iheader->biClrUsed = p_iheader ->biClrUsed;
	while(1)
	{
		res = f_read(p_fbmp, p_buf, buf_size, &br);
		if(res || (br == 0))
		{
			return;
		}
		for(i = 0; i < br; )
		{
			b = *(p_buf + i);
			i++;
			g = *(p_buf + i);
			i ++;
			r = *(p_buf + i);
			i ++;
			i ++;
			
			temp_rgb565= RGB32toRGB565_(b, g, r);
			/*DATA_L = temp_rgb565;
			DATA_H = temp_rgb565 >> 8;
			WR_L;
			WR_H;*/
			LCD_DATA_OUT(temp_rgb565);
		}
	}
}


u32 BMP_MakeBmpFile(long bmp_width, 
					long bmp_height,
					FIL* p_bmp,
					const char *p_path,
					u8 bmp_type)
{
	BITMAPFILEHEADER f_header;
	BITMAPINFOHEADER info_header;
	
	RGB_MASK rgb_mask;
	FRESULT res;
	u32 bw = 0;
										//初始化bmp的文件头和信息头							
	BMP_bmpInit(bmp_width, bmp_height, 16, &f_header, &info_header, bmp_type);
	res = f_open(p_bmp, p_path, FA_CREATE_ALWAYS | FA_WRITE);
	
	if(res)
	{
		res = f_close(p_bmp);
		return 0;
	}
	res = f_lseek(p_bmp, f_header.bfSize);	//新建的bmp文件大小
	res = f_lseek(p_bmp, 0);				//定位到文件开头
	//写入文件头
	res = f_write(p_bmp, &f_header, sizeof(BITMAPFILEHEADER), &bw);
	//写入信息头
	res = f_write(p_bmp, &info_header, sizeof(BITMAPINFOHEADER), &bw);
	
	//写RGB MASK
	if(bmp_type == RGB565)
	{
		res = f_write(p_bmp, &rgb565_mask, sizeof(RGB_MASK), &bw);	
	}
	else if(bmp_type == RGB555)
	{
		res = f_write(p_bmp, &rgb555_mask, sizeof(RGB_MASK), &bw);	
	}
	
	res = f_sync(p_bmp);
	return info_header.biSizeImage;
}

u8 BMP_FillBmp(FIL* p_bmp,
				 u32 fill_size,
				 void* p_buf,
				 u32 buf_size)
{	
	static u32 Cnt = 0;
	FRESULT res;
	u32 bw = 0;
	fill_size -= Cnt;
	if(fill_size > buf_size)
	{
		res = f_write(p_bmp, p_buf, buf_size, &bw);
		Cnt += buf_size;
		return 0;
	}
	else
	{
		res = f_write(p_bmp, p_buf, fill_size, &bw);
		res = f_close(p_bmp);
		Cnt = 0;
		return 1;
	}
}


void BMP_bmpInit(long bmp_width,
				 long bmp_height,
				 unsigned int bmp_bitcount,
				 BITMAPFILEHEADER *p_fheader, BITMAPINFOHEADER *p_info_header,
				 u8 bmp_type)
{
	long bmp_width_temp = 				//4字节对齐后的实际宽度
				(((bmp_width * bmp_bitcount)+31)>>5)<<1;
	p_fheader->bfType = 0x4D42;			//由文件头,信息头加图像数据(没有调色板)		
	p_fheader->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp_width_temp*bmp_height*2;
	if((bmp_type == RGB555) || (bmp_type== RGB565))
	{
		p_fheader->bfSize += sizeof(RGB_MASK);
	}
	p_fheader->bfReserved1 = 0;			//保留位为0								
	p_fheader->bfReserved2 = 0;			//在没有彩色表的情况下位图数据存于此	
	p_fheader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	if((bmp_type == RGB555) || (bmp_type== RGB565))
	{
		p_fheader->bfOffBits += sizeof(RGB_MASK);
	}
										//通常情况下信息头大小为该值			
	p_info_header->biSize = sizeof(BITMAPINFOHEADER);
	p_info_header->biWidth = bmp_width;	//初始化为0								
	p_info_header->biHeight = -bmp_height;	//初始化为0							
	p_info_header->biPlanes = 1;		//初始化为16位位图						
	p_info_header->biBitCount = bmp_bitcount;
	if((bmp_type == RGB555) || (bmp_type== RGB565))
	{									//16位模式
		p_info_header->biCompression = BI_BITFIELDS;
	}
	else
	{
		p_info_header->biCompression = BI_RGB;	
	}				
										//位图由以下公式计算					
	p_info_header->biSizeImage = bmp_width_temp * bmp_height*2;
	p_info_header->biXPelsPerMeter = 0;	//分辨率初始为0							
	p_info_header->biYPelsPerMeter = 0;
	p_info_header->biClrUsed = 0;		//使用到的颜色数为0表示颜色数为2的biBitCount次方，如16位则为65K色
	p_info_header->biClrImportant = 0;	//所有颜色都重要						
}

////////////////////
////////////////////
signed char BMP_Showbmp1(unsigned int start_x,
			  			unsigned int start_y,
			  			const char *p_path)
{
	FIL f_bmp;
	FRESULT res;
	unsigned int br = 0;
	u8*pbuf = (u8*)P_ImageBuf;			//buffer的大小不要小于两个文件头的	
											//大小，通常为54					
	BITMAPFILEHEADER f_header;
	BITMAPINFOHEADER info_header;
	
	res = f_open(&f_bmp, p_path, FA_OPEN_EXISTING | FA_READ);
	
	if(res)
	{
		return -1;							//打开失败则返回失败标志			
	}										//读一个缓冲区的数据				
	
	res = f_read(&f_bmp, pbuf, 512, &br);				
											//位图文件头	结构体赋值			
	f_header = *(BITMAPFILEHEADER *)pbuf;
	//memcpy(&f_header, buffer, sizeof(BITMAPFILEHEADER));
	if(f_header.bfType != 0x4d42)
	{
		return 1;							//不是BMP图像						
	}	
											//位图信息头	结构体赋值			
	info_header = *(BITMAPINFOHEADER *)(pbuf + sizeof(BITMAPFILEHEADER));
	if(info_header.biHeight < 0)
	{
		info_header.biHeight = -info_header.biHeight;
	}
	f_lseek(&f_bmp, f_header.bfOffBits);	//读指针定位到位图数据起始处		
	
#if LCD_CHAR_HORIZONTAL > 0
	//竖屏显示
	LCD_WriteRegister(0x0003,0x1010);
	LCD_SetWindow(start_x, start_y, 		//设置GRAM绘图区域					
				   info_header.biWidth + start_x -1, 
				   info_header.biHeight + start_y - 1);
#else
	//横屏显示
	LCD_WriteRegister(0x0003,0x1028);
	LCD_SetWindow(start_x, start_y, 		//设置GRAM绘图区域					
				   info_header.biHeight + start_x -1, 
				   info_header.biWidth + start_y - 1);
#endif

	
	LCD_WriteGRAM_EN();							//开始绘图							
	switch(info_header.biBitCount)
	{
		case 4:
		case 8:
		case 16:
		{									//减去余数是为了能取2的整数倍		
			BMP_Read16Clr1(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		case 24:
		{									//减去余数是为了能取3的整数倍		
			BMP_Read24Clr(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		case 32:
		{
			BMP_Read32Clr(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		default:			
			break;
	}
	LCD_WR_END();							//完成绘图							
	LCD_SetWindow(0, 0, 239, 319);			//恢复全局作图区
#if LCD_CHAR_HORIZONTAL > 0
	//bmp为上下颠倒存储,恢复正常的显示顺序
	LCD_WriteRegister(0x0003,0x1030);
#else
	//bmp为上下颠倒存储,恢复正常的显示顺序
	LCD_WriteRegister(0x0003,0x1038);
#endif					
	f_close(&f_bmp);						//关闭文件							
	return 0;								//正常返回							
	
}

signed char BMP_Showbmp(unsigned int start_x,
			  			unsigned int start_y,
			  			const char *p_path)
{
	FIL f_bmp;
	FRESULT res;

	unsigned int br = 0;
	//unsigned char buffer[320*2*4];		//buffer的大小不要小于两个文件头的	
	u8*pbuf = (u8*)P_ImageBuf;					//大小，通常为54		
				
	BITMAPFILEHEADER f_header;
	BITMAPINFOHEADER info_header;
	
	res = f_open(&f_bmp, p_path, FA_OPEN_EXISTING | FA_READ);
	if(res)
	{
		return -1;							//打开失败则返回失败标志			
	}										//读一个缓冲区的数据				
	
	res = f_read(&f_bmp, pbuf, 512, &br);				
											//位图文件头	结构体赋值			
	f_header = *(BITMAPFILEHEADER *)pbuf;
	//memcpy(&f_header, buffer, sizeof(BITMAPFILEHEADER));
	if(f_header.bfType != 0x4d42)
	{
		return 1;							//不是BMP图像						
	}	
											//位图信息头	结构体赋值			
	info_header = *(BITMAPINFOHEADER *)(pbuf + sizeof(BITMAPFILEHEADER));
	if(info_header.biHeight < 0)
	{
		info_header.biHeight = -info_header.biHeight;
	}
	f_lseek(&f_bmp, f_header.bfOffBits);	//读指针定位到位图数据起始处		
	
#if LCD_CHAR_HORIZONTAL > 0
	//竖屏显示
	LCD_WriteRegister(0x0003,0x1010);
	LCD_SetWindow(start_x, start_y, 		//设置GRAM绘图区域					
				   info_header.biWidth + start_x -1, 
				   info_header.biHeight + start_y - 1);
#else
	//横屏显示
	LCD_WriteRegister(0x0003,0x1028);		//设置正反显示顺序
	LCD_SetWindow(start_x, start_y, 		//设置GRAM绘图区域					
				   115 + start_x, 
				   155 + start_y);
#endif

	
	LCD_WriteGRAM_EN();							//开始绘图							
	switch(info_header.biBitCount)
	{
		case 4:
		case 8:
		case 16:
		{									//减去余数是为了能取2的整数倍		
			BMP_Read16Clr(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		case 24:
		{									//减去余数是为了能取3的整数倍		
			BMP_Read24Clr(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		case 32:
		{
			BMP_Read32Clr(&f_bmp, &info_header, pbuf, IMAGE_BUFFER_SIZE);
			break;
		}
		default:			
			break;
	}
	LCD_WR_END();							//完成绘图							
	LCD_SetWindow(0, 0, 239, 319);			//恢复全局作图区
#if LCD_CHAR_HORIZONTAL > 0
	//bmp为上下颠倒存储,恢复正常的显示顺序
	LCD_WriteRegister(0x0003,0x1030);
#else
	//bmp为上下颠倒存储,恢复正常的显示顺序
	LCD_WriteRegister(0x0003,0x1038);
#endif					
	f_close(&f_bmp);						//关闭文件							
	return 0;								//正常返回							
	
}