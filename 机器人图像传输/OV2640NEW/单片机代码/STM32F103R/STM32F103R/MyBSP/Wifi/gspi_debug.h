/*
 *	Debugging macros
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#ifdef	DEBUG_SSP_LEVEL2
#ifndef DEBUG_LEVEL1
#define	DEBUG_LEVEL1
#endif
#define	_ENTER() printk(KERN_DEBUG "Enter: %s, %s linux %i\n", __FUNCTION__, \
							__FILE__, __LINE__)
#define	_LEAVE() printk(KERN_DEBUG "Leave: %s, %s linux %i\n", __FUNCTION__, \
							__FILE__, __LINE__)
#else
#define _ENTER()
#define _LEAVE()
#endif

#ifdef	DEBUG_SSP_LEVEL1
#define	_DBGMSG(x...)		printk(KERN_DEBUG x)
#define	_WARNING(x...)		printk(KERN_WARNING x)
extern void gspi_asciidump8(char *prompt, u8 * p, int size);
extern void gspi_asciidump16(char *prompt, u16 * p, int size);
extern void gspi_hexdump16(char *prompt, u16 * p, int size);
extern void gspi_hexdump8(char *prompt, u16 * p, int size);
#else
#define	_DBGMSG(x...)
#define	_WARNING(x...)
#endif

#ifdef DEBUG_SSP_LEVEL0
#define	_PRINTK(x...)		printk(x)
#define	_ERROR(x...)		printk(KERN_ERR x)
#else
#define	_PRINTK(x...)
#define	_ERROR(x...)
#endif
