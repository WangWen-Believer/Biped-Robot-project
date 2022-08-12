#ifndef LCD_GUI_H_H_
#define LCD_GUI_H_H_
#include "stm32f10x.h"

#ifndef _BIT
#define _BIT
#define BIT(n)				(1 << (n))
#endif
////////////////////////////////////////
void LCD_WriteMenuChar(unsigned int start_x, unsigned int start_y,
				   	   unsigned int char_clr,
				       unsigned int bk_clr,
				       unsigned char char_data
					   );
void LCD_WriteString(unsigned char Start_X, unsigned char Start_Y,
					unsigned int Char_Clr,
				    unsigned int Bk_Clr,
					unsigned char *p_str,
					unsigned char is_transp);
void LCD_WriteChar(unsigned int Start_X, unsigned int Start_Y,
				   	unsigned int Char_Clr,
				    unsigned int Bk_Clr,
				    unsigned char ch_Char);
void LCD_Print(const unsigned char *p_str);
unsigned char Get_CharOffset(unsigned char char_data);
void Set_CharWindow(unsigned int Start_X, unsigned int Start_Y);
void LCD_WriteHexNumber(u16 x, u16 y, unsigned long data, unsigned char is_cap);
void LCD_WriteNumber(unsigned long data, unsigned char ch_Dot);
# endif
