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
*                                            ARM Cortex-A8
*                                              IAR EWARM
*
* Filename      : cpu.h
* Version       : V1.30.02.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
*                               WARNING - DEPRECATION NOTICE - WARNING
* August 2013
* This file is part of a deprecated port and will be removed in a future release.
* The functionalities of this port were replaced by the ARM-Cortex-A port.
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CPU_MODULE_PRESENT
#define  CPU_MODULE_PRESENT


/*
*********************************************************************************************************
*                                          CPU INCLUDE FILES
*
* Note(s) : (1) The following CPU files are located in the following directories :
*
*               (a) \<Your Product Application>\cpu_cfg.h
*
*               (b) \<CPU-Compiler Directory>\cpu_def.h
*
*               (c) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                               <cpu>                           directory name for specific CPU
*                               <compiler>                      directory name for specific compiler
*
*           (2) Compiler MUST be configured to include the '\<CPU-Compiler Directory>\' directory the
*               specific CPU-compiler directory, & '\<Your Product Application>\' as additional include
*               path directories.
*
*           (3) Since NO custom library modules are included, 'cpu.h' may ONLY use configurations from
*               CPU configuration file 'cpu_cfg.h' that do NOT reference any custom library definitions.
*
*               In other words, 'cpu.h' may use 'cpu_cfg.h' configurations that are #define'd to numeric
*               constants or to NULL (i.e. NULL-valued #define's); but may NOT use configurations to
*               custom library #define's (e.g. DEF_DISABLED or DEF_ENABLED).
*********************************************************************************************************
*/

#include  <intrinsics.h>

#include  <cpu_def.h>
#include  <cpu_cfg.h>                                           /* See Note #3.                                         */

#ifdef __cplusplus
extern  "C" {
#endif


/*
*********************************************************************************************************
*                                    CONFIGURE STANDARD DATA TYPES
*
* Note(s) : (1) Configure standard data types according to CPU-/compiler-specifications.
*
*           (2) (a) (1) 'CPU_FNCT_VOID' data type defined to replace the commonly-used function pointer
*                       data type of a pointer to a function which returns void & has no arguments.
*
*                   (2) Example function pointer usage :
*
*                           CPU_FNCT_VOID  FnctName;
*
*                           FnctName();
*
*               (b) (1) 'CPU_FNCT_PTR'  data type defined to replace the commonly-used function pointer
*                       data type of a pointer to a function which returns void & has a single void
*                       pointer argument.
*
*                   (2) Example function pointer usage :
*
*                           CPU_FNCT_PTR   FnctName;
*                           void          *p_obj
*
*                           FnctName(p_obj);
*********************************************************************************************************
*/

typedef            void        CPU_VOID;
typedef            char        CPU_CHAR;                        /*  8-bit character                                     */
typedef  unsigned  char        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
typedef  unsigned  char        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef    signed  char        CPU_INT08S;                      /*  8-bit   signed integer                              */
typedef  unsigned  short       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef    signed  short       CPU_INT16S;                      /* 16-bit   signed integer                              */
typedef  unsigned  int         CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef    signed  int         CPU_INT32S;                      /* 32-bit   signed integer                              */
typedef  unsigned  long  long  CPU_INT64U;                      /* 64-bit unsigned integer                              */
typedef    signed  long  long  CPU_INT64S;                      /* 64-bit   signed integer                              */

typedef            float       CPU_FP32;                        /* 32-bit floating point                                */
typedef            double      CPU_FP64;                        /* 64-bit floating point                                */


typedef  volatile  CPU_INT08U  CPU_REG08;                       /*  8-bit register                                      */
typedef  volatile  CPU_INT16U  CPU_REG16;                       /* 16-bit register                                      */
typedef  volatile  CPU_INT32U  CPU_REG32;                       /* 32-bit register                                      */
typedef  volatile  CPU_INT64U  CPU_REG64;                       /* 64-bit register                                      */


typedef            void      (*CPU_FNCT_VOID)(void);            /* See Note #2a.                                        */
typedef            void      (*CPU_FNCT_PTR )(void *p_obj);     /* See Note #2b.                                        */


/*
*********************************************************************************************************
*                                       CPU WORD CONFIGURATION
*
* Note(s) : (1) Configure CPU_CFG_ADDR_SIZE & CPU_CFG_DATA_SIZE with CPU's word sizes :
*
*                   CPU_WORD_SIZE_08             8-bit word size
*                   CPU_WORD_SIZE_16            16-bit word size
*                   CPU_WORD_SIZE_32            32-bit word size
*                   CPU_WORD_SIZE_64            64-bit word size            See Note #1a
*
*               (a) 64-bit word size NOT currently supported.
*
*           (2) Configure CPU_CFG_ENDIAN_TYPE with CPU's data-word-memory order :
*
*               (a) CPU_ENDIAN_TYPE_BIG         Big-   endian word order (CPU words' most  significant
*                                                                         octet @ lowest memory address)
*               (b) CPU_ENDIAN_TYPE_LITTLE      Little-endian word order (CPU words' least significant
*                                                                         octet @ lowest memory address)
*
*           (3) '__LITTLE_ENDIAN__' is an IAR compiler #define that reflects the '--endian' option,
*               indicating the data word-memory order :
*
*               (a) '0' for big    endian word-memory order
*               (b) '1' for little endian word-memory order
*********************************************************************************************************
*/

                                                                /* Define  CPU         word sizes (see Note #1) :       */
#define  CPU_CFG_ADDR_SIZE              CPU_WORD_SIZE_32        /* Defines CPU address word size  (in octets).          */
#define  CPU_CFG_DATA_SIZE              CPU_WORD_SIZE_32        /* Defines CPU data    word size  (in octets).          */
#define  CPU_CFG_DATA_SIZE_MAX          CPU_WORD_SIZE_64        /* Defines CPU maximum word size  (in octets).          */

                                                                /* Defines CPU data    word-memory order (see Note #2). */
#if (defined(__LITTLE_ENDIAN__) && \
            (__LITTLE_ENDIAN__ == 1))                           /* Defines CPU data    word-memory order (see Note #2). */
