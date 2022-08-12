/********************************************************************************************************
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
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/********************************************************************************************************
*
*                                            CPU PORT FILE
*
*                                      Renesas RL78 Specific code
*                                          GNU RL78 C Compiler
*
* Filename      : cpu_a.asm
* Version       : V1.30.02.00
* Programmer(s) : MD
*********************************************************************************************************
*/

#include  <cpu.h>


/********************************************************************************************************
*                                    set_interrupt_state & get_interrupt_state
*
* Description: Set or retrieve interrupt priority level.
* KPIT GNU Work around for set and get interrupt states
*********************************************************************************************************
*/

void __set_interrupt_state(CPU_INT08U cpu_sr){
    if (cpu_sr)
        asm("EI");
    else
        asm("DI");
}
	
CPU_INT08U __get_interrupt_state(void){

    CPU_INT08U  cpu_sr;


    asm(" MOV  A, PSW");                                        /* Get Process Status Word Register PSW value           */
    asm(" SHR  A, 7");                                          /* Save only the Interrupt Enabled (IE) Bit             */
    asm(" MOV  %0, A" : "=r"(cpu_sr));                          /* Save IE bit value into cpu_sr                        */       //__asm

    return(cpu_sr);
}

