#include "LCD_Driver.h"
#include "MyBspInc.h"
#include "OnChip_Driver_Inc.h"
////////////////////////////////////////////////////////////////////////////////
//数据输出，包括寄存器内容和GRAM数据内容			
//将用宏定义代替，说明：							
//  LCD_DATA_OUT()将一个16位数据输出到数据总线, 	
//被写寄存器和写GRAM(写像素点)的函数调用,移植时 	
//根据数据接口是8位或16位更改该函数(或称宏定义)		
////////////////////////////////////////////////////////////////////////////////
void LCD_DATA_OUT(u16 data)
{
#if LCD_8_BIT_EN		> 0
	//默认为8位数据端口写高8位			
	DATA_8BIT_OUT((u8)(data>>8));		
	LCD_WR_L;
	NOP();
	LCD_WR_H;
	
	//写低8位							
	DATA_8BIT_OUT((u8)data);	
	LCD_WR_L;
	NOP();
	LCD_WR_H;
#else
	//16位数据接口
	DATA_16BIT_OUT(data);
	LCD_WR_L;
	LCD_WR_H;
#endif
}
////////////////////////////////////////////////////////////////////////////////
//数据输入，包括寄存器内容和GRAM数据内容		 	
//说明:											 	
//  LCD_DATA_IN()将一个16位数据从数据总线上读取  	
//被读寄存器和读GRAM(读像素点)的函数调用,移植时  	
//根据数据接口是8位或16位更改该函数(可用内联函数)	
////////////////////////////////////////////////////////////////////////////////
u16 LCD_DATA_IN(void)
{
	u16 temp = 0;
#if LCD_8_BIT_EN		> 0
	GPIOC->CRL = 0x88888888;					//PC0-7  上拉输入
	LCD_RD_L;									//读有效	
	NOP();										//8位读时钟之间插入NOP()延时
	NOP();										
	LCD_RD_H;
	temp = DATA_8BIT_IN;						//读取高字节				
	
	LCD_RD_L;									//读有效	
	NOP();										//8位读时钟之间插入NOP()延时
	NOP();	
	LCD_RD_H;
	temp <<= 8;
	temp |= DATA_8BIT_IN;						//读取低字节					
	
	GPIOC->CRL = 0X33333333; //PC0-7  			//上拉输出
#else
	//置为输入
	GPIOC->CRL = 0x88888888; //PC0-7  上拉输入
	GPIOB->CRH = 0X88888888; // PB8-15上拉输入
	GPIOB->ODR |= 0XFF00;    //全部输出高
	GPIOC->ODR |= 0X00FF; 
	
	LCD_RD_L;									//读有效						
	LCD_RD_H;
	temp = DATA_16BIT_IN;	
	
	GPIOC->CRL = 0X33333333; //PC0-7  上拉输出
	GPIOB->CRH = 0X33333333; //PB8-15 上拉输出
	GPIOB->ODR |= 0XFF00;    //全部输出高
	GPIOC->ODR |= 0X00FF;
#endif
	return temp;
}
//写LCD缓存命令,视需要更改0x0022的值,一般LCD驱动
//IC都使用的该命令								
void LCD_WriteGRAM_EN(void)
{
	LCD_CS_L;									//选中片选						
	
	LCD_RS_L;									//命令读写控制RS->0有效			
	LCD_DATA_OUT(0x0022);						//写入寄存器地址				
	LCD_RS_H;
	//LCD_CS_H;//新添加
}
//读LCD缓存命令,视需要更改0x0022的值,一般LCD驱动
//IC都使用的该命令								
void LCD_ReadGRAM_EN(void)
{
	LCD_CS_L;									//选中片选						
	
	LCD_RS_L;									//命令读写控制RS->0有效			
	LCD_DATA_OUT(0x0022);						//写入寄存器地址				
	LCD_RS_H;
}
////////////////////////////////////////////////////////////////////////////////
//  LCD_SetCursor ->设置读写指针				
//  该函数在移植时视需要修改,一般驱动IC使用了20H
//和21H分别设置GARM的x和y地址					
////////////////////////////////////////////////////////////////////////////////
void LCD_SetCursor(u16 x,u16 y)
{	//													   	*-------->x			
  	LCD_WriteRegister(0x0020, x); // 行				   		|		(H 127)		
  	LCD_WriteRegister(0x0021, y); // 列				   		|					
	///////////////////////////////							|					
	//R61514屏没有20H寄存器，xy坐标通过21H寄存器转化	   	|					
	//完成，公式:y*256 + x,参见手册R21H寄存器描述		   	V(V 159)			
# if R61514_EN 		> 0		
	LCD_WriteRegister(0x0021,(y << 8) + x);
# endif
}

