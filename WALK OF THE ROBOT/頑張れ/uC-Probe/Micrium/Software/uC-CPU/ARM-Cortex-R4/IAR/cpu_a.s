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
;                                            ARM Cortex-R4 
;                                            IAR C Compiler
;
; Filename      : cpu_a.s
; Version       : V1.30.02.00
; Programmer(s) : FT
;********************************************************************************************************


;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    PUBLIC  CPU_SR_Save
    PUBLIC  CPU_SR_Restore

    PUBLIC  CPU_IntDis
    PUBLIC  CPU_IntEn

    PUBLIC  CPU_IRQ_Dis
    PUBLIC  CPU_IRQ_En

    PUBLIC  CPU_FIQ_Dis
    PUBLIC  CPU_FIQ_En
    
    PUBLIC  CPU_CntLeadZeros

    PUBLIC  CPU_PMU_Dis
    PUBLIC  CPU_PMU_En
    PUBLIC  CPU_PMU_Rst

    PUBLIC  CPU_PMU_CtrDis
    PUBLIC  CPU_PMU_CtrEn
    PUBLIC  CPU_PMU_CtrEventSet
    PUBLIC  CPU_PMU_CtrRst
    
    PUBLIC  CPU_PMU_CtrGet
    PUBLIC  CPU_PMU_CtrCycleEn
    PUBLIC  CPU_PMU_CtrCycleDis
    PUBLIC  CPU_PMU_CtrCycleGet
    PUBLIC  CPU_PMU_CtrCycleRst


    PUBLIC  CPU_MPU_En
    PUBLIC  CPU_MPU_Dis
    PUBLIC  CPU_MPU_RegionEn
    PUBLIC  CPU_MPU_RegionDis

    PUBLIC  CPU_CtxID_Set
    PUBLIC  CPU_CtxID_Get
    

;********************************************************************************************************
;                                           VARIABLES
;********************************************************************************************************

    


;********************************************************************************************************
;                                                EQUATES
;
; Note(s) : (1) CNTENS/CNTENC bit arragement.
;
;               +---+-------------------------------+----+----+----+
;               | C |             RESERVED          | P2 | P1 | P0 |
;               +---+-------------------------------+----+----+----+
;                 |                                 |--------------|
;                 +----------> Cycle Counter Enable        |
;                                                          +----> Performance monitor
;                                                                 counters.
;
;********************************************************************************************************


CPU_ARM_CTRL_INT_DIS     EQU    0xC0                            ; Disable both FIQ & IRQ
CPU_ARM_CTRL_FIQ_DIS     EQU    0x40                            ; Disable FIQ.
CPU_ARM_CTRL_IRQ_DIS     EQU    0x80                            ; Disable IRQ.

CPU_ARM_BIT_CNTES_C      EQU    0x80000000                      ; Cycle counter enable set.
CPU_ARM_BIT_PMNC_E       EQU    0x00000001                      ; All counter enable bits.
CPU_ARM_BIT_PMNC_P       EQU    0x00000002                      ; Event counter reset.
CPU_ARM_BIT_PMNC_C       EQU    0x00000004                      ; Cycle counter reset.
CPU_ARM_BIT_PMNC_RST     EQU    0x00000006                      ; Reset all counters.


;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    RSEG CODE:CODE:NOROOT(2)
    CODE32


;********************************************************************************************************
;                                      CRITICAL SECTION FUNCTIONS
;
; Description : Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking, the
;               state of the interrupt disable flag is stored in the local variable 'cpu_sr' & interrupts
;               are then disabled ('cpu_sr' is allocated in all functions that need to disable interrupts).
;               The previous interrupt state is restored by copying 'cpu_sr' into the CPU's status register.
;
; Prototypes  : CPU_SR  CPU_SR_Save   (void);
;               void    CPU_SR_Restore(CPU_SR  cpu_sr);
;
; Note(s)     : (1) These functions are used in general like this :
;
;                       void  Task (void  *p_arg)
;                       {
;                           CPU_SR_ALLOC();                     /* Allocate storage for CPU status register */
;                               :
;                               :
;                           CPU_CRITICAL_ENTER();               /* cpu_sr = CPU_SR_Save();                  */
;                               :
;                               :
;                           CPU_CRITICAL_EXIT();                /* CPU_SR_Restore(cpu_sr);                  */
;                               :
;                       }
;
;               (2) When NMFI behavior is enabled, FIQ interrutps cannot be masked by software.
;                   Enabling NMFI behavior ensures that when the FIQ mask, that is, the CPSR.F bit, has
;                   been cleared by the reset handler, fast interrupts are always taken as quickly as 
;                   possible, except during handling of a fast interrupt. NMFI behavior is controlled
;                   by a configuration input signal CFGNMFI, that is asserted high to enable NMFI operation.
;                   There is not software control of NMFI.
;********************************************************************************************************