#define  CPU_CFG_ENDIAN_TYPE            CPU_ENDIAN_TYPE_LITTLE  /*   See Note #3b.                                      */
#else
#define  CPU_CFG_ENDIAN_TYPE            CPU_ENDIAN_TYPE_BIG     /*   See Note #3a.                                      */
#endif


/*
*********************************************************************************************************
*                                 CONFIGURE CPU ADDRESS & DATA TYPES
*********************************************************************************************************
*/

                                                                /* CPU address type based on address bus size.          */
#if     (CPU_CFG_ADDR_SIZE == CPU_WORD_SIZE_32)
typedef  CPU_INT32U  CPU_ADDR;
#elif   (CPU_CFG_ADDR_SIZE == CPU_WORD_SIZE_16)
typedef  CPU_INT16U  CPU_ADDR;
#else
typedef  CPU_INT08U  CPU_ADDR;
#endif

                                                                /* CPU data    type based on data    bus size.          */
#if     (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_32)
typedef  CPU_INT32U  CPU_DATA;
#elif   (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_16)
typedef  CPU_INT16U  CPU_DATA;
#else
typedef  CPU_INT08U  CPU_DATA;
#endif


typedef  CPU_DATA    CPU_ALIGN;                                 /* Defines CPU data-word-alignment size.                */
typedef  CPU_ADDR    CPU_SIZE_T;                                /* Defines CPU standard 'size_t'   size.                */


/*
*********************************************************************************************************
*                                       CPU STACK CONFIGURATION
*
* Note(s) : (1) Configure CPU_CFG_STK_GROWTH in 'cpu.h' with CPU's stack growth order :
*
*               (a) CPU_STK_GROWTH_LO_TO_HI     CPU stack pointer increments to the next higher  stack
*                                                   memory address after data is pushed onto the stack
*               (b) CPU_STK_GROWTH_HI_TO_LO     CPU stack pointer decrements to the next lower   stack
*                                                   memory address after data is pushed onto the stack
*
*           (2) Configure CPU_CFG_STK_ALIGN_BYTES with the highest minimum alignement required for
*               cpu stacks.
*
*               (a) ARM Procedure Calls Standard requires an 8 bytes stack alignment.
*********************************************************************************************************
*/

#define  CPU_CFG_STK_GROWTH       CPU_STK_GROWTH_HI_TO_LO       /* Defines CPU stack growth order (see Note #1).        */

#define  CPU_CFG_STK_ALIGN_BYTES  (8u)                          /* Defines CPU stack alignment in bytes. (see Note #2). */

typedef  CPU_INT32U               CPU_STK;                      /* Defines CPU stack data type.                         */
typedef  CPU_ADDR                 CPU_STK_SIZE;                 /* Defines CPU stack size data type.                    */


