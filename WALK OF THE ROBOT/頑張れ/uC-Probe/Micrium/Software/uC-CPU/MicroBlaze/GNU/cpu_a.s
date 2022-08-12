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
*                                              MicroBlaze
*                                            GNU C Compiler
*
* Filename      : cpu_a.s
* Version       : V1.30.02.00
* Programmer(s) : MG
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

.equ    CPU_IE_BIT,         0x02

.text


/*
*********************************************************************************************************
*                                         DISABLE INTERRUPTS
*                                      CPU_SR  CPU_SR_Save(void);
*
* Description : Disables the interrupts and returns the RMSR contents.  This allows the IE state to be
*               restored at a subsequent time.
*
*               The variable in the calling routine which the return is set to MUST be declared 'volatile'
*               for proper operation.  There is no guarantee that the proper register will be scheduled
*               for the subsequent 'CPU_SR_Save()' function call if the variable is not declared
*               'volatile'.
*
* Arguments   : None
*
* Returns     : Current RMSR contents in R3
*
* Note(s)     : This function uses the MSRCLR instruction, which is not, by default, recognized by
*               MicroBlaze processors.  Setting the paramter C_USE_MSR_INSTR to '1' in the MHS file
*               allows the processor to recognize this instruction.
*********************************************************************************************************
*/

CPU_SR_Save:
    RTSD    r15, 8
    MSRCLR  r3,  CPU_IE_BIT                  /* Save MSR in r3 and disable interrupts                  */


/*
*********************************************************************************************************
*                                         ENABLE INTERRUPTS
*                                    void CPU_SR_Restore(CPU_SR sr);
*
* Description: Enables the interrupts using the provided data. If the IE bit is set in the argument, the
*              RTID opcode is used to return.  If the IE bis is clear, the standard RTSD is used leaving
*              the interrupts disabled.
*
*              The argument from the calling routine MUST be declared 'volatile' for proper operation.
*              There is no guarantee that the proper register will be scheduled for the 'CPU_SR_Restore()'
*              function call if the variable is not declared 'volatile'.
*
* Arguments   : Saved RMSR contents in R5
*
* Returns     : None
*
* Note(s)     : None
*********************************************************************************************************
*/

CPU_SR_Restore:
    RTSD    r15, 8
    MTS     rMSR, r5                         /* Move the saved status from r5 into rMSR                */


/*
*********************************************************************************************************
*                                     CPU ASSEMBLY PORT FILE END
*********************************************************************************************************
*/