CPU_SR_Save
        MRS     R0, CPSR
        CPSID   IF                                              ; Set IRQ & FIQ bits in CPSR to DISABLE all interrupts
        DSB
        BX      LR                                              ; DISABLED, return the original CPSR contents in R0


CPU_SR_Restore                                                  ; See Note #2
        DSB
        MSR     CPSR_c, R0
        BX      LR


;********************************************************************************************************
;                                     ENABLE & DISABLE INTERRUPTS
;
; Description : Disable/Enable IRQs & FIQs.
;
; Prototypes  : void  CPU_IntEn (void);
;               void  CPU_IntDis(void);
;
; Note(s)     : See 'CPU_SR_Save()' note #1.
;********************************************************************************************************

CPU_IntDis
        CPSID   IF
        DSB
        BX      LR

CPU_IntEn
        DSB
        CPSIE   IF
        BX      LR


;********************************************************************************************************
;                                        ENABLE & DISABLE IRQs
;
; Description : Disable/Enable IRQs.
;
; Prototypes  : void  CPU_IRQ_En (void);
;               void  CPU_IRQ_Dis(void);
;********************************************************************************************************

CPU_IRQ_Dis
        MRS     R0, CPSR
        ORR     R0, R0, #CPU_ARM_CTRL_IRQ_DIS                   ; Set IRQ bit in CPSR to disable IRQs.
        MSR     CPSR_c, R0
        BX      LR


CPU_IRQ_En
        MRS     R0, CPSR
        BIC     R0, R0, #CPU_ARM_CTRL_IRQ_DIS                   ; Clear IRQ bit in CPSR to enable IRQs.
        MSR     CPSR_c, R0
        BX      LR


;********************************************************************************************************
;                                        ENABLE & DISABLE FIQs
;
; Description : Disable/Enable FIQs.
;
; Prototypes  : void  CPU_FIQ_En (void);
;               void  CPU_FIQ_Dis(void);
;
; Note(s)     : See 'CPU_SR_Save()' note #1.
;********************************************************************************************************

CPU_FIQ_Dis
        MRS     R0, CPSR
        ORR     R0, R0, #CPU_ARM_CTRL_FIQ_DIS                   ; Set FIQ bit in CPSR to disable FIQs.
        MSR     CPSR_c, R0
        BX      LR

CPU_FIQ_En
        MRS     R0, CPSR
        BIC     R0, R0, #CPU_ARM_CTRL_FIQ_DIS                   ; Clear FIQ bit in CPSR to enable FIQs.
        MSR     CPSR_c, R0
        BX      LR