/*
*********************************************************************************************************
*                                   CRITICAL SECTION CONFIGURATION
*
* Note(s) : (1) Configure CPU_CFG_CRITICAL_METHOD with CPU's/compiler's critical section method :
*
*                                                       Enter/Exit critical sections by ...
*
*                   CPU_CRITICAL_METHOD_INT_DIS_EN      Disable/Enable interrupts
*                   CPU_CRITICAL_METHOD_STATUS_STK      Push/Pop       interrupt status onto stack
*                   CPU_CRITICAL_METHOD_STATUS_LOCAL    Save/Restore   interrupt status to local variable
*
*               (a) CPU_CRITICAL_METHOD_INT_DIS_EN  is NOT a preferred method since it does NOT support
*                   multiple levels of interrupts.  However, with some CPUs/compilers, this is the only
*                   available method.
*
*               (b) CPU_CRITICAL_METHOD_STATUS_STK    is one preferred method since it supports multiple
*                   levels of interrupts.  However, this method assumes that the compiler provides C-level
*                   &/or assembly-level functionality for the following :
*
*                     ENTER CRITICAL SECTION :
*                       (1) Push/save   interrupt status onto a local stack
*                       (2) Disable     interrupts
*
*                     EXIT  CRITICAL SECTION :
*                       (3) Pop/restore interrupt status from a local stack
*
*               (c) CPU_CRITICAL_METHOD_STATUS_LOCAL  is one preferred method since it supports multiple
*                   levels of interrupts.  However, this method assumes that the compiler provides C-level
*                   &/or assembly-level functionality for the following :
*
*                     ENTER CRITICAL SECTION :
*                       (1) Save    interrupt status into a local variable
*                       (2) Disable interrupts
*
*                     EXIT  CRITICAL SECTION :
*                       (3) Restore interrupt status from a local variable
*
*           (2) Critical section macro's most likely require inline assembly.  If the compiler does NOT
*               allow inline assembly in C source files, critical section macro's MUST call an assembly
*               subroutine defined in a 'cpu_a.asm' file located in the following software directory :
*
*                   \<CPU-Compiler Directory>\<cpu>\<compiler>\
*
*                       where
*                               <CPU-Compiler Directory>    directory path for common   CPU-compiler software
*                               <cpu>                       directory name for specific CPU
*                               <compiler>                  directory name for specific compiler
*
*           (3) (a) To save/restore interrupt status, a local variable 'cpu_sr' of type 'CPU_SR' MAY need
*                   to be declared (e.g. if 'CPU_CRITICAL_METHOD_STATUS_LOCAL' method is configured).
*
*                   (1) 'cpu_sr' local variable SHOULD be declared via the CPU_SR_ALLOC() macro which, if
*                        used, MUST be declared following ALL other local variables.
*
*                        Example :
*
*                           void  Fnct (void)
*                           {
*                               CPU_INT08U  val_08;
*                               CPU_INT16U  val_16;
*                               CPU_INT32U  val_32;
*                               CPU_SR_ALLOC();         MUST be declared after ALL other local variables
*                                   :
*                                   :
*                           }
*
*               (b) Configure 'CPU_SR' data type with the appropriate-sized CPU data type large enough to
*                   completely store the CPU's/compiler's status word.
*********************************************************************************************************
*/
                                                                /* Configure CPU critical method      (see Note #1) :   */
#define  CPU_CFG_CRITICAL_METHOD    CPU_CRITICAL_METHOD_STATUS_LOCAL

typedef  CPU_INT32U                 CPU_SR;                     /* Defines   CPU status register size (see Note #3b).   */

                                                                /* Allocates CPU status register word (see Note #3a).   */
#if     (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
#define  CPU_SR_ALLOC()             CPU_SR  cpu_sr = (CPU_SR)0
#else
#define  CPU_SR_ALLOC()
#endif



#define  CPU_INT_DIS()         do { cpu_sr = CPU_SR_Save(); } while (0) /* Save    CPU status word & disable interrupts.*/
#define  CPU_INT_EN()          do { CPU_SR_Restore(cpu_sr); } while (0) /* Restore CPU status word.                     */


#ifdef   CPU_CFG_INT_DIS_MEAS_EN
                                                                        /* Disable interrupts, ...                      */
                                                                        /* & start interrupts disabled time measurement.*/
#define  CPU_CRITICAL_ENTER()  do { CPU_INT_DIS();         \
                                    CPU_IntDisMeasStart(); }  while (0)
                                                                        /* Stop & measure   interrupts disabled time,   */
                                                                        /* ...  & re-enable interrupts.                 */
#define  CPU_CRITICAL_EXIT()   do { CPU_IntDisMeasStop();  \
                                    CPU_INT_EN();          }  while (0)

#else

#define  CPU_CRITICAL_ENTER()  do { CPU_INT_DIS(); } while (0)          /* Disable   interrupts.                        */
#define  CPU_CRITICAL_EXIT()   do { CPU_INT_EN();  } while (0)          /* Re-enable interrupts.                        */

#endif


/*
*********************************************************************************************************
*                                    MEMORY BARRIERS CONFIGURATION
*
* Note(s) : (1) (a) Configure memory barriers if required by the architecture.
*
*                   CPU_MB      Full memory barrier.
*                   CPU_RMB     Read (Loads) memory barrier.
*                   CPU_WMB     Write (Stores) memory barrier.
*
*********************************************************************************************************
*/

#define  CPU_MB()       __DSB()
#define  CPU_RMB()      __DSB()
#define  CPU_WMB()      __DSB()


