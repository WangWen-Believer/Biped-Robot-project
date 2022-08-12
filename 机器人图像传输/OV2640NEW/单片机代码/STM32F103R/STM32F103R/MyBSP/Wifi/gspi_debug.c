/*
	File	: gspi_debug.c
	This file contains debug functions

	Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
*/

#include <linux/kernel.h>

void
gspi_hexdump8(char *prompt, u8 * p, int size)
{
    int i;

    printk("%s: ", prompt);

    for (i = 0; i < size; ++i)
        printk("%02x ", p[i]);

    printk("\n");
}

void
gspi_hexdump16(char *prompt, u16 * p, int size)
{
    int i;

    printk("%s: ", prompt);

    for (i = 0; i < size; ++i)
        printk("%04x ", p[i]);

    printk("\n");
}

#ifdef DEBUG
void
gspi_asciidump8(char *prompt, u8 * p, int size)
{
    printk(KERN_DEBUG "%s: ", prompt);

    while (size--)
        printk("%c", *p++);

    printk("\n");
}

void
gspi_asciidump16(char *prompt, u16 * p, int size)
{
    printk(KERN_DEBUG "%s: ", prompt);

    while (size--)
        printk("%c", *p++);

    printk("\n");
}

#endif /* DEBUG */
