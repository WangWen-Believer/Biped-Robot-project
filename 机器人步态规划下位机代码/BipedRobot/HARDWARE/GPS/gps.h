#ifndef _GPS_H
#define _GPS_H
#endif
#include "sys.h"
extern uint8_t Hour,Min,Sec,Day,Mouth,Year,GPS_VA,weidu_dir,jingdu_dir,star_num,star_num_t,star_run[12],GPS_3D;
extern float jingdu,weidu;
extern u16 star_info[12][4],star_info_t[12][4],GPS_ATLI;
void GPRMC_DAT(void);
void GPGSV_DAT(void);
void GPGSA_DAT(void);
void GPGGA_DAT(void);
extern uint8_t TxBuffer1[400]; 
extern uint8_t Rec_Len;