/*
*********************************************************************************************************
*                                         ARM EXCEPTIONS VECTORS
*
* Note(s) : (1) Exceptions are taken whenever the normal flow of a program MUST temporarily halt,
*               for example, to service an interrupt from a peripheral. The ARM architecture has
*               the following execption vectors.
*
*                   CPU_ARM_EXCEPT_RST              Reset exception.
*                   CPU_ARM_EXCEPT_UND              Undefined instruction.
*                   CPU_ARM_EXCEPT_SWI              Software interrupt.
*                   CPU_ARM_EXCEPT_ABORT_PREFETCH   Prefetch Abort.
*                   CPU_ARM_EXCEPT_ABORT_DATA       Data Abort.
*                   CPU_ARM_EXCEPT_IRQ              Interrupt request.
*                   CPU_ARM_EXCEPT_FIQ              Fast Interrupt Request.
*********************************************************************************************************
*/

#define  CPU_ARM_EXCEPT_RST                               0u
#define  CPU_ARM_EXCEPT_UND                               1u
#define  CPU_ARM_EXCEPT_SWI                               2u
#define  CPU_ARM_EXCEPT_ABORT_PREFETCH                    3u
#define  CPU_ARM_EXCEPT_ABORT_DATA                        4u
#define  CPU_ARM_EXCEPT_RSVD                              5u
#define  CPU_ARM_EXCEPT_IRQ                               6u
#define  CPU_ARM_EXCEPT_FIQ                               7u


/*
*********************************************************************************************************
*                     ARM CORTEX-A8 PROGRAM STATUS REGISTER BIT & BIT-FIELDS DEFINES
*********************************************************************************************************
*/

#define  CPU_ARM_BIT_CPSR_N                     DEF_BIT_31
#define  CPU_ARM_BIT_CPSR_Z                     DEF_BIT_30
#define  CPU_ARM_BIT_CPSR_C                     DEF_BIT_29
#define  CPU_ARM_BIT_CPSR_V                     DEF_BIT_28
#define  CPU_ARM_BIT_CPSR_Q                     DEF_BIT_27
#define  CPU_ARM_BIT_CPSR_J                     DEF_BIT_24
#define  CPU_ARM_MSK_CPSR_GE                    DEF_BIT_FIELD(4u, 16u)

#define  CPU_ARM_BIT_CPSR_E                     DEF_BIT_09
#define  CPU_ARM_BIT_CPSR_A                     DEF_BIT_08
#define  CPU_ARM_BIT_CPSR_I                     DEF_BIT_07
#define  CPU_ARM_BIT_CPSR_F                     DEF_BIT_06
#define  CPU_ARM_BIT_CPSR_T                     DEF_BIT_05
#define  CPU_ARM_MSK_CPSR_MODE                  DEF_BIT_FIELD(5u, 0u)
#define  CPU_ARM_BIT_CPSR_MODE_USER                    0x10u
#define  CPU_ARM_BIT_CPSR_MODE_FIQ                     0x11u
#define  CPU_ARM_BIT_CPSR_MODE_IRQ                     0x12u
#define  CPU_ARM_BIT_CPSR_MODE_SUPERVISOR              0x13u
#define  CPU_ARM_BIT_CPSR_MODE_ABORT                   0x17u
#define  CPU_ARM_BIT_CPSR_MODE_UNDEFINED               0x1Bu
#define  CPU_ARM_BIT_CPSR_MODE_SYSTEM                  0x1Fu

/*
*********************************************************************************************************
*                              ARM CORTEX-A8 FLOATING POINT UNIT BIT DEFINES
*********************************************************************************************************
*/

#define  CPU_ARM_BIT_FPEXC_EN                   DEF_BIT_30


/*
*********************************************************************************************************
*                          ARM CORTEX-A8 EVENTS AND PERFORMANCE MONITOR
*
* Note(s) : (1) The Performance Monitoring Unit (PMU) includes logic to detect various events
*               that can occur. This events can be counted using the registers in the PMU.
*********************************************************************************************************
*/

#define  CPU_ARM_EVENT_SOFT_INC                        0x00u    /* Software increment.                                  */

#define  CPU_ARM_EVENT_INST_CACHE_MISS                 0x01u    /* Instruction cache miss.                              */
#define  CPU_ARM_EVENT_INST_CACHE_TAG_ERR              0x4Au    /* Instruction cache tag RAM parity or ECC err.         */
#define  CPU_ARM_EVENT_INST_CACHE_DATA_ERR             0x4Bu    /* Instruction cache data RAM parity or ECC err.        */
#define  CPU_ARM_EVENT_INST_EXECUTED                   0x08u    /* Instruciton architecturally executed.                */
#define  CPU_ARM_EVENT_INST_DUAL_ISSUED                0x5Eu    /* Dual-issued pair of instructions architecturally ... */
                                                                /* ... executed.                                        */
