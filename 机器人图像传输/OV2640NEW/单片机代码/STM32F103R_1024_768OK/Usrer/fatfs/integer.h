/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

# ifndef _INTEGER_H_H_
# define _INTEGER_H_H_
/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef signed char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

/* Boolean type */
//typedef enum { FALSE = 0, TRUE } BOOL;		//已经在STM32系统文件文件枚举

# endif
