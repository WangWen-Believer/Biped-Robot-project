#ifndef FlashDef_H
#define FlashDef_H

sbit FLASH_CS=    P1 ^ 7;
sbit FLASH_CLK=   P1 ^ 3;
sbit FLASH_IO0=   P1 ^ 2;
sbit FLASH_IO1=   P1 ^ 6;
sbit FLASH_IO2=   P1 ^ 5;
sbit FLASH_IO3=   P1 ^ 4;

sbit FLASH_WP=    P1 ^ 5;
sbit FLASH_HOLD=  P1 ^ 4;
sbit FLASH_DO  =  P1 ^ 6;
sbit FLASH_DIO  = P1 ^ 2;

#define W25P_FastReadData 0x0B

void IO_Send_Byte(uint8 dataout);

#endif
