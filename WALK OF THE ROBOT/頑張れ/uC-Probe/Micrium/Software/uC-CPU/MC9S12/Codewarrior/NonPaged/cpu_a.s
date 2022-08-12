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
;                                           Freescale MC9S12
;                                             Codewarrior
;                                              Non Paged
;
; Filename      : cpu_a.s
; Version       : V1.30.02.00
; Programmer(s) : EHS
;********************************************************************************************************

NON_BANKED:       section  

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

        xdef  CPU_SR_Save
        xdef  CPU_SR_Restore


;********************************************************************************************************
;                                               EQUATES
;********************************************************************************************************


;********************************************************************************************************
;                                  SAVE THE CCR AND DISABLE INTERRUPTS
;                                                  &
;                                              RESTORE CCR
;
; Description : These function implements OS_CRITICAL_METHOD #3
;
; Arguments   : The function prototypes for the two functions are:
;               1) CPU_SR  CPU_SR_Save(void);
;                             where CPU_SR is the contents of the CCR register prior to disabling
;                             interrupts.
;               2) void    CPU_SR_Restore(CPU_SR cpu_sr);
;                             'cpu_sr' the the value of the CCR to restore.
;
; Note(s)     : 1) It's assumed that the compiler uses the D register to pass a single 16-bit argument
;                  to and from an assembly language function.
;********************************************************************************************************

CPU_SR_Save:
    tfr  ccr,b                         ; It's assumed that 8-bit return value is in register B
    sei                                ; Disable interrupts
    rts                                ; Return to caller with D containing the previous CCR

CPU_SR_Restore:
    tfr  b,ccr                         ; B contains the CCR value to restore, move to CCR
    rts


;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************

