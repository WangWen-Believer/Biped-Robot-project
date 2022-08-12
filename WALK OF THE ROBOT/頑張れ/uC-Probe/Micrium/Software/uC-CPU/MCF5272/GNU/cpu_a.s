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


;********************************************************************************************************
;
;                                            CPU PORT FILE
;
;                                               MCF5272
;                                            GNU C Compiler
;
; Filename      : cpu_a.asm
; Version       : V1.30.02.00
; Programmer(s) : JJL
;********************************************************************************************************


;********************************************************************************************************
;                                        PUBLIC DECLARATIONS
;********************************************************************************************************

        .global  CPU_SR_Save
        .global  CPU_SR_Restore


;********************************************************************************************************
;                                CPU_SR_Save() for OS_CRITICAL_METHOD #3
;
; Description : This functions implements the OS_CRITICAL_METHOD #3 function to preserve the state of the
;               interrupt disable flag in order to be able to restore it later.
;
; Arguments   : none
;
; Returns     : It is assumed that the return value is placed in the D0 register as expected by the
;               compiler.
;********************************************************************************************************

        .text

CPU_SR_Save:
        MOVE    %SR,%D0                                         /* Copy SR into D0                                      */
        MOVE.L  %D0,-(%A7)                                      /* Save D0                                              */
        ORI.L   #0x0700,%D0                                     /* Disable interrupts                                   */
        MOVE    %D0,%SR
        MOVE.L  (%A7)+,%D0                                      /* Restore original state of SR                         */
        RTS

;********************************************************************************************************
;                               CPU_SR_Restore() for OS_CRITICAL_METHOD #3
;
; Description : This functions implements the OS_CRITICAL_METHOD #function to restore the state of the
;               interrupt flag.
;
; Arguments   : cpu_sr   is the contents of the SR to restore.  It is assumed that this 'argument' is
;                        passed in the D0 register of the CPU by the compiler.
;
; Returns     : None
;********************************************************************************************************

CPU_SR_Restore:
        MOVE    %D0,%SR
        RTS


;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************

        END

