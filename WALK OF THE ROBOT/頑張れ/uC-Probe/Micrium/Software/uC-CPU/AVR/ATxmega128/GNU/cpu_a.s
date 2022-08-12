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
*                                           Atmel ATxmega128
*                                            GNU C Compiler
*
* Filename      : cpu_a.s
* Version       : V1.30.02.00
* Programmer(s) : FGK
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             ASM HEADER
*********************************************************************************************************
*/

        .text


/*
*********************************************************************************************************
*                                              DEFINES
*********************************************************************************************************
*/

        .equ SREG, 0x3F                                         /* Status  Register                                     */


/*
*********************************************************************************************************
*                                          PUBLIC DECLARATIONS
*********************************************************************************************************
*/

        .global CPU_SR_Save
        .global CPU_SR_Restore


/*
*********************************************************************************************************
*                            DISABLE/ENABLE INTERRUPTS USING OS_CRITICAL_METHOD #3
*
* Description : These functions are used to disable and enable interrupts using OS_CRITICAL_METHOD #3.
*
*               CPU_SR  CPU_SR_Save (void)
*                     Get current value of SREG
*                     Disable interrupts
*                     Return original value of SREG
*
*               void  CPU_SR_Restore (OS_CPU_SR cpu_sr)
*                     Set SREG to cpu_sr
*                     Return
*********************************************************************************************************
*/

CPU_SR_Save:
        IN      R16,SREG                                        /* Get current state of interrupts disable flag         */
        CLI                                                     /* Disable interrupts                                   */
        RET                                                     /* Return original SREG value in R16                    */


CPU_SR_Restore:
        OUT     SREG,R16                                        /* Restore SREG                                         */
        RET                                                     /* Return                                               */

