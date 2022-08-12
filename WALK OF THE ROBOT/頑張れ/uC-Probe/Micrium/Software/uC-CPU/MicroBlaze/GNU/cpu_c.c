/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/CPU is provided in source form to registered licensees ONLY.  It is 
*                  illegal to distribute this source code to any third party unless you receive 
*                  written permission by an authorized Micrium representative.  Knowledge of 
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest 
*                  software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            CPU PORT FILE
*
*                                              Microblaze
*                                                 GNU
*
* Filename      : cpu_c.c
* Version       : V1.30.02.00
* Programmer(s) : NB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#include  <cpu.h>
#include  <cpu_core.h>

#ifdef __cplusplus
extern  "C" {
#endif


/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       CPU_FlushDCache()
*
* Description : Flush a specific range in the cache memory 
*
* Argument(s) :     addr    the start address of the memory area to flush
*                   len     the size of the memory area to flush
* 
* Return(s)   : none.
*
* Caller(s)   : Various.
*
* Note(s)     : The function uses microblaze_flush_dcache_range() which is part of Xilinx libraries  
*********************************************************************************************************
*/

void  CPU_CacheDataFlush (void       *addr, 
                          CPU_INT32U  len)
{
     microblaze_flush_dcache_range((CPU_INT32S)addr, len);           
}

/*
*********************************************************************************************************
*                                       CPU_InvalidateDCache()
*
* Description : Invalide a specific range in the cache memory
*
* Argument(s) :     addr    the start address of the memory area to invalidate
*                   len     the size of the memory area to invalidate
*
* Return(s)   : none.
*
* Caller(s)   : Various.
*
* Note(s)     : The function uses microblaze_invalidate_dcache_range() which is part of Xilinx libraries  
*********************************************************************************************************
*/
                                              
void  CPU_CacheDataInvalidate (void        *addr,
                               CPU_INT32U   len)
{
     microblaze_invalidate_dcache_range((CPU_INT32S)addr, len);                 
}

#ifdef __cplusplus
}
#endif

