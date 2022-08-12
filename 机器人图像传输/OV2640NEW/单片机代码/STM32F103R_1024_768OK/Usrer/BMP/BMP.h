#ifndef BMP_H_H_
#define BMP_H_H_

#include "../fatfs/FATFS_008.h"

#include "stm32f10x.h"

#define RGB555		0
#define RGB565		1

//第一部分为位图文件头BITMAPFILEHEADER,			
//是一个结构，其定义如下：						
//这个结构的长度是固定的，为14个字节			
//WORD为无符号16位整数，DWORD为无符号32位整数）	
#pragma pack (1)		//以下三个机构体均按1字节对齐
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;  		//0x00~0x01//指定文件类型，通常为0x424D，即字符串"BM"	
	DWORD bfSize;  		//0x02~0x05//指定文件大小，包括这14个字节				
	
	WORD bfReserved1; 	//0x06~0x07//为保留字，不用考虑							
	WORD bfReserved2; 	//0x08~0x09//为保留字，不用考虑							

	DWORD bfOffBits; 	//0x0a~0x0d//为从文件头到实际的位图数据的偏移字节数，	
						//即前三个部分的长度之和								
} BITMAPFILEHEADER;

//__attribute__ ((packed)) 
//第二部分为位图信息头BITMAPINFOHEADER，也是一个
//结构体，其定义如下：							
//绝大多数的BMP图像都是 BITMAPINFOHEADER结构的	
//即长度为为40个字节（WORD为无符号16位整数，	
//DWORD无符号32位整数,LONG为32位整数）			
typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; 	 	//0x0e~0x11//说明BITMAPINFOHEADER结构所需要的字节数(40)	

	LONG biWidth;  		//0x12~0x15//指定图象的宽度，单位是象素					
	LONG biHeight;  	//0x16~0x9//指定图象的高度，单位是象素					

	WORD biPlanes;  	//0x1a~0xb//为目标设备说明位面数，其值将总是被设为1		

	WORD biBitCount; 	//0x1c~0x0d//指定颜色位数,为1(2色图),4(16色),8(256色)	
						//		   16(高彩色),24(真彩色图),32(增强型真彩色位图)	
	DWORD biCompression;//0x1e~0x21//压缩说明： 								
# define BI_RGB			0x00	//0 - 不压缩 (使用BI_RGB表示) 	
# define BI_RLEB		0x01	//1 - RLE 8-使用8位RLE压缩方式(用BI_RLE8表示) 	
# define BI_RLE4		0x02	//2 - RLE 4-使用4位RLE压缩方式(用BI_RLE4表示) 	
# define BI_BITFIELDS	0x03	//3 - Bitfields-位域存放方式(用BI_BITFIELDS表示)
	DWORD biSizeImage; 	//0x22~0x25//指定实际的位图数据占用的字节数其实也可以从以下的公式中计算出来：biSizeImage=biWidth'*biHeight要注意的是：上述公式中的biWidth'必须是4的整倍数（所以不是biWidth，而是biWidth'，表示大于或等于biWidth的，离4最近的 整倍数。举个例子，如果biWidth=240，则biWidth'=240；如果biWidth=241，biWidth'=244）如果 biCompression为BI_RGB，则该项可能为零
						
	LONG biXPelsPerMeter; //0x26~0x29//指定目标设备的水平分辨率，单位是每米的象素个数
	LONG biYPelsPerMeter; //0x2a~0x2d//指定目标设备的垂直分辨率，单位同上。		

	DWORD biClrUsed; 	  //0x2e~0x31//指定本图象实际用到的颜色数，如果该值为零，则用到的颜色数为2的biBitCount次方。
	DWORD biClrImportant; //0x32~0x35//指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。
}BITMAPINFOHEADER; 
	
//第三部分为调色板(Palette),当然,这里是对那些需	
//要调色板的位图文件而言的。有些位图，如真彩色图
//是不需要调色板的,BITMAPINFOHEADER后直接是位图	
//数据。										
//调色板实际上是一个数组，共有biClrUsed个元素	
//(如果该值为零，则有2的biBitCount次方个元素)	
//数组中每个元素的类型是一个RGBQUAD结构，占4个字
//节，其定义如下：								
typedef struct tagRGBQUAD{
	BYTE rgbBlue;  					//该颜色的蓝色分量							
	BYTE rgbGreen;  				//该颜色的绿色分量							
	BYTE rgbRed;  					//该颜色的红色分量							
	BYTE rgbReserved; 				//保留值									
}RGBQUAD;
#pragma pack () 
//第四部分就是实际的图象数据了。对于用到调色板的位图，图象数据就是该像素颜在调色
//板中的索引值，对于真彩色图，图象数据就是实际的R,G,B值。						
//要注意两点：																	
//1．每一行的字节数必须是4的整倍数，如果不是，则需要补齐。这在前面介绍			
//	 biSizeImage时已经提到了。													
//2．一般来说，.BMP文件的数据从下到上，从左到右的。也就是说，从文件中最先读到的	
//是图象最下面一行的左边第一个像素，然后是左边第二个像素…接下来是倒数第二行左边
//第一个像素，左边第二个像素…依次类推，最后得到的是最上面一行的最右一个像素。
	
//4宫格显示
signed char BMP_Showbmp(unsigned int start_x,
			  			unsigned int start_y,
			  			const char *p_path);
//大图显示
signed char BMP_Showbmp1(unsigned int start_x,
			  			unsigned int start_y,
			  			const char *p_path);
void BMP_Read16Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size);
void BMP_Read24Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size);
void BMP_Read32Clr(FIL *p_fbmp, BITMAPINFOHEADER *p_iheader, 
				   unsigned char *p_buf, unsigned int buf_size);
				   
//写BMP								
void BMP_bmpInit(long bmp_width,
				 long bmp_height,
				 unsigned int bmp_bitcount,
				 BITMAPFILEHEADER *p_fheader, BITMAPINFOHEADER *p_info_header,
				 u8 bmp_type);					
u32 BMP_MakeBmpFile(long bmp_width, 
					long bmp_height,
					FIL* p_bmp,
					const char *p_path,
					u8 bmp_type);
u8 BMP_FillBmp(FIL* p_bmp,
				 u32 fill_size,
				 void* p_buf,
				 u32 buf_size);
# endif
