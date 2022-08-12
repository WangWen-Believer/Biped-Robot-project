/*
 * 	File: gspi_io.c
 * 	Desc: Low level SSP driver on pxa27x for GSPI
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
	01/30/06: Add kernel 2.6 support for GSPI8xxx/Bulverde
********************************************************/

#include	"gspi_io.h"
#include	"gspi_debug.h"

#define USE_DMA				1
#define SSP_SFRM			24
#define SSP_IRQ				22
#define GSPI_DIRECT_MAJOR		240
#define SFRM_DOWN			0
#define SFRM_UP				1

#define MODULE_GET	if(try_module_get(THIS_MODULE)==0) return -1;
#define MODULE_PUT	module_put(THIS_MODULE)

static inline void ssp_sfrm(int updown);
gspihost_info_t *G_gspiinfo;
static int major = GSPI_DIRECT_MAJOR;
static int clkdiv = 0;
volatile int dma_transfer = 0;

int g_dummy_clk_reg = 0;
int g_dummy_clk_ioport = 0;
int g_bus_mode_reg = 0x02;
EXPORT_SYMBOL(g_dummy_clk_reg);
EXPORT_SYMBOL(g_dummy_clk_ioport);
EXPORT_SYMBOL(g_bus_mode_reg);

static void gspihost_exit(gspihost_info_t * gspiinfo);
static inline void
ssp_sfrm(int updown)
{
    /*if (updown == SFRM_DOWN)
        GPCR0 = (1 << SSP_SFRM);        ///Pull SFRM signal down
    else
        GPSR0 = (1 << SSP_SFRM);        ///Pull SFRM signal up */
    return;
}

static void
dma_irqr(int dma, void *devid, struct pt_regs *regs)
{
   
    return;
}

static void
dma_irqw(int dma, void *devid, struct pt_regs *regs)
{
    gspihost_info_t *gspiinfo = (gspihost_info_t *) devid;
    return;
}

static inline int
gspi_acquire_io(gspihost_info_t * gspiinfop)
{
    int ret;

    return ret;
}

static inline void
gspi_release_io(gspihost_info_t * gspiinfop)
{
    return;
}

static void
cleanup_dma_allocated_memory(gspihost_info_t * gspiinfo)
{

}

static int
dma_init(gspihost_info_t * gspiinfo)
{
    return -1;
}

static int
gspihost_open(struct inode *inode, struct file *filp)
{
   
    return 0;
}

static int
gspihost_release(struct inode *inode, struct file *filp)
{
  
    return 0;
}

static int
gspihost_ioctl(struct inode *inode, struct file *filp,
               unsigned int cmd, unsigned long arg)
{
    
    return -ENOIOCTLCMD;
}

static struct file_operations gspihost_fops = {
  owner:THIS_MODULE,
  open:gspihost_open,
  ioctl:gspihost_ioctl,
  release:gspihost_release,
};

void
setup_write_dma(gspihost_info_t * gspiinfo, int n)
{
   
}

int
gspi_write_data_direct(u8 * data, u16 reg, u16 n)
{
    return 0;
}

int
gspi_write_reg(  u16 reg, u16 val)
{
    gspi_write_data_direct(  (u8 *) & val, reg, 2);

    return 0;
}

int
gspi_write_data(  u16 * data, u16 size)
{
    gspi_write_data_direct(  (u8 *) & data[1], data[0], 2);

    return 0;
}

void
gspi_write_to_read(gspihost_info_t * gspiinfo, int n)
{
    
}

void
setup_read_dma(gspihost_info_t * gspiinfo, u16 reg, u8 * data, int n)
{
    
}

int
gspi_read_data_direct(  u8 * data, u16 reg, u16 n)
{

    return 0;
}

int
gspi_read_data(  u16 * data, u16 size)
{
    return gspi_read_data_direct(  (u8 *) & data[1], data[0], 2);
}

int
gspi_read_reg(  u16 reg, u16 * val)
{

    return 0;
}

int
gspi_register_irq(gspihost_info_p gspiinfo)
{
    return 0;
}

void
gspi_unregister_irq(gspihost_info_p gspihost)
{
}

gspi_notifier_rec_p
register_user(gspi_notifier_rec_p notifierp)
{
    return 0;
}

void
unregister_user(gspi_notifier_rec_p notifierp)
{

}

static int
gspihost_init_hw(gspihost_info_t * gspiinfo)
{
    return 0;
}

static gspihost_info_t *
gspihost_init(void)
{
    
    return gspiinfo;
}

void
gspi_reset(void)
{
}

static int __init
gspihost_module_init(void)
{
  
    return 0;
}

static void
gspihost_exit(gspihost_info_t * gspiinfo)
{
    
}

static void __exit
gspihost_module_exit(void)
{

}

