/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
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
*                                                 ARM
*                                            IAR C Compiler
*
* Filename      : cpu_c.c
* Version       : V1.30.02.00
* Programmer(s) : FT
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

#include  <lib_def.h>

#ifdef __cplusplus
extern  "C" {
#endif


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         CPU_CntLeadZeros()
*
* Description : Counts the number of contiguous, most-significant, leading zero bits before the 
*                   first binary one bit in a data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is an INTERNAL CPU module function but MAY be called by application 
*               function(s).
*
* Note(s)     : (1) (a) Supports 32-bit data value size as configured by 'CPU_DATA' (see 'cpu.h  
*                       CPU WORD CONFIGURATION  Note #1').
*
*                   (b) For 32-bit values :
*
*                             b31  b30  b29  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                             ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                              1    x    x         x    x    x    x    x            0
*                              0    1    x         x    x    x    x    x            1
*                              0    0    1         x    x    x    x    x            2
*                              :    :    :         :    :    :    :    :            :
*                              :    :    :         :    :    :    :    :            :
*                              0    0    0         1    x    x    x    x           27
*                              0    0    0         0    1    x    x    x           28
*                              0    0    0         0    0    1    x    x           29
*                              0    0    0         0    0    0    1    x           30
*                              0    0    0         0    0    0    0    1           31
*                              0    0    0         0    0    0    0    0           32
*
*
*               (2) MUST be defined in 'cpu_a.asm' (or 'cpu_c.c') if CPU_CFG_LEAD_ZEROS_ASM_PRESENT 
*                   is #define'd in 'cpu_cfg.h' or 'cpu.h'.
*********************************************************************************************************
*/

#ifdef   CPU_CFG_LEAD_ZEROS_ASM_PRESENT
CPU_DATA  CPU_CntLeadZeros (CPU_DATA  val)
{
    CPU_DATA  cnt = 0u;

    asm("CLZ %0, %1" : "=r"(cnt) : "r" (val));

    return (cnt);
}
#endif

#ifdef __cplusplus
}
#endif
