/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

// Inidialize a Drive				
# include "integer.h"
# include "sd_driver.h"
# include "diskio.h"
struct tm {
   	int tm_sec;   						// 秒 seconds after the minute, 0 to 60	
   	int tm_min;   						// 分 minutes after the hour, 0 to 59	
	int tm_hour;  						// 时 hours since midnight, 0 to 23*	
	int tm_mday;  						// 日 day of the month, 1 to 31			
	int tm_mon;   						// 月 months since January, 0 to 11		
	int tm_year; 	 					// 年 years since 1900					
	int tm_wday;  						// 星期 days since Sunday, 0 to 6		
	int tm_yday;  						// 从元旦起的天数 0 to 365				
 	int tm_isdst; 						// 夏令时？？Daylight Savings Time flag	
};

#define SD_DISK		0
DSTATUS disk_initialize (
	BYTE drv
)
{
	switch (drv) 
	{
		case SD_DISK:
			return SD_Init();
		//////////////////////////////////////////////
		//Insert other disk's initialize here		//
		//case OTHER_DISK:							//
		//	return Other_Disk_Init();				//
		//////////////////////////////////////////////
	}
	return RES_PARERR;
}



DSTATUS disk_status (
	BYTE drv
)
{
	switch (drv) 
	{
		case SD_DISK:
			return SD_Status();
		//////////////////////////////////////////////
		//Insert other disk's status here			//
		//case OTHER_DISK:							//
		//	return Other_Disk_Status();				//
		//////////////////////////////////////////////

	}
	return RES_PARERR;
}



DRESULT disk_read (
	BYTE drv,
	BYTE* buff,
	DWORD lba,
	BYTE count
)
{
	switch (drv) 
	{
		case SD_DISK:
			return SD_Read(buff, lba, count);
		//////////////////////////////////////////////
		//Insert other disk's Read here			//
		//case OTHER_DISK:							//
		//	return Other_Disk_Read();				//
		//////////////////////////////////////////////
	}
	return RES_PARERR;
}



DRESULT disk_write (
	BYTE drv,
	const BYTE* buff,
	DWORD lba,
	BYTE count
)
{
	switch (drv) 
	{
		case SD_DISK:
			return SD_Write(buff, lba, count);
		//////////////////////////////////////////////
		//Insert other disk's write here			//
		//case OTHER_DISK:							//
		//	return Other_Disk_Write();				//
		//////////////////////////////////////////////
	}
	return RES_PARERR;
}



DRESULT disk_ioctl (
	BYTE drv,
	BYTE cmd,
	void* buff
)
{
	switch (drv) 
	{
		case SD_DISK:
			return SD_Ioctl(cmd, buff);
		//////////////////////////////////////////////
		//Insert other disk's Ioctl here			//
		//case OTHER_DISK:							//
		//	return Other_Disk_Ioctl();				//
		//////////////////////////////////////////////
	}
	return RES_PARERR;
}



/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */

DWORD get_fattime (void)
{
	/*   struct tm t;
    DWORD date;
    t.tm_year=2009-1980;	
    t.tm_mon=8;         	
	t.tm_mday=3;
	t.tm_hour=15;
	t.tm_min=30;
    t.tm_sec=20;      
	date =t.tm_year;
	date=date<<7;
	date+=t.tm_mon;
	date=date<<4;
	date+=t.tm_mday;
	date=date<<5;
	date+=t.tm_hour;
	date=date<<5;
	date+=t.tm_min;
	date=date<<5;
	date+=t.tm_sec;
	date=1950466004;
*/
    return 1950466005;
}


