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
*                                               Nios II
*                                            GNU C Compiler
*
* Filename      : cpu_c.c
* Version       : V1.30.02.00
* Programmer(s) : MG
*                 JJL
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
*                                            CPU_SR_Save()
*
* Description : This function disables interrupts for critical sections of code.
*
* Argument(s) : none.
*
* Return(s)   : The CPU's status register, so that interrupts can later be returned to their original
*               state.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_SR  CPU_SR_Save (void)
{
    return (alt_irq_disable_all());
}


/*
*********************************************************************************************************
*                                          CPU_SR_Restore()
*
* Description : Restores interrupts after critical sections of code.
*
* Argument(s) : cpu_sr    The interrupt status that will be restored.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  CPU_SR_Restore (CPU_SR  cpu_sr)
{
    alt_irq_enable_all(cpu_sr);
}

#ifdef __cplusplus
}
#endif
