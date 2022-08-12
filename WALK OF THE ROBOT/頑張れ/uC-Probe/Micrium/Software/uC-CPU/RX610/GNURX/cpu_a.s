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
;                                      Renesas RX610 Specific code
;                                          GNU RX C Compiler
;
; Filename      : cpu_a.s
; Version       : V1.30.02.00
; Programmer(s) : FGK
;********************************************************************************************************


;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

	.global     _set_ipl
	.global     _get_ipl
	
	.text


;********************************************************************************************************
;                                        set_ipl() & get_ipl()
;
; Description: Set or retrieve interrupt priority level.
;********************************************************************************************************

_set_ipl:
	PUSH R2
    MVFC PSW, R2
	AND  #-0F000001H, R2
	SHLL #24, R1
	OR   R1, R2 	
    MVTC R2, PSW
	POP  R2
	RTS
	
_get_ipl:
    MVFC PSW, R1
	SHLR #24, R1
	AND  #15, R1
	RTS


    .END

