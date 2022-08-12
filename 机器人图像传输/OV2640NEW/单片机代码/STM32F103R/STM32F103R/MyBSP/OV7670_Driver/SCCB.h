
/*

wangguanfu
2009-08-06

*/

#ifndef _SCCB_H
#define _SCCB_H

#include "stm32f10x.h"

#include"VARIABLE.h"


/*
#define SCCB_DDR		GPIOB->CRH
#define SCCB_PORT		GPIOB->ODR
#define SCCB_PIN		GPIOB->IDR

#define SCCB_SIO_C		14
#define SCCB_SIO_D		15

#define SIO_C_SET		{SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET		{SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_D);}

#define SIO_D_IN		{GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= 0x80000000; GPIOB->ODR |= 0x8000;}
#define SIO_D_OUT		{GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= 0x30000000; GPIOB->ODR |= 0x8000;}

#define SIO_D_STATE	((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))
*/



#define SCCB_DDR		GPIOB->CRL
#define SCCB_PORT		GPIOB->ODR
#define SCCB_PIN		GPIOB->IDR

#define SCCB_SIO_C		6
#define SCCB_SIO_D		7

#define SIO_C_SET		{SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET		{SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_D);}
/*
#define SIO_D_IN		{SCCB_DDR&=~(1<<SCCB_SIO_D);}
#define SIO_D_OUT		{SCCB_DDR|=(1<<SCCB_SIO_D);}
*/
#define SIO_D_IN		{GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= 0x80000000; GPIOB->ODR |= 0x0080;}
#define SIO_D_OUT		{GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= 0x30000000; GPIOB->ODR |= 0x0080;}

#define SIO_D_STATE	((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))
///////////////////////////////////////////
void DelaySCCB(void);
void InitSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
uchar SCCBwriteByte(uchar m_data);
uchar SCCBreadByte(void);


#endif /* _SCCB_H */


