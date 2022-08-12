/*
********************************************************************************************************
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
*                                               MIPS14k
*                                              MicroMips
*
* Filename      : cpu_a.s
* Version       : V1.30.02.00
* Programmer(s) : NB
*********************************************************************************************************
*/

#define _ASMLANGUAGE

/*
*********************************************************************************************************
*                                            PUBLIC FUNCTIONS
*********************************************************************************************************
*/

        .globl      CPU_SR_Save
        .globl      CPU_SR_Restore

/*
*********************************************************************************************************
*                                              EQUATES
*********************************************************************************************************
*/

.text


/*
*********************************************************************************************************
*                                          DISABLE INTERRUPTS
*                                      CPU_SR  CPU_SR_Save(void);
*
* Description: This function saves the state of the Status register and then disables interrupts via this
*              register.  This objective is accomplished with a single instruction, di.  The di 
*              instruction's operand, $2, is the general purpose register to which the Status register's 
*              value is saved.  This value can be read by C functions that call OS_CPU_SR_Save().  
*
* Arguments  : None
*
* Returns    : The previous state of the Status register
*********************************************************************************************************
*/

    .ent CPU_SR_Save
CPU_SR_Save:

    jr    $31
    di    $2                                   /* Disable interrupts, and move the old value of the... */
                                               /* ...Status register into v0 ($2)                      */
    .end CPU_SR_Save


/*
*********************************************************************************************************
*                                          ENABLE INTERRUPTS
*                                   void CPU_SR_Restore(CPU_SR sr);
*
* Description: This function must be used in tandem with CPU_SR_Save().  Calling CPU_SR_Restore()
*              causes the value returned by CPU_SR_Save() to be placed in the Status register. 
*
* Arguments  : The value to be placed in the Status register
*
* Returns    : None
*********************************************************************************************************
*/

    .ent CPU_SR_Restore
CPU_SR_Restore:

    jr    $31
    mtc0  $4, $12, 0                           /* Restore the status register to its previous state    */

    .end CPU_SR_Restore


/*
*********************************************************************************************************
*                                     CPU ASSEMBLY PORT FILE END
*********************************************************************************************************
*/

