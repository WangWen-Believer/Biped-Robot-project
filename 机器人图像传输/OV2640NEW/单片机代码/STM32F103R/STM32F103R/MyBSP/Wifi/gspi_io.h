/*
 * 	File: gspi_io.h
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
#ifndef _GSPI_IO_H
#define _GSPI_IO_H

#include "stm32f10x.h"

#define PRINTM		printf

#undef SSCR0_DSS
#undef SSCR0_FRF
#undef SSCR0_SCR
#undef SSCR1_RFT
#undef SSCR1_TFT
#define SET_PXA_GPIO_MODE 		pxa_gpio_mode
#define SET_PXA_IRQ_TYPE(gpio) 		set_irq_type(IRQ_GPIO(gpio), IRQT_FALLING)
#define DMA_BUF_ALLOC(flags, paddr,size)	dma_alloc_coherent(NULL, size, paddr, flags);
#define DMA_BUF_FREE(vaddr,paddr,size)		dma_free_coherent(NULL, size, vaddr, paddr);


#define EXTERN extern

#define IRQ_RET_TYPE		void

#define	PXA_SSP_BLKSZ_MAX 		(1<<9)  /* Actually 1023 */
#define	PXA_SSP_BLOCKS_PER_BUFFER 	(3)
#define PXA_SSP_IODATA_SIZE 		(PXA_SSP_BLOCKS_PER_BUFFER * \
							PXA_SSP_BLKSZ_MAX)
#define GSPI_OK				0
typedef struct gspihost_info gspihost_info_t;
typedef gspihost_info_t *gspihost_info_p;
typedef struct gspi_card_rec *gspi_card_rec_p;
typedef struct gspi_card_rec io_card_rec_t;
typedef io_card_rec_t *io_card_rec_p;
typedef struct gspi_notifier_rec gspi_notifier_rec_t;
typedef gspi_notifier_rec_t *gspi_notifier_rec_p;
typedef int (*gspi_notifier_fn_p) (gspi_card_rec_p);

struct gspihost_info
{
    int irq;
    u16 dev_id;
    int dma_init;

    /*
     * DMA Related 
     */

    int chan;                   /* dma channel no                  */
    int chanrw;                 /* dma channel no                */

    dma_addr_t phys_addr;       /* iodata physical address         */
    dma_addr_t phys_addr_rw;    /* iodata physical address              */

    pxa_dma_desc *read_desc;    /* input descriptor array         */
    pxa_dma_desc *rw_desc;      /* input descriptor array           */

    pxa_dma_desc *write_desc;   /* output descriptor 
                                   array virtual address */
    dma_addr_t read_desc_phys_addr;     /* descriptor array 
                                           physical address      */
    dma_addr_t rw_desc_phys_addr;       /* descriptor array 
                                           physical address      */
    dma_addr_t write_desc_phys_addr;    /* descriptor array 
                                           physical address      */
    unsigned char *iodata;      /* I/O data buffer           */
    unsigned char *iorw;        /* I/O data buffer           */

    wait_queue_head_t queue_tx;
    struct semaphore host_sem;
    volatile int dma_txack;

    gspi_card_rec_p card;
};

struct gspi_card_rec
{
    u8 magic[4];
    gspihost_info_p ctrlr;      // Back Reference to Host Controller
    int (*add) (gspi_card_rec_p card);
    int (*remove) (gspi_card_rec_p card);
      IRQ_RET_TYPE(*user_isr) (int, void *, struct pt_regs *);
    void *user_arg;
    u16 chiprev;
};

struct gspi_notifier_rec
{
    int (*add) (gspi_card_rec_p card);
    int (*remove) (gspi_card_rec_p card);
      IRQ_RET_TYPE(*user_isr) (int, void *, struct pt_regs *);
};

EXTERN int gspi_read_reg(  u16 reg, u16 * data);
EXTERN int gspi_write_reg(  u16 reg, u16 data);
EXTERN int gspi_read_data(  u16 * data, u16 size);
EXTERN int gspi_write_data(  u16 * data, u16 size);
EXTERN int gspi_read_data_direct( 
                                 u8 * data, u16 reg, u16 size);
EXTERN int gspi_write_data_direct( 
                                  u8 * data, u16 reg, u16 size);
EXTERN int gspi_register_irq(gspihost_info_p);
EXTERN void gspi_unregister_irq(gspihost_info_p);
EXTERN void gspi_reset(void);
EXTERN gspi_notifier_rec_p register_user(gspi_notifier_rec_p notifierp);
EXTERN void unregister_user(gspi_notifier_rec_p notifierp);


#endif /* _GSPI_IO_H */