#define  CPU_ARM_EVENT_INST_BRANCH_EXECUTED            0x0Du    /* B immediate, BL immediate or BLX immediate ...       */
                                                                /* ... instruction architecturally executed.            */
#define  CPU_ARM_EVENT_INST_RETURN_EXECUTED            0x0Eu    /* Procedure return architecturally executed other ...  */
                                                                /* ... than exception returns.                          */
#define  CPU_ARM_EVENT_INST_BUFFER_STALL               0x40u    /* Stall because instruction buffer cannot deliver ...  */
                                                                /* ... an instruction.                                  */
#define  CPU_ARM_EVENT_UNALIGN_ACCESS                  0x0Fu    /* Unaligned access architecturally executed.           */
#define  CPU_ARM_EVENT_BRANCH_MISPREDICTED             0x10u    /* Branch mispredicted or not predicted.                */
#define  CPU_ARM_EVENT_BRANCH_PREDICTED                0x12u    /* Branches or other change in program flow that ...    */
                                                                /* .. could have been predicted by the branch ...       */
                                                                /* .. prediction Resources of the processor             */
#define  CPU_ARM_EVENT_CYCLE_CNT                       0x11u    /* Cycle count.                                         */
#define  CPU_ARM_EVENT_EXCEPT_TAKEN                    0x09u    /* Exception taken.                                     */
#define  CPU_ARM_EVENT_EXCEPT_RETURN                   0x0Au    /* Exception return architecturally executed.           */
#define  CPU_ARM_EVENT_CTX_ID_CHANGE                   0x0Bu    /* Change to Context ID executed.                       */
#define  CPU_ARM_EVENT_SOFT_PC_CHANGE                  0x0Cu    /* Software change of PC, except by an exception, ...   */
                                                                /* ... architecturally executed.                        */
#define  CPU_ARM_EVENT_DATA_CACHE_MISS                 0x03u    /* Data cache miss.                                     */
#define  CPU_ARM_EVENT_DATA_CACHE_ACCESS               0x04u    /* Data cache access.                                   */
#define  CPU_ARM_EVENT_DATA_READ                       0x06u    /* Data Read  architecturally executed.                 */
#define  CPU_ARM_EVENT_DATA_WRITE                      0x07u    /* Data Write architecturally executed.                 */
#define  CPU_ARM_EVENT_DATA_CACHE_WR_BACK              0x42u    /* Data cache write-back.                               */
#define  CPU_ARM_EVENT_DATA_CACHE_TAG_ERR              0x4Cu    /* Data cache tag or dirty RAM parity error or ECC err. */
#define  CPU_ARM_EVENT_DATA_CACHE_DATA_ERR             0x4Du    /* Data cache data RAM parity error or ECC err.         */
#define  CPU_ARM_EVENT_EXT_MEM_REQ                     0x43u    /* Exernal Memory request.                              */

#define  CPU_ARM_EVENT_LSU_STALL_BUSY                  0x44u    /* Stall becasue of LSU being busy.                     */
#define  CPU_ARM_EVENT_LSU_STALL_BUF_FULL              0x51u    /* LSU stall caused by full store buffer.               */
#define  CPU_ARM_EVENT_LSU_STALL_Q_FULL                0x52u    /* LSU stall caused by store queue full.                */

#define  CPU_ARM_EVENT_STO_FORCE_DRAIN                 0x45u    /* Store buffer was forced to drain completely.         */
#define  CPU_ARM_EVENT_STO_MERGE                       0x50u    /* Store buffer merge.                                  */

#define  CPU_ARM_EVENT_FIQ_INT_DIS                     0x46u    /* The number of cyles FIQ interrupts are disabled.     */
#define  CPU_ARM_EVENT_IRQ_INT_DIS                     0x47u    /* The number of cyles IRQ interrupts are disabled.     */

#define  CPU_ARM_EVENT_TCM_ERR_PAR_PREFETCH_FATAL      0x4Eu    /* TCM parity error or fatal ECC error reported ...     */
                                                                /* ... from the prefetch unit.                          */
#define  CPU_ARM_EVENT_TCM_ERR_PAR_LOAD_STORE_FATAL    0x4Fu    /* TCM parity error or fatal ECC error reported ...     */
                                                                /* ... from the load/store unit.                        */

#define  CPU_ARM_EVENT_INSTR_INT_DIV_EXEC              0x53u    /* Integer divide instruction SDIV or UDIV executed.    */
#define  CPU_ARM_EVENT_STALL_CYCLE_INT_DIV             0x54u    /* Stall cycle caused by integer divide.                */

#define  CPU_ARM_EVENT_INSTR_PLD_LINE_FILL             0x55u    /* PLD instruction that initiates a linefill.           */
#define  CPU_ARM_EVENT_INSTR_PLD_LINE_FILL_STOP        0x56u    /* PLD instruction that did not initiate a linefill ... */
                                                                /* ... because of a resource shortage.                  */
