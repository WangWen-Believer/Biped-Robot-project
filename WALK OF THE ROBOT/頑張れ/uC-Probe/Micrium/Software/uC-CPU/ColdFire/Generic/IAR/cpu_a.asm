/*
;********************************************************************************************************
;                                                uC/CPU
;                                    CPU CONFIGURATION & PORT LAYER
;
;                          (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
;
;               All rights reserved.  Protected by international copyright laws.
;
;               uC/CPU is provided in source form to registered licensees ONLY.  It is 
;               illegal to distribute this source code to any third party unless you receive 
;               written permission by an authorized Micrium representative.  Knowledge of 
;               the source code may NOT be used to develop a similar product.
;
;               Please help us continue to provide the Embedded community with the finest 
;               software available.  Your honesty is greatly appreciated.
;
;               You can find our product's user manual, API reference, release notes and
;               more information at https://doc.micrium.com.
;               You can contact us at www.micrium.com.
;********************************************************************************************************
*/

/*
;********************************************************************************************************
;
;                                            CPU PORT FILE
;
;                                               ColdFire
;                                            IAR C Compiler
;
; Filename      : cpu_a.asm
; Version       : V1.30.02.00
; Programmer(s) : JJL
;                 FGK
;********************************************************************************************************
*/

/*
;********************************************************************************************************
;                                         PUBLIC DECLARATIONS
;********************************************************************************************************
*/

        PUBLIC  CPU_VectInit

        PUBLIC  CPU_SR_Save
        PUBLIC  CPU_SR_Restore

/*
;********************************************************************************************************
;                                         EXTERNAL DECLARATIONS
;********************************************************************************************************
*/

        EXTERN  CPU_VBR_Ptr

        RSEG    CODE:CODE:NOROOT(2)                             /* Align to power 2, 4 bytes.                            */

/*
;********************************************************************************************************
;                                 VECTOR BASE REGISTER INITIALIZATION
;
; Description : This function is called to set the Vector Base Register to the value specified in
;               the function argument.
;
; Argument(s) : VBR         Desired vector base address.
;
; Return(s)   : none.
;
; Note(s)     : (1) 'CPU_VBR_Ptr' keeps the current vector base address.
;
;               (2) 'VBR' parameter is assumed to be passed on D0 by the compiler.
;********************************************************************************************************
*/

CPU_VectInit:
        MOVE.L  D0, (CPU_VBR_Ptr)                               /* Save 'vbr' into CPU_VBR_Ptr                          */
        MOVEC   D0, VBR
        RTS


/*
;********************************************************************************************************
;                               CPU_SR_Save() for OS_CRITICAL_METHOD #3
;
; Description : This functions implements the OS_CRITICAL_METHOD #3 function to preserve the state of the
;               interrupt disable flag in order to be able to restore it later.
;
; Argument(s) : none.
;
; Return(s)   : It is assumed that the return value is placed in the D0 register as expected by the
;               compiler.
;
; Note(s)     : none.
;********************************************************************************************************
*/

CPU_SR_Save:
        MOVE.W  SR, D0                                          /* Copy SR into D0                                      */
        MOVE.W  D0, D1
        ORI.L   #0x0700, D1                                     /* Disable interrupts                                   */
        MOVE.W  D1, SR                                          /* Restore SR state with interrupts disabled            */
        RTS


/*
;********************************************************************************************************
;                             CPU_SR_Restore() for OS_CRITICAL_METHOD #3
;
; Description : This functions implements the OS_CRITICAL_METHOD #function to restore the state of the
;               interrupt flag.
;
; Argument(s) : cpu_sr      Contents of the SR to restore.  It is assumed that 'cpu_sr' is passed in D0.
;
; Return(s)   : none.
;
; Note(s)     : none.
;********************************************************************************************************
*/

CPU_SR_Restore:
        MOVE.W  D0, SR                                          /* Restore SR previous state                            */
        RTS


/*
;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************
*/

        END
