#*********************************************************************************************************
#*                                                uC/CPU
#*                                    CPU CONFIGURATION & PORT LAYER
#*
#*                          (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
#*
#*               All rights reserved.  Protected by international copyright laws.
#*
#*               uC/CPU is provided in source form to registered licensees ONLY.  It is 
#*               illegal to distribute this source code to any third party unless you receive 
#*               written permission by an authorized Micrium representative.  Knowledge of 
#*               the source code may NOT be used to develop a similar product.
#*
#*               Please help us continue to provide the Embedded community with the finest 
#*               software available.  Your honesty is greatly appreciated.
#*
#*               You can find our product's user manual, API reference, release notes and
#*               more information at https://doc.micrium.com.
#*               You can contact us at www.micrium.com.
#*********************************************************************************************************

#*********************************************************************************************************
#*
#*                                            CPU PORT FILE
#*
#*                                          Freescale MPC8349E
#*
#* Filename      : cpu_a.s
#* Version       : V1.30.02.00
#* Programmer(s) : CM
#*
#*********************************************************************************************************


#*********************************************************************************************************
#*                                             ASM HEADER
#*********************************************************************************************************

        .text

#*********************************************************************************************************
#*                                          PUBLIC DECLARATIONS
#*********************************************************************************************************

        .global  CPU_SR_Save
        .global  CPU_SR_Restore
        .global  CPU_SR_Rd
        .global  CPU_IntDis
        .global  CPU_IntEn
        .global  CPU_TBL_Get
        .global  CPU_TBU_Get
        .global  CPU_TBL_Set
        .global  CPU_TBU_Set


#*********************************************************************************************************
#*                                      CRITICAL SECTION FUNCTIONS
#*
#* Description : These functions are used to enter and exit critical sections using Critical Method #3.
#*
#*                   CPU_SR  CPU_SR_Save (void)
#*                          Get current global interrupt mask bit value from MSR
#*                          Disable interrupts
#*                          Return global interrupt mask bit
#*
#*                   void  CPU_SR_Restore (CPU_SR  cpu_sr)
#*                          Set global interrupt mask bit on MSR according to parameter cpu_sr
#*                          Return
#*
#* Argument(s) : cpu_sr      global interrupt mask status.
#*********************************************************************************************************

CPU_SR_Save:
    mfmsr   r3
    mfmsr   r5                              # Preparation for disabling interrupts (1)
    andi.   r5,r5,0x7fff                    # Preparation for disabling interrupts : set EE (bit #16) to '0' (2)
    mtmsr   r5                              # Disable interrupts
    blr

CPU_SR_Restore:
    mtmsr   r3
    blr


#*********************************************************************************************************
#*                                      READ STATUS REGISTER FUNCTION
#*
#* Description : This function is used to retrieve the status register value.
#*
#*                   CPU_SR  CPU_SR_Rd (void)
#*                          Get current MSR value
#*                          Return
#*********************************************************************************************************

CPU_SR_Rd:
    mfmsr   r3
    blr


#*********************************************************************************************************
#*                                      DISABLE/ENABLE INTERRUPTS
#*
#* Description : Disable/Enable interrupts by setting or clearing the global interrupt mask in the cpu
#*               status register.
#*
#*                    void  CPU_IntDis (void)
#*                           Set global interrupt mask bit on MSR
#*                           Return
#*
#*                    void  CPU_IntEn (void)
#*                           Clear global interrupt mask bit on MSR
#*                           Return
#*********************************************************************************************************

CPU_IntDis:
    mfmsr   r5                              # Preparation for disabling interrupts (1)
    andi.   r5,r5,0x7fff                    # Preparation for disabling interrupts : set EE (bit #16) to '0' (2)
    mtmsr   r5                              # Disable interrupts
    blr


CPU_IntEn:
    mfmsr   r5                              # Preparation for enabling interrupts (1)
    ori     r5,r5,0x8000                    # Preparation for enabling interrupts : set EE (bit #16) to '1'(2)
    mtmsr   r5                              # Enable interrupts
    blr


#*********************************************************************************************************
#*                                      READ TIME BASE LOW REGISTER FUNCTION
#*
#* Description : This function is used to retrieve the time base low register value.
#*
#*                   CPU_INT32U  CPU_TBL_Get (void)
#*                          Get current TBL value
#*                          Return
#*********************************************************************************************************

CPU_TBL_Get:
    mfspr   r3, 268
    blr


#*********************************************************************************************************
#*                                      READ TIME BASE HIGH REGISTER FUNCTION
#*
#* Description : This function is used to retrieve the time base high register value.
#*
#*                   CPU_INT32U  CPU_TBU_Get (void)
#*                          Get current TBU value
#*                          Return
#*********************************************************************************************************

CPU_TBU_Get:
    mfspr   r3, 269
    blr


#*********************************************************************************************************
#*                                      WRITE TIME BASE LOW REGISTER FUNCTION
#*
#* Description : This function is used to set the time base low register value.
#*
#*                   void  CPU_TBL_Set (CPU_INT32U value)
#*                          Write value into TBL
#*                          Return
#*********************************************************************************************************

CPU_TBL_Set:
    mtspr   284, r3
    blr


#*********************************************************************************************************
#*                                      WRITE TIME BASE HIGH REGISTER FUNCTION
#*
#* Description : This function is used to set the time base high register value.
#*
#*                   void  CPU_TBU_Set (CPU_INT32U value)
#*                          Write value into TBU
#*                          Return
#*********************************************************************************************************

CPU_TBU_Set:
    mtspr   285, r3
    blr


#*********************************************************************************************************
#*                                     CPU ASSEMBLY PORT FILE END
#*********************************************************************************************************
    .end