////////////////////////////////////////////////////////////////////////////////
//  LCD_WriteRegister()->写寄存器												
//  写寄存器,LCD i80接口标准,RS为低时写寄存器IR	
//(寄存器指针),将index的值赋给他;RS为高时写数据,
//将data的值赋给IR指向的寄存器,该函数是i80接口上
//层应用,移植时不用修改							
////////////////////////////////////////////////////////////////////////////////
void LCD_WriteRegister(u16 index, u16 data)
{
////////////////////////////////////////////////////////////////////////////////
  	// 对于8位模式,则数据端口要进行两次操作，下图是16位模式情况下的操作   //
  	// nCS       ----\__________________________________________/-------  //
  	// RS        ------\____________/-----------------------------------  //
  	// nRD       -------------------------------------------------------  //
  	// nWR       --------\_______/--------\_____/-----------------------  //
  	// DB[0:15]  ---------[index]----------[data]-----------------------  //
  	//                                                                    //
////////////////////////////////////////////////////////////////////////////////
	LCD_CS_L;									//选中片选						
	
	LCD_RS_L;									//命令读写控制RS->0有效			
	LCD_DATA_OUT(index);						//先写入寄存器地址				
	
	LCD_RS_H;									//数据读写控制RS->1有效			
	LCD_DATA_OUT(data);
	
	LCD_CS_H;									//关闭片选						
}

////////////////////////////////////////////////////////////////////////////////
//  LCD_ReadRegister()->读寄存器												
//  读寄存器,LCD i80接口标准,RS为低时写寄存器IR	
//(寄存器指针),将index的值赋给他;RS为高时读数据,
//将data的值赋给IR指向的寄存器,该函数是i80接口上
//层应用,移植时不用修改							
////////////////////////////////////////////////////////////////////////////////
u16 LCD_ReadRegister(u16 index)
{
////////////////////////////////////////////////////////////////////////////////
  	// 对于8位模式,则数据端口要进行两次操作，下图是16位模式情况下的操作   //
  	// nCS       ----\__________________________________________/-------  //
  	// RS        ------\____________/-----------------------------------  //
  	// nRD       -------------------------\_____/-----------------------  //
  	// nWR       --------\_______/--------------------------------------  //
  	// DB[0:15]  ---------[index]----------[data]-----------------------  //
  	//                                                                    //
////////////////////////////////////////////////////////////////////////////////
	u16 temp = 0;
  	LCD_CS_L;									//选中片选						
	
	LCD_RS_L;									//命令读写控制RS->0有效			
	LCD_DATA_OUT(index);						//写入寄存器地址				
	
	LCD_RS_H;									//数据读写控制RS->1有效			
	temp = LCD_DATA_IN();
	LCD_CS_H;									//关闭片选						
	return temp;
}