#define  CPU_ARM_EVENT_AXI_NON_CACHE_ACCESS            0x57u    /* Non-cacheable access on AXI master bus.              */
#define  CPU_ARM_EVENT_STO_CACHE_LINE                  0x59u    /* Store buffer operation has detected that two ...     */
                                                                /* ... slots have data in same cache line but with ...  */
                                                                /* ... different attributes.                            */
#define  CPU_ARM_EVENT_DUAL_ISSUE_BRANCH               0x5Au    /* Dual issue case A (branch).                          */
#define  CPU_ARM_EVENT_DUAL_ISSUE_LOAD_STORE           0x5Bu    /* Dual issue case B1, B2, F2 (load/store), F2D.        */
#define  CPU_ARM_EVENT_DUAL_ISSUE_OTHER                0x5Cu    /* Dual issue other.                                    */
#define  CPU_ARM_EVENT_INSTR_FP_EXEC                   0x5Du    /* Double precision floating point arithmetic or ...    */
                                                                /* ... conversion instruction executed.                 */
#define  CPU_ARM_EVENT_DATA_CACHE_DATA_FATAL_ERR       0x60u    /* Data cache data RAM fatal ECC error.                 */
#define  CPU_ARM_EVENT_DATA_CACHE_TAG_FATAL_ERR        0x61u    /* Data cache tag/dirty RAM fatal ECC error.            */
#define  CPU_ARM_EVENT_LIVELOCK                        0x62u    /* Processor livelock because of hard errors or ...     */
                                                                /* ... exception at exception vector.a                  */
#define  CPU_ARM_EVENT_ATCM_ERR_PAR                    0x64u    /* ATCM  parity or multi-bit ECC error.                 */
#define  CPU_ARM_EVENT_ATCM_ERR_BIT                    0x67u    /* ATCM  single-bit ECC error.                          */
#define  CPU_ARM_EVENT_BOTCM_ERR_PAR                   0x65u    /* B0TCM parity or multi-bit ECC error.                 */
#define  CPU_ARM_EVENT_B0TCM_ERR_BIT                   0x68u    /* B0TCM single-bit ECC error.                          */
#define  CPU_ARM_EVENT_B1TCM_ERR_PAR                   0x66u    /* B1TCM parity or multi-bit ECC error.                 */
#define  CPU_ARM_EVENT_B1TCM_ERR_BIT                   0x69u    /* B1TCM single-bit ECC error.                          */

#define  CPU_ARM_EVENT_TCM_ERR_LOAD_STORE              0x6Au    /* TCM correctable ECC error reported by load/store...  */
                                                                /* ... unit.                                            */
#define  CPU_ARM_EVENT_TCM_ERR_PREFETCH                0x6Bu    /* Correctable ECC error reported by prefetch unit.     */
#define  CPU_ARM_EVENT_TCM_ERR_AXI_FATAL               0x6Cu    /* TCM parity or fatal ECC error reported by AXI ...    */
                                                                /* ... slave interface.                                 */
#define  CPU_ARM_EVENT_TCM_ERR_AXI                     0x6Du    /* TCM correctable ECC error reported by AXI slave ...  */
                                                                /* ... interface.                                       */

/*
*********************************************************************************************************
*                             ARM CORTEX-A8 MEMORY PROTECTION UNIT DEFINES
*********************************************************************************************************
*/

#define  CPU_ARM_MMU_ACCESS_REG_BIT_B                           DEF_BIT_00
#define  CPU_ARM_MMU_ACCESS_REG_BIT_C                           DEF_BIT_01
#define  CPU_ARM_MMU_ACCESS_REG_BIT_TEX_0                       DEF_BIT_03
#define  CPU_ARM_MMU_ACCESS_REG_BIT_TEX_1                       DEF_BIT_04
#define  CPU_ARM_MMU_ACCESS_REG_BIT_TEX_2                       DEF_BIT_05

                                                                /* ------------- ACCESS PERMISSION DEFINES ------------ */
#define  CPU_ARM_MMU_ACCESS_PERM_NO_ACCESS                      DEF_BIT_MASK(0u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_PRIV_FULL                      DEF_BIT_MASK(1u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_USER_RD                        DEF_BIT_MASK(2u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_USER_FULL                      DEF_BIT_MASK(3u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_RSVD_00                        DEF_BIT_MASK(0u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_PRIV_RD                        DEF_BIT_MASK(5u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_PRIV_USER_RD                   DEF_BIT_MASK(6u, 8u)
#define  CPU_ARM_MMU_ACCESS_PERM_RSVD_01                        DEF_BIT_MASK(7u, 8u)

