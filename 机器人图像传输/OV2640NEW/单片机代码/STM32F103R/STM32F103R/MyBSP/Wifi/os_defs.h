/*
 * Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#ifndef _OS_HEADER1_
#define _OS_HEADER1_

typedef char CHAR;
typedef char *PCHAR;
typedef u8 *PUCHAR;
typedef u16 *PUSHORT;
typedef long *PLONG;
typedef PLONG LONG_PTR;
typedef u32 *ULONG_PTR;
typedef u32 *Pu32;
typedef unsigned int UINT;
typedef UINT *PUINT;
typedef void VOID;
typedef VOID *PVOID;
typedef int WLAN_STATUS;
typedef u8 BOOLEAN;
typedef BOOLEAN *PBOOLEAN;
typedef PVOID PDRIVER_OBJECT;
typedef PUCHAR PUNICODE_STRING;
typedef long long LONGLONG;
typedef LONGLONG *PLONGLONG;
typedef unsigned long long *PULONGLONG;
typedef PUCHAR ANSI_STRING;
typedef ANSI_STRING *PANSI_STRING;
typedef unsigned short WCHAR;
typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;
typedef struct semaphore SEMAPHORE;

#ifdef __KERNEL__
typedef irqreturn_t IRQ_RET_TYPE;
#define IRQ_RET		return IRQ_HANDLED
#endif /* __KERNEL__ */

#endif /* _OS_HEADER1 */