////////////////////////////////////////////////////////////////////////////////
//  LCD_DrawPoint()->画点函数					
//  该函数先设置GARM地址,然后发送写命令,接着再将
//color的值赋给GRAM中对应的地址.该函数是上层应用
//移植时不用修改								
////////////////////////////////////////////////////////////////////////////////
void LCD_DrawPoint(u16 x, u16 y, u16 color)
{
	if ((x > X_END) || (y > Y_END)) 			//显示不能超过最大坐标值		
	{
		return;
	}
	LCD_SetCursor(x, y);
	
	LCD_WriteGRAM_EN();
	LCD_DATA_OUT(color);
	LCD_WR_END();
}
////////////////////////////////////////////////////////////////////////////////
//  LCD_GetPoint()->读点函数					
//  该函数先设置GARM地址,然后发送写命令,接着是一
//个哑操作,该哑操作根据8位或16位接口需要更改宏定
//义.该函数是上层应用移植时不用修改				
////////////////////////////////////////////////////////////////////////////////
u16 LCD_GetPoint(u16 x, u16 y)
{
////////////////////////////////////////////////////////////////////////////////
  	// 对于8位模式,则数据端口要进行两次操作，下图是16位模式情况下的操作   //
  	// nCS       ----\__________________________________________/-------  //
  	// RS        ------\____________/-----------------------------------  //
  	// nRD       -------------------------\_____/------\_____/----------  //
  	// nWR       --------\_______/--------------------------------------  //
  	// DB[0:15]  ---------[Address]-------[Dummy]-------[data]----------  //
  	// 注意:在读GRAM时,要先设置读地址，再写读命令，然后是Dummy Read，最后 //
	//      才是数据。同时，在8位模式下，Dummy Read 是一个Word的时间，意味//
	//		着RD要产生2次上升沿，最后读回来的数据还要进行转换			  //
////////////////////////////////////////////////////////////////////////////////
	u16 temp_color = 0;
  	u16 temp = 0;
  	
	LCD_SetCursor(x,y);
  	
	LCD_ReadGRAM_EN();
	
	DUMMY_READ();						//第一次不读							
	temp_color = LCD_DATA_IN();
	
	LCD_WR_END();
										
	temp = temp_color >> 11;			//RRRRRGGGGGGBBBBB 改为 				
	temp |= temp_color << 11;			//BBBBBGGGGGGRRRRR 格式					
	temp |= (temp_color & 0x07E0);		//0000011111100000  = 0x07E0			
  	
	return temp;
}
////////////////////////////////////////////////////////////////////////////////
//  LCD_SetWindow()->设置GRAM窗口				
//  该函数对于块写很有用,用户只需设置好块写区域 
//然后依次给设置GRAM区域写数据即可,GC指针会自动 
//增加而无需用户更改,这样就提高了写效率.读数据时
//GC不会自动增加(GC->GRAM Counter)				
////////////////////////////////////////////////////////////////////////////////
void LCD_SetWindow(u16 start_x,u16 start_y,
					u16 end_x,u16 end_y)
{ 
  		
  	LCD_WriteRegister(0x0050, start_x);	
  	LCD_WriteRegister(0x0052, start_y);	
  	LCD_WriteRegister(0x0051, end_x);		
  	LCD_WriteRegister(0x0053, end_y);	 
	 	
	//驱动ICR61514->设置GARM地址			
  	////////////////////////////////////////
# if R61514_EN		> 0
	end_x <<= 8;					//高8位是垂直结束地址						
  	end_x |= (unsigned char)start_x;//低8位是垂直开始地址(水平GRAM地址也是如此 )
  	end_y <<= 8;
  	end_y |= (unsigned char)start_y;
	
  	LCD_WriteRegister(0x0044, end_x);
  	LCD_WriteRegister(0x0045, end_y);
# endif
	LCD_SetCursor(start_x, start_y);//设置起始绘图的GRAM地址					
	
}
//LCD清屏函数							
void LCD_Clear(u16 color)
{
	unsigned long  i;
	LCD_SetWindow(0, 0, X_END, Y_END);
	LCD_WriteGRAM_EN();
	for(i=0; i< X_SIZE*Y_SIZE; i++)		//R61514为128*160						
  	{
    	LCD_CS_L;
		LCD_DATA_OUT(color);
		LCD_CS_H;
  	}
	LCD_WR_END();
	
	LCD_SetWindow(0,0, X_END, Y_END);	//恢复全局作图区						
}
//填充一个矩形区域						
void LCD_Fill(u16 start_x,u16 start_y,
			  u16 end_x,u16 end_y,
			  u16 color)
{
	unsigned long  i;

	LCD_SetWindow(start_x, start_y, end_x, end_y);
	
	LCD_WriteGRAM_EN();
	for(i=0; i < (end_x - start_x + 1)*(end_y - start_y + 1); i++)				
  	{
    	LCD_DATA_OUT(color);			//填充颜色								
  	}
	LCD_WR_END();
	
	LCD_SetWindow(0,0, X_END, Y_END);	//恢复全局作图区						
}
//液晶端口初始化,外部无需调用			
void LCD_PortInit(void)
{
	//控制端口方向初始化,移植时只需更改有关宏定义
	/*LCD_CS_DDR |= BIT(LCD_CS_BIT);
	LCD_RS_DDR |= BIT(LCD_RS_BIT);
	LCD_WR_DDR |= BIT(LCD_WR_BIT);
	LCD_RD_DDR |= BIT(LCD_RD_BIT);
	LCD_REST_DDR |= BIT(LCD_REST_BIT);*/
	//控制端口电平初始化						
	/*LCD_CS_H;
	LCD_RS_H;
	LCD_WR_H;
	LCD_RD_H;
	LCD_REST_H;*/
	//数据总线端口方向初始化,视接口需要更改或添加
	
	//DATA_L_DDR = 0xff;
	//DATA_L_PORT = 0xff;
	
	RCC->APB2ENR|=1<<3;//先使能外设PORTB时钟
 	RCC->APB2ENR|=1<<4;//先使能外设PORTC时钟

											 
	//PORTC0~13推挽输出 	
	GPIOC->CRL=0x33333333;
	GPIOC->CRH&=0xFF000000;
	GPIOC->CRH|=0x00333333;
	GPIOC->ODR|=0x3FFF;	
	//PORTB 高8位推挽输出 
#if LCD_8_BIT_EN		> 0
	
#else
	GPIOB->CRH=0x33333333;
	GPIOB->ODR|=0xFF00;
#endif

}
//液晶驱动初始化						
void LCD_DriverInit(void)
{
	unsigned short int lcd_id = 0x0000;		//保存LCD_ID号							
	LCD_PortInit();						//调用端口初始化						
				
    SET_PORT_H(LCD_LED_PORT, LCD_LED_BIT);//开背光
	LCD_REST_L;							//复位控制								
	Delay_nMS(1);	
    LCD_REST_H;
	Delay_nMS(1);						//完成复位											
	LCD_WriteRegister(0x0000, 0x0001);	//开启时钟								
	Delay_nMS(10);
	lcd_id = LCD_ReadRegister(0x0000);	//读取LCD_ID							
	lcd_id = 0x9325;
	while(0)
	{
		UART_Transmit(lcd_id >> 8);
		UART_Transmit(lcd_id);
		Delay_nMS(500);
	}
	switch(lcd_id)
	{
		//R61514
		case 0x1514:					//R61514S驱动IC							
		LCD_WriteRegister(0x0007, 0x0000);
		Delay_nMS(2);
		LCD_WriteRegister(0x0017, 0x0001);
		LCD_WriteRegister(0x0010, 0x4410);
		LCD_WriteRegister(0x0011, 0x0000);
		LCD_WriteRegister(0x0012, 0x0118);
		LCD_WriteRegister(0x0013, 0x0d23);
		Delay_nMS(2);
		LCD_WriteRegister(0x0010, 0x4490);
		LCD_WriteRegister(0x0011, 0x0000);
		LCD_WriteRegister(0x0012, 0x013d);
		Delay_nMS(2);
		LCD_WriteRegister(0x0001, 0x0213);
		LCD_WriteRegister(0x0003, 0x1030);	//0x1030,设置接口方式,颜色位数和扫描方向
		LCD_WriteRegister(0x0007, 0x0005);
		LCD_WriteRegister(0x0008, 0x0603);
		LCD_WriteRegister(0x0009, 0x002f);
		LCD_WriteRegister(0x000b, 0x8000);
	
		LCD_WriteRegister(0x0040, 0x0000);
		LCD_WriteRegister(0x0041, 0x0000);
		LCD_WriteRegister(0x0042, 0x9f00);
		LCD_WriteRegister(0x0043, 0x9f00);
		LCD_WriteRegister(0x0044, 0x7f00);	//水平窗口起始大小(高8位HEA[结束地址],低8位HSA[起始地址])
		LCD_WriteRegister(0x0045, 0x9f00);	//垂直窗口起始大小(高8位VEA[结束地址],低8位VSA[起始地址])
		LCD_WriteRegister(0x0021, 0x0000);	//GRAM起始坐标点										 
		
		LCD_WriteRegister(0x0030, 0x0103);
		LCD_WriteRegister(0x0031, 0x0001);
		LCD_WriteRegister(0x0032, 0x0304);
		LCD_WriteRegister(0x0033, 0x0204);
		LCD_WriteRegister(0x0034, 0x0406);
		LCD_WriteRegister(0x0035, 0x0707);
		LCD_WriteRegister(0x0036, 0x0407);
		LCD_WriteRegister(0x0037, 0x0303);
		LCD_WriteRegister(0x0038, 0x0403);
		LCD_WriteRegister(0x0039, 0x0102);
		Delay_nMS(1);
											//-----Display On-------------------
		LCD_WriteRegister(0x0002, 0x0600);
		LCD_WriteRegister(0x0007, 0x0015);
		Delay_nMS(1);
		LCD_WriteRegister(0x0007, 0x0055);
		Delay_nMS(1);
		LCD_WriteRegister(0x0002, 0x0700);
		LCD_WriteRegister(0x0007, 0x0077);
		
		break;								//完成初始化						
		//ILI9320与ILI9328
		case 0x9325:
		case 0x9328:
		case 0xD325:
	//************* Start Initial Sequence **********// 
        LCD_WriteRegister(0x0001, 0x0100);        // set SS and SM bit 
        LCD_WriteRegister(0x0002, 0x0700);        // set 1 line inversion 
        #if LCD_CHAR_HORIZONTAL > 0
		//字符正放(竖屏),即X->240,CHAR_X->8 
        LCD_WriteRegister(0x0003,0x1010);//65K    ,8位模式下两次传输,16位模式下1次传输,BIT[7]OGR为0时系统坐标固定,(H->x:0-219,V->y:0-319)
		#else
		//字符顺时针旋转90度(横屏),即X->240,CHAR_X->16
		LCD_WriteRegister(0x0003,0x1038);	
		#endif 
        LCD_WriteRegister(0x0004, 0x0000);        // Resize register 
        LCD_WriteRegister(0x0008, 0x0207);        // set the back porch and front porch 
        LCD_WriteRegister(0x0009, 0x0000);        // set non-display area refresh cycle ISC[3:0] 
        LCD_WriteRegister(0x000A, 0x0000);        // FMARK function 
        LCD_WriteRegister(0x000C, 0x0000);        // RGB interface setting 
        LCD_WriteRegister(0x000D, 0x0000);        // Frame marker Position 
        LCD_WriteRegister(0x000F, 0x0000);          // RGB interface polarity 
    //*************Power On sequence ****************// 
        LCD_WriteRegister(0x0010, 0x0000);            // SAP, BT[3:0], AP, DSTB, SLP, STB 
        LCD_WriteRegister(0x0011, 0x0007);            // DC1[2:0], DC0[2:0], VC[2:0] 
        LCD_WriteRegister(0x0012, 0x0000);            // VREG1OUT voltage 
        LCD_WriteRegister(0x0013, 0x0000);            // VDV[4:0] for VCOM amplitude 
    	LCD_WriteRegister(0x0007, 0x0001);       
            Delay_nMS(200);                                                        // Dis-charge capacitor power voltage 
        LCD_WriteRegister(0x0010, 0x1290);            // SAP, BT[3:0], AP, DSTB, SLP, STB 
        LCD_WriteRegister(0x0011, 0x0227);            // DC1[2:0], DC0[2:0], VC[2:0] 
            Delay_nMS(50);                                             // Delay 50ms     
        LCD_WriteRegister(0x0012, 0x001A);            // Internal reference voltage= Vci; 
            Delay_nMS(50);                                             // Delay 50ms 
        LCD_WriteRegister(0x0013, 0x1800);            // Set VDV[4:0] for VCOM amplitude 
        LCD_WriteRegister(0x0029, 0x0028);            // Set VCM[5:0] for VCOMH 
        LCD_WriteRegister(0x002B, 0x000C);            // Set Frame Rate   
            Delay_nMS(50);                                                            // Delay 50ms 
        LCD_WriteRegister(0x0020, 0x0000);            // GRAM horizontal Address 
        LCD_WriteRegister(0x0021, 0x0000);            // GRAM Vertical Address   
    // ----------- Adjust the Gamma    Curve ----------// 
        LCD_WriteRegister(0x0030, 0x0000); 
        LCD_WriteRegister(0x0031, 0x0305); 
        LCD_WriteRegister(0x0032, 0x0003); 
        LCD_WriteRegister(0x0035, 0x0304); 
        LCD_WriteRegister(0x0036, 0x000F); 
        LCD_WriteRegister(0x0037, 0x0407); 
        LCD_WriteRegister(0x0038, 0x0204); 
        LCD_WriteRegister(0x0039, 0x0707); 
        LCD_WriteRegister(0x003C, 0x0403); 
        LCD_WriteRegister(0x003D, 0x1604); 
    	//------------------ Set GRAM area ---------------// 
        LCD_WriteRegister(0x0050, 0x0000);          // Horizontal GRAM Start Address 
        LCD_WriteRegister(0x0051, 0x00EF);          // Horizontal GRAM End Address 
        LCD_WriteRegister(0x0052, 0x0000);          // Vertical GRAM Start Address 
        LCD_WriteRegister(0x0053, 0x013F);          // Vertical GRAM Start Address 
		LCD_WriteRegister(0x0060, 0xA700);          // Gate Scan Line 
        LCD_WriteRegister(0x0061, 0x0001);          // NDL,VLE, REV 
        LCD_WriteRegister(0x006A, 0x0000);          // set scrolling line 
    	//-------------- Partial Display Control ---------// 
        LCD_WriteRegister(0x0080, 0x0000); 
        LCD_WriteRegister(0x0081, 0x0000); 
        LCD_WriteRegister(0x0082, 0x0000); 
        LCD_WriteRegister(0x0083, 0x0000); 
        LCD_WriteRegister(0x0084, 0x0000); 
        LCD_WriteRegister(0x0085, 0x0000); 
    	//-------------- Panel Control -------------------// 
        LCD_WriteRegister(0x0090, 0x0010); 
        LCD_WriteRegister(0x0092, 0x0600); 
       
        LCD_WriteRegister(0x0007, 0x0133);          // 262K color and display ON 
		break;
		//ILI9320与ILI9300
		
		case 0x9320:
		case 0x9300:
		LCD_WriteRegister(0x00,0x0000);
		LCD_WriteRegister(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteRegister(0x02,0x0700);	//LCD Driver Waveform Contral.
	#if LCD_CHAR_HORIZONTAL > 0
		//字符正放(竖屏),即X->240,CHAR_X->8 
        LCD_WriteRegister(0x0003,0x1010);//65K    ,8位模式下两次传输,16位模式下1次传输,BIT[7]OGR为0时系统坐标固定,(H->x:0-219,V->y:0-319)
	#else
		//字符顺时针旋转90度(横屏),即X->240,CHAR_X->16
		LCD_WriteRegister(0x0003,0x1038);	
	#endif
		LCD_WriteRegister(0x04,0x0000);	//Scalling Contral.
		LCD_WriteRegister(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteRegister(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteRegister(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteRegister(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteRegister(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteRegister(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		Delay_nMS(5); 
		LCD_WriteRegister(0x07,0x0101);	//Display Contral.
		Delay_nMS(5); 								  
		LCD_WriteRegister(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteRegister(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteRegister(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		LCD_WriteRegister(0x13,0x0b00);								//Power Control 4.
		LCD_WriteRegister(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteRegister(0x2b,(1<<14)|(1<<4));	    
		LCD_WriteRegister(0x50,0);	//Set X Star
		//水平GRAM终止位置Set X End.
		LCD_WriteRegister(0x51,239);	//Set Y Star
		LCD_WriteRegister(0x52,0);	//Set Y End.t.
		LCD_WriteRegister(0x53,319);	//
	
		LCD_WriteRegister(0x60,0x2700);	//Driver Output Control.
		LCD_WriteRegister(0x61,0x0001);	//Driver Output Control.
		LCD_WriteRegister(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WriteRegister(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WriteRegister(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WriteRegister(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WriteRegister(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WriteRegister(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WriteRegister(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WriteRegister(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WriteRegister(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WriteRegister(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WriteRegister(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WriteRegister(0x97,(0<<8));	//
		LCD_WriteRegister(0x98,0x0000);	//Frame Cycle Contral.	   
		LCD_WriteRegister(0x07,0x0173);	//(0x0173)
		break;
	}
	
}