#define  CPU_ARM_MMU_ACCESS_SHARE                               DEF_BIT_02
#define  CPU_ARM_MMU_ACCESS_EXECUTE_NEVER                       DEF_BIT_12

                                                                /* ----------- MEMORY ACCESS TYPE ATTRIBUTES ---------- */
#define  CPU_ARM_MMU_ACCESS_TYPE_STRONG_ORDERED                 DEF_BIT_NONE
#define  CPU_ARM_MMU_ACCESS_TYPE_DEV_SHARED                     (                                                                  CPU_ARM_MMU_ACCESS_REG_BIT_B)
#define  CPU_ARM_MMU_ACCESS_TYPE_DEV                            (CPU_ARM_MMU_ACCESS_REG_BIT_TEX_1                                                              )

#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_OI_WT                   (                                   CPU_ARM_MMU_ACCESS_REG_BIT_C                               )
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_OI_WB                   (                                   CPU_ARM_MMU_ACCESS_REG_BIT_C | CPU_ARM_MMU_ACCESS_REG_BIT_B)
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_OI_NONE                 (CPU_ARM_MMU_ACCESS_REG_BIT_TEX_0                                                              )
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_OI_WBA                  (CPU_ARM_MMU_ACCESS_REG_BIT_TEX_0 | CPU_ARM_MMU_ACCESS_REG_BIT_C | CPU_ARM_MMU_ACCESS_REG_BIT_B)

#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_CACHE(inner, outer)     (CPU_ARM_MMU_ACCESS_REG_BIT_TEX_2 | ((inner << 3u)) | (outer))
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_CACHE_OPT_NONE           DEF_BIT_NONE
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_CACHE_OPT_WBA            DEF_BIT_00
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_CACHE_OPT_WT             DEF_BIT_01
#define  CPU_ARM_MMU_ACCESS_TYPE_NORMAL_CACHE_OPT_WB            (DEF_BIT_00 | DEF_BIT_01)


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*
* Note(s) : (1) CPU_CntLeadZeros() prototyped/defined respectively in :
*
*               (a) 'cpu.h'/'cpu_a.asm',       if CPU_CFG_LEAD_ZEROS_ASM_PRESENT      #define'd in 'cpu.h'/
*                                                 'cpu_cfg.h' to enable assembly-version function
*
*               (b) 'cpu_core.h'/'cpu_core.c', if CPU_CFG_LEAD_ZEROS_ASM_PRESENT  NOT #define'd in 'cpu.h'/
*                                                 'cpu_cfg.h' to enable C-source-version function otherwise
*
*               See also 'cpu_core.h  FUNCTION PROTOTYPES  Note #2'.
*
*          (2) CPU_PMU_xxx() functions are intended to manage the Event & Performanace Monitor unit (PMU).
*********************************************************************************************************
*/

CPU_SR       CPU_SR_Save        (void);
void         CPU_SR_Restore     (CPU_SR  cpu_sr);

void         CPU_IntEn          (void);
void         CPU_IntDis         (void);

void         CPU_IRQ_En         (void);
void         CPU_IRQ_Dis        (void);

void         CPU_FIQ_En         (void);
void         CPU_FIQ_Dis        (void);

#define CPU_CFG_LEAD_ZEROS_ASM_PRESENT                          /* See Note #1.                                         */
CPU_DATA     CPU_CntLeadZeros   (CPU_DATA    val);
                                                                /* See Note #2                                          */
void         CPU_PMU_Dis        (void);
void         CPU_PMU_En         (void);
void         CPU_PMU_Rst        (void);

                                                                /* Event counter functions.                             */
void         CPU_PMU_CtrDis     (CPU_INT08U  ctr);
void         CPU_PMU_CtrEn      (CPU_INT08U  ctr);
void         CPU_PMU_CtrEventSet(CPU_INT08U  ctr,
                                 CPU_INT08U  event);
CPU_DATA     CPU_PMU_CtrGet     (CPU_INT08U  ctr);
void         CPU_PMU_CtrRst     (CPU_INT08U  ctr);
                                                                /* Cycle counter functions.                             */
void         CPU_PMU_CtrCycleDis(void);
void         CPU_PMU_CtrCycleEn (void);
CPU_DATA     CPU_PMU_CtrCycleGet(void);
CPU_DATA     CPU_PMU_CtrCycleRst(void);

                                                                /* MMU functions                                        */
void         CPU_MMU_Init       (void);
void         CPU_MMU_En         (void);
void         CPU_MMU_Dis        (void);
CPU_BOOLEAN  CPU_MMU_RegionEn   (CPU_INT08U  nbr,
                                 CPU_ADDR    addr,
                                 CPU_INT08U  sub_reg_en,
                                 CPU_INT32U  size,
                                 CPU_INT32U  acess_attrib);
void         CPU_MMU_RegionDis  (CPU_INT08U  nbr);