;********************************************************************************************************
;                                         CPU_CntLeadZeros()
;                                        COUNT LEADING ZEROS
;
; Description : Counts the number of contiguous, most-significant, leading zero bits before the 
;                   first binary one bit in a data value.
;
; Prototype   : CPU_DATA  CPU_CntLeadZeros(CPU_DATA  val);
;
; Argument(s) : val         Data value to count leading zero bits.
;
; Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
;
; Caller(s)   : Application.
;
;               This function is an INTERNAL CPU module function but MAY be called by application 
;               function(s).
;
; Note(s)     : (1) (a) Supports 32-bit data value size as configured by 'CPU_DATA' (see 'cpu.h  
;                       CPU WORD CONFIGURATION  Note #1').
;
;                   (b) For 32-bit values :
;
;                             b31  b30  b29  ...  b04  b03  b02  b01  b00    # Leading Zeros
;                             ---  ---  ---       ---  ---  ---  ---  ---    ---------------
;                              1    x    x         x    x    x    x    x            0
;                              0    1    x         x    x    x    x    x            1
;                              0    0    1         x    x    x    x    x            2
;                              :    :    :         :    :    :    :    :            :
;                              :    :    :         :    :    :    :    :            :
;                              0    0    0         1    x    x    x    x           27
;                              0    0    0         0    1    x    x    x           28
;                              0    0    0         0    0    1    x    x           29
;                              0    0    0         0    0    0    1    x           30
;                              0    0    0         0    0    0    0    1           31
;                              0    0    0         0    0    0    0    0           32
;
;
;               (2) MUST be defined in 'cpu_a.asm' (or 'cpu_c.c') if CPU_CFG_LEAD_ZEROS_ASM_PRESENT is 
;                   #define'd in 'cpu_cfg.h' or 'cpu.h'.
;********************************************************************************************************

CPU_CntLeadZeros:
        CLZ     R0, R0                                          ; Count leading zeros
        BX      LR


;********************************************************************************************************
;                                            CPU_PMU_Dis()
;                                        
; Description : Disable performance monitor counters..
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

; void  CPU_PMU_Dis (void)

CPU_PMU_Dis:        
        MRC     P15, 0, R0, C9, C12, 0                          ; Read PMNC Register.
        BIC     R0, R0, #CPU_ARM_BIT_PMNC_C                     ; Clear enable bit.
        MCR     P15, 0, R0, C9, C12, 0                          ; Write PMNC Register.                
        BX      LR
        
        
;********************************************************************************************************
;                                            CPU_PMU_En()
;                                        
; Description : Enable performance monitor counters.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

; void  CPU_PMU_En (void)

CPU_PMU_En:        
        MRC     P15, 0, R0, C9, C12, 0                          ; Read PMNC Register.
        ORR     R0, R0, #CPU_ARM_BIT_PMNC_E                     ; Set all counter enable bit.
        MCR     P15, 0, R0, C9, C12, 0                          ; Write PMNC Register.
        BX      LR
 

;********************************************************************************************************
;                                            CPU_PMU_Rst()
;                                        
; Description : Reset performance monitor counters.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

; void  CPU_PMU_Rst (void)

CPU_PMU_Rst:                        
        MRC     P15, 0, R0, C9, C12, 0                          ; Read PMNC Register.
        ORR     R0, R0, #CPU_ARM_BIT_PMNC_RST                   ; Resets all counters.
        MCR     P15, 0, R0, C9, C12, 0                          ; Write PMNC Register.
        
        BX      LR
      
      
;********************************************************************************************************
;                                            CPU_PMU_CtrDis()
;                                        
; Description : Disable any of the performance monitor count registers.
;
; Argument(s) : ctr    Performance monitor counter
;                         0   Performance monitor counter 0
;                         1   Performance monitor counter 1
;                         2   Performance monitor counter 2
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : None.
;********************************************************************************************************

; void  CPU_PMU_CtrDis  (CPU_INT08U   ctr)  ==>  R0

CPU_PMU_CtrDis:
        CMP     R0, #2                                          ; Argument check.
        BXHI    LR        
        
        MOV     R1, #1 
        LSL     R0, R1, R0
        MCR     P15, 0, R0, C9, C12, 2                          ; Write CNTENC Register.
        BX      LR        


;********************************************************************************************************
;                                            CPU_PMU_CtrEn()
;                                        
; Description : Enable any of the performance monitor count registers.
;
; Argument(s) : ctr    Performance monitor counter
;                         0   Performance monitor counter 0
;                         1   Performance monitor counter 1
;                         2   Performance monitor counter 2
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : (1) 'R1' is used to calculate the value to be written in the CNTENS register.
;********************************************************************************************************

; void  CPU_PMU_CtrEn  (CPU_INT08U   ctr)  ==>  R0

CPU_PMU_CtrEn:
        CMP     R0, #0x02                                       ; Argument check.
        BXHI    LR        
        
        MOV     R1, #0x01 
        LSL     R0, R1, R0
        MCR     P15, 0, R0, C9, C12, 1                          ; Write CNTENS Register.
        BX      LR
        

;********************************************************************************************************
;                                            CPU_PMU_CtrEventSet()
;                                        
; Description : Selects an an event with a specific timer
;
; Argument(s) : ctr    Performance monitor counter
;                         0   Performance monitor counter 0
;                         1   Performance monitor counter 1
;                         2   Performance monitor counter 2
;
;
;               event  Event code (see cpu.h CPU_ARM_EVENT_xxx #define's)
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrEventSet (CPU_INT08U  ctr,     ==>  R0
;                           CPU_INT08U  event)   ==>  R1

CPU_PMU_CtrEventSet:
        CMP     R0, #0x02
        BXHI    LR
        
        MRC     P15, 0, R2, C9, C12, 5                          ; Read  PMNXSEL Register
        BIC     R2, R2, #0x0000001F
        ORR     R2, R2, R0 
        MCR     P15, 0, R2, C9, C12, 5                          ; Write PMNXSEL Register
 
        MRC     P15, 0, R2, C9, C13, 1                          ; Read  EVTSELx Register
        BIC     R2, R2, #0x000000FF
        ORR     R2, R2, R1 
        MCR     P15, 0, R2, C9, C13, 1                          ; Write EVTSELx Register        
        BX      LR


;********************************************************************************************************
;                                            CPU_PMU_CtrGet()
;                                        
; Description : Return the value of a specific performance monitor count register.
;
; Argument(s) : ctr    Performance monitor counter
;                         0   Performance monitor counter 0
;                         1   Performance monitor counter 1
;                         2   Performance monitor counter 2
;
; Return(s)   : Performance monitor counter value. R0
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrGet (CPU_INT08U  ctr)  ==>  R0

CPU_PMU_CtrGet:
        CMP     R0, #0x02                                       ; Argument check.
        BXHI    LR
        
        MRC     P15, 0, R1, C9, C12, 5                          ; Read  PMNXSEL Register
        BIC     R1, R1, #0x0000001F
        ORR     R1, R1, R0 
        MCR     P15, 0, R1, C9, C12, 5                          ; Write PMNXSEL Register
 
        MRC     P15, 0, R0, C9, C13, 2                          ; Read  PMNx    Register
        BX      LR



;********************************************************************************************************
;                                            CPU_PMU_CtrRst()
;                                        
; Description : Reset an event counter.
;
; Argument(s) : ctr    Performance monitor counter
;                         0   Performance monitor counter 0
;                         1   Performance monitor counter 1
;                         2   Performance monitor counter 2
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrRst  (CPU_INT08U  ctr)  ==>  R0

CPU_PMU_CtrRst:
        CMP     R0, #2
        BXHI    LR
        
        MRC     P15, 0, R1, C9, C12, 5                          ; Read  PMNXSEL Register.
        BIC     R1, R1, #0x0000001F
        ORR     R1, R1, R0 
        MCR     P15, 0, R1, C9, C12, 5                          ; Write PMNXSEL Register.
 
        MOV     R0, #0
        MCR     P15, 0, R0, C9, C13, 2                          ; Write PMNx    Register.
        BX      LR


;********************************************************************************************************
;                                          CPU_PMU_CtrCycleDis()
;                                        
; Description : Disable cycle counter.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrCycleDis(void)

CPU_PMU_CtrCycleDis:       
        MOV     R0, #CPU_ARM_BIT_CNTES_C
        MCR     P15, 0, R0, C9, C12, 2                          ; Write CNTENC Register.
        BX      LR


;********************************************************************************************************
;                                          CPU_PMU_CtrCycleEn()
;                                        
;
; Description : Disable cycle counter.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrCycleEn (void)

CPU_PMU_CtrCycleEn:       
        MOV     R0, #CPU_ARM_BIT_CNTES_C
        MCR     P15, 0, R0, C9, C12, 1                          ; Write CNTENS Register.
        BX      LR


;********************************************************************************************************
;                                          CPU_PMU_CtrCycleGet()
;                                        
;
; Description : Get cycle counter value.
;
; Argument(s) : none.
;
; Return(s)   : Cycle counter value.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrCycleGet (void)

CPU_PMU_CtrCycleGet:               
        MRC     P15, 0, R0, C9, C13, 0                          ; Read CCNT Register.
        BX      LR


;********************************************************************************************************
;                                          CPU_PMU_CtrCycleRst()
;                                        
;
; Description : Reset counter cycle.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_PMU_CtrCycleRst (void)

CPU_PMU_CtrCycleRst: 
        MRC     P15, 0, R0, C9, C12, 0                          ; Read PMNC Register.
        ORR     R0, R0, #CPU_ARM_BIT_PMNC_C                     ; Resets all counters.
        MCR     P15, 0, R0, C9, C12, 0                          ; Write PMNC Register.
        BX      LR


;********************************************************************************************************
;                                              CPU_MPU_En()
;                                        
; Description : Enable MPU
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_MPU_En (void)

CPU_MPU_En
        MRC     P15, 0, R0, C1, C0, 0                           ; Read CP15 register 1
        ORR     R0, R0, #0x1
        DSB
        MCR     P15, 0, R0, C1, C0, 0                           ; Enable MPU
        ISB
        BX      LR
        
        
;********************************************************************************************************
;                                              CPU_MPU_Dis()
;                                        
; Description : Disable MPU.
;
; Argument(s) : none.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_MPU_Dis (void)

CPU_MPU_Dis 
        MRC     P15, 0, R0, C1, C0, 0                           ; Read CP15 register 1
        BIC     R0, R0, #0x1
        DSB
        MCR     P15, 0, R0, C1, C0, 0                           ; Disable MPU
        BX      LR


;********************************************************************************************************
;                                              CPU_MPU_RegionEn()                                        
;
; Description : enable a MPU memory region.
;
; Argument(s) : nbr          Region number.
;
;               addr         Region start address.
;
;               sub_reg_dis  Bit-field with the subregion that are disabled (see note #1)
;
;               size         Region size minus one (see note #2). 
;
;               access       Memory region access attributes. The access atrributes word should be
;                            a OR between the followin attributes falgs.
;
;                            access  = CPU_ARM_MPU_ACCESS_PERM_xxx        (Access permissions)
;                                    | CPU_ARM_MPU_ACCESS_TYPE_xxx        (Access type       )
;                                    | CPU_ARM_MPU_ACCESS_SHARE           (Share attribute   )
;                                    | CPU_ARM_MPU_ACCESS_EXECUTE_NEVER   (Determine if a memory is executable)
;
;                            The 'CPU_ARM_MPU_ACCESS_PERM_xxx' field can take one of the following values:
;                          
;                            CPU_ARM_MPU_ACCESS_PERM_NO_ACCESS                   All accesses generate a permission fault.
;                            CPU_ARM_MPU_ACCESS_PERM_PRIV_FULL                   Priviliged access only.
;                            CPU_ARM_MPU_ACCESS_PERM_USER_RD                     Writes in User mode generate permission fault.
;                            CPU_ARM_MPU_ACCESS_PERM_USER_FULL                   Full access.
;                            CPU_ARM_MPU_ACCESS_PERM_PRIV_RD                     Privileged read-only.
;                            CPU_ARM_MPU_ACCESS_PERM_PRIV_USER_RD                Privileged/user read-only.
;
;                            The 'CPU_ARM_MPU_ACCESS_TYPE_xxx' field can take one of the following values:
;        
;                            CPU_ARM_MPU_ACCESS_TYPE_STRONG_ORDERED              Strongly-ordered. Always shareable  ('CPU_ARM_MPU_ACCESS_SHARE' is ignored)
;                            CPU_ARM_MPU_ACCESS_TYPE_DEV_SHARED                  Shareable device. Always shareable  ('CPU_ARM_MPU_ACCESS_SHARE' is ignored)
;                            CPU_ARM_MPU_ACCESS_TYPE_DEV                         Non-Shareable. Always non-shareable ('CPU_ARM_MPU_ACCESS_SHARE' is ignored)
;
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_WT                Outer and Inner write-trought, no write allocate.
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_WB                Outer and Inner write-back, no write-allocate.
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_NONE              Outer and Inner non-cacheable.
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_WBA               Outer and Inner write-back, write allocated.
;
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_CACHE(inner, outer)  It is a macro when the memory region is Cacheable memory.
;                            where the 'inner' and 'outer' parameter can be one of the following:
;
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_CACHE_OPT_NONE       Non-cacheable
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_CACHE_OPT_WBA        Write-back, write-allocate.
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_CACHE_OPT_WT         Write-trough, no write allocate.
;                            CPU_ARM_MPU_ACCESS_TYPE_NORMAL_CACHE_OPT_WB         Write-back, no write allocate.
;
;                            If 'CPU_ARM_MPU_ACCESS_EXECUTE_NEVER' is set, instruciton fetches are not enabled for a particular region.
;
; Return(s)   : DEF_YES, if valid memory region is set
;
;               DEF_NO,  otherwise.. (see note #4)
;
; Caller(s)   : Application.
;              
; Note(s)     : (1) Each region can be split into eight equal sized non-overlapping subregions.
;                   an access to a memory address in a disabled subregion does not use the atributes 
;                   and permissions defined for that region. Instead, it uses the attributes and 
;                   permissions of a lower priority region or generates a bacground fault if no other 
;                   region overlap at that address. This enables increased protection and 
;                   memory attribute granularity.
;
;               (2) Region size paramater MUST be in power of 2 (32, 64, 128, 256, etc).
;                   
;                   (a) The minimal value for the region size is 32 - 1 
;                       The maximum value is 4294967295 - 1
;********************************************************************************************************

;CPU_BOOLEAN  CPU_MPU_RegionEn  (CPU_INT08U  nbr,           -->  RO
;                                CPU_ADDR    addr           -->  R1
;                                CPU_INT08U  sub_reg_dis,   -->  R2
;                                CPU_INT32U  size,          -->  R3
;                                CPU_INT32U  access);       --> [SP]

CPU_MPU_RegionEn
         PUSH   {R4, R5}
         MRC    P15, 0, R4, C0, C0, 4                           ; Read MPU number of available regions.
         LSR    R4, R4, #0x08
         AND    R4, R4, #0x0F
         CMP    R0, R4                                          ; Compare region number with maximun number of regions.
         BPL    CPU_MPU_RegionEnExitFail
                                                                 
         CMP    R3, #0x1F                                       ; If size < minimal size return fail
         BLT    CPU_MPU_RegionEnExitFail

         MCR    P15, 0, R0, C6, C2, 0                           ; Write MPU memory region number register.
         MRC    P15, 0, R4, C6, C1, 2                           ; Read data MPU region size and enable register.
         AND    R4, R4, #0x01                                   ; Check if region is enabled.
         CMP    R4, #0x00                                       ; If region is already enable, return fail
         BNE    CPU_MPU_RegionEnExitFail
         
         MCR    P15, 0, R1, C6, C1, 0                           ; Write MPU base address register.
         LDR    R4, [SP, #8]                                        ; Load access parameter.
         MCR    P15, 0, R4, C6, C1, 4                           ; Write Region acces control register.
         
         LSL    R4, R2, #0x08                                    ; Set the sub-region disable field [15:8]
         CLZ    R5, R3                                           ; Calculate the size field (log2(size))
         RSB    R5, R5, #0x1F
         LSL    R5, R5, #0x01
         ORR    R4, R4, R5
         ORR    R4, R4, #0x01
         MCR    P15, 0, R4, C6, C1, 2                           ; Write Data MPU region Size and enable register.
         MOV    R0, #0x1                                        ; return 'DEF_OK'
         POP    {R4, R5}
         BX     LR
         
CPU_MPU_RegionEnExitFail
         MOV    R0, #0x0                                        ; return 'DEF_FAIL'
         POP    {R4, R5}
         BX     LR


;********************************************************************************************************
;                                              CPU_MPU_RegionDis()                                        
;
; Description : Disable a memory region.
;
; Argument(s) : nbr          Region number.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;CPU_BOOLEAN  CPU_MPU_RegionDis (CPU_INT08U  nbr) -->  RO

CPU_MPU_RegionDis
         MRC    P15, 0, R1, C0, C0, 4                           ; Read MPU number of available regions.
         LSR    R1, R1, #0x08
         AND    R1, R1, #0x0F
         CMP    R0, R1                                          ; Compare region number with maximun number of regions.
         BPL    CPU_MPU_RegionDisExit
         MOV    R1, #0x00
         MCR    P15, 0, R1, C6, C1, 2                           ; Write Data MPU region Size and enable register.

CPU_MPU_RegionDisExit
         BX     LR


;********************************************************************************************************
;                                              CPU_CtxID_Set()                                        
;
; Description : Set the context identification value in the Contex ID register.
;
; Argument(s) : ctx_id   Context identifier.
;
; Return(s)   : none.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;void  CPU_CtxID_Set  (CPU_INT32U  ctx_id);  --> RO

CPU_CtxID_Set
        MCR     P15, 0, R0, C13, C0, 1
        BX      LR
        

;********************************************************************************************************
;                                              CPU_CtxID_Set()                                        
;
; Description : Get the context identification value from the Contex ID register.
;
; Argument(s) : none.
;
; Return(s)   : The current context identification value.
;
; Caller(s)   : Application.
;              
; Note(s)     : none.
;********************************************************************************************************

;CPU_INT32U  CPU_CtxID_Get  (void);

CPU_CtxID_Get
        MRC     P15, 0, R0, C13, C0, 1
        BX      LR


;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************

        END