void         CPU_CtxID_Set      (CPU_INT32U  ctx_id);
CPU_INT32U   CPU_CtxID_Get      (void);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  CPU_CFG_ADDR_SIZE
#error  "CPU_CFG_ADDR_SIZE              not #define'd in 'cpu.h'               "
#error  "                         [MUST be  CPU_WORD_SIZE_08   8-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_16  16-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_32  32-bit alignment]"

#elif  ((CPU_CFG_ADDR_SIZE != CPU_WORD_SIZE_08) && \
        (CPU_CFG_ADDR_SIZE != CPU_WORD_SIZE_16) && \
        (CPU_CFG_ADDR_SIZE != CPU_WORD_SIZE_32))
#error  "CPU_CFG_ADDR_SIZE        illegally #define'd in 'cpu.h'               "
#error  "                         [MUST be  CPU_WORD_SIZE_08   8-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_16  16-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_32  32-bit alignment]"
#endif


#ifndef  CPU_CFG_DATA_SIZE
#error  "CPU_CFG_DATA_SIZE              not #define'd in 'cpu.h'               "
#error  "                         [MUST be  CPU_WORD_SIZE_08   8-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_16  16-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_32  32-bit alignment]"

#elif  ((CPU_CFG_DATA_SIZE != CPU_WORD_SIZE_08) && \
        (CPU_CFG_DATA_SIZE != CPU_WORD_SIZE_16) && \
        (CPU_CFG_DATA_SIZE != CPU_WORD_SIZE_32))
#error  "CPU_CFG_DATA_SIZE        illegally #define'd in 'cpu.h'               "
#error  "                         [MUST be  CPU_WORD_SIZE_08   8-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_16  16-bit alignment]"
#error  "                         [     ||  CPU_WORD_SIZE_32  32-bit alignment]"
#endif




#ifndef  CPU_CFG_ENDIAN_TYPE
#error  "CPU_CFG_ENDIAN_TYPE            not #define'd in 'cpu.h'   "
#error  "                         [MUST be  CPU_ENDIAN_TYPE_BIG   ]"
#error  "                         [     ||  CPU_ENDIAN_TYPE_LITTLE]"

#elif  ((CPU_CFG_ENDIAN_TYPE != CPU_ENDIAN_TYPE_BIG   ) && \
        (CPU_CFG_ENDIAN_TYPE != CPU_ENDIAN_TYPE_LITTLE))
#error  "CPU_CFG_ENDIAN_TYPE      illegally #define'd in 'cpu.h'   "
#error  "                         [MUST be  CPU_ENDIAN_TYPE_BIG   ]"
#error  "                         [     ||  CPU_ENDIAN_TYPE_LITTLE]"
#endif




#ifndef  CPU_CFG_STK_GROWTH
#error  "CPU_CFG_STK_GROWTH             not #define'd in 'cpu.h'    "
#error  "                         [MUST be  CPU_STK_GROWTH_LO_TO_HI]"
#error  "                         [     ||  CPU_STK_GROWTH_HI_TO_LO]"

#elif  ((CPU_CFG_STK_GROWTH != CPU_STK_GROWTH_LO_TO_HI) && \
        (CPU_CFG_STK_GROWTH != CPU_STK_GROWTH_HI_TO_LO))
#error  "CPU_CFG_STK_GROWTH       illegally #define'd in 'cpu.h'    "
#error  "                         [MUST be  CPU_STK_GROWTH_LO_TO_HI]"
#error  "                         [     ||  CPU_STK_GROWTH_HI_TO_LO]"
#endif




#ifndef  CPU_CFG_CRITICAL_METHOD
#error  "CPU_CFG_CRITICAL_METHOD        not #define'd in 'cpu.h'             "
#error  "                         [MUST be  CPU_CRITICAL_METHOD_INT_DIS_EN  ]"
#error  "                         [     ||  CPU_CRITICAL_METHOD_STATUS_STK  ]"
#error  "                         [     ||  CPU_CRITICAL_METHOD_STATUS_LOCAL]"

#elif  ((CPU_CFG_CRITICAL_METHOD != CPU_CRITICAL_METHOD_INT_DIS_EN  ) && \
        (CPU_CFG_CRITICAL_METHOD != CPU_CRITICAL_METHOD_STATUS_STK  ) && \
        (CPU_CFG_CRITICAL_METHOD != CPU_CRITICAL_METHOD_STATUS_LOCAL))
#error  "CPU_CFG_CRITICAL_METHOD  illegally #define'd in 'cpu.h'             "
#error  "                         [MUST be  CPU_CRITICAL_METHOD_INT_DIS_EN  ]"
#error  "                         [     ||  CPU_CRITICAL_METHOD_STATUS_STK  ]"
#error  "                         [     ||  CPU_CRITICAL_METHOD_STATUS_LOCAL]"
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#ifdef __cplusplus
}
#endif

#endif                                                          /* End of CPU module include.                           */

