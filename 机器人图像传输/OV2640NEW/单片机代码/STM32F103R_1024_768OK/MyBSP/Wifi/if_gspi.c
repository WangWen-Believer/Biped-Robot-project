/** @file if_gspi.c
  * @brief This file contains generic GSPI functions
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
  */
/********************************************************
Change log:
	09/26/05: Add Doxygen format comments
	10/20/05: Add GSPI8686 support
	01/30/06: Add kernel 2.6 support for GSPI8xxx/Bulverde
	
********************************************************/
#include	"if_gspi.h"
#include	"gspi_io.h"

#include	"helper.h"

#include	"gspi8686.h"

#define HIC_DEFAULT_VALUE 0
/********************************************************
		Local Variables
********************************************************/

/********************************************************
		Global Variables
********************************************************/

gspi_notifier_rec_t gspi_notifier;
extern int g_dummy_clk_reg;
extern int g_dummy_clk_ioport;

/********************************************************
		Local Functions
********************************************************/

static int gspi_read_reg32(wlan_private * priv, u16 offset, u32 * data);
static int gspi_read_host_int_status(wlan_private * priv, u8 * data);
static int gspi_read_event_scratch(wlan_private * priv);
static wlan_private *pwlanpriv;
static wlan_private *(*wlan_add_callback) (void *dev_id);
static int (*wlan_remove_callback) (void *dev_id);

/** 
 *  @brief clear the auto generate interrupt bit in Host
 *  Interrupt Control register
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   NA
 */
static void
gspi_init_HOST_INT_CTRL_REG(wlan_private * priv)
{
    io_card_rec_p cardp = priv->wlan_dev.card;

    gspi_write_reg(cardp, HOST_INT_CTRL_REG,
                   HIC_DEFAULT_VALUE & ~(HIC_TxDnldAuto
                                         | HIC_RxUpldAuto | HIC_CmdDnldAuto
                                         | HIC_CmdUpldAuto));
}

/**
 *  @brief This function re-enable the interrupt of the mask bit.
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @param mask    interrupt mask 	
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
gspi_write_host_int_status(wlan_private * priv, u16 mask)
{
    if (gspi_write_reg(priv->wlan_dev.card, HOST_INT_STATUS_REG, ~mask)) {
        PRINTM(ERROR, "gspi_write_reg failed\n");
        return WLAN_STATUS_FAILURE;
    }

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function used to poll CmdDnLdRdy bit of Host Interrupt Status Register
 * 
 *  @param cardp   A pointer to gspi_card_rec structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wait_for_hostintstatus(gspi_card_rec_p cardp)
{
#define MAX_WAIT_TRIES 100
    int i = 0;
    u16 stat;

    for (i = 0; i < MAX_WAIT_TRIES; ++i) {
        gspi_read_reg(cardp, HOST_INT_STATUS_REG, &stat);

        if (stat & GHIS_CmdDnLdRdy)
            return WLAN_STATUS_SUCCESS;

        udelay(100);
    }

    return WLAN_STATUS_FAILURE;
}

/** 
 *  @brief This function read a 32bit value from GSPI register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param reg          GSPI hardware register
 *  @param data		A pointer to return the register value    
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
gspi_read_reg32(wlan_private * priv, u16 reg, u32 * data)
{
    u16 readdt[3];
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    if (gspi_read_data_direct(cardp, (u8 *) readdt, reg, 4) < 0) {
        PRINTM(INFO, "Error on gspi_read_reg32(%02x)\n", reg);
        return WLAN_STATUS_FAILURE;
    }

    memcpy(data, readdt, 4);
#ifdef 	GSPI_TX_RX_DEBUG
    printk("read reg32(0x%x) = 0x%x\n", reg, *data);
#endif
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function read the host inerrrupt status register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param curHIS	A pointer to return the value of Host Interrupt Status register
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
gspi_read_host_int_status(wlan_private * priv, u8 * curHIS)
{
    int ret;
    u16 his;
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    if (!(ret = gspi_read_reg(cardp, HOST_INT_STATUS_REG, &his)))
        *curHIS = (u8) his;

    return ret;
}

/**
 *  @brief Read Event cause from the event scratch register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
gspi_read_event_scratch(wlan_private * priv)
{
    int ret;

    ENTER();

    ret = gspi_read_reg32(priv, SCRATCH_3_REG, &priv->adapter->EventCause);
    if (ret < 0) {
        PRINTM(ERROR, "ERROR: Event Scratch Pad Register Read!\n");
        return ret;
    }

    PRINTM(INFO, "The event is %x\n", priv->adapter->EventCause);

    priv->adapter->EventCause <<= 3;

    LEAVE();

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function enables the host interrupts mask
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param mask	   the interrupt mask
 *  @return 	   WLAN_STATUS_SUCCESS
 */
static int
enable_host_int_mask(wlan_private * priv, u8 mask)
{
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    /* Enabling TxDnldRdy, RxDnldRdy, CmdUpldRdy, CmdDnldRdy, CardEvent
     * interrupts */
    gspi_write_reg(priv->wlan_dev.card, HOST_INT_STATUS_MASK_REG,
                   HISM_TxDnLdRdy | HISM_RxUpLdRdy | HISM_CmdDnLdRdy
                   | HISM_CardEvent | HISM_CmdUpLdRdy);

    LEAVE();

    return ret;
}

/**  @brief This function disables the host interrupts mask.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param mask	   the interrupt mask
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
disable_host_int_mask(wlan_private * priv, u8 int_mask)
{
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    return gspi_write_reg(cardp, HOST_INT_STATUS_MASK_REG, 0x00);
}

/********************************************************
		Global Functions
********************************************************/
/** 
 *  @brief This is the interrupt handler for GSPI device
 *
 *  @param irq 	   The irq of GSPI device.
 *  @param dev_id  A pointer to net_device structure
 *  @param fp	   A pointer to pt_regs structure
 *  @return 	   n/a
 */
static IRQ_RET_TYPE
sbi_interrupt(int irq, void *dev_id, struct pt_regs *fp)
{
    struct net_device *dev = dev_id;

    disable_irq(dev->irq);
    wlan_interrupt(dev);
    IRQ_RET;
}

/** 
 *  @brief Call back function when New Hardware insert.
 *
 *  This function will notify wlan driver a new hardware insert.
 *
 *  @param card	   A pointer to struct net_device 
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_add_card(void *card)
{
    if (!wlan_add_callback)
        return WLAN_STATUS_FAILURE;

    pwlanpriv = wlan_add_callback(card);

    return (pwlanpriv != NULL) ? WLAN_STATUS_SUCCESS : WLAN_STATUS_FAILURE;
}

/** 
 *  @brief Call back function when Hardware been removed.
 *
 *  This function will notify wlan driver a hardware removed.
 *
 *  @param card	   A pointer to struct net_device 
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_remove_card(void *card)
{
    if (!wlan_remove_callback)
        return WLAN_STATUS_FAILURE;

    pwlanpriv = NULL;
    return wlan_remove_callback(card);
}

/** 
 *  @brief wlan driver call this function to register to bus driver
 *
 *  This function will be used to register wlan driver's add/remove callback function.
 *
 *  @param add	   wlan driver's call back funtion for add card.
 *  @param remove  wlan driver's call back funtion for remove card.
 *  @param arg     not been used
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int *
sbi_register(wlan_notifier_fn_add add, wlan_notifier_fn_remove remove,
             void *arg)
{
    int *gspi_ret;

    wlan_add_callback = add;
    wlan_remove_callback = remove;

    gspi_notifier.add = (gspi_notifier_fn_p) sbi_add_card;
    gspi_notifier.remove = (gspi_notifier_fn_p) sbi_remove_card;
    gspi_notifier.user_isr = sbi_interrupt;
    gspi_ret = (int *) register_user(&gspi_notifier);

    if (!gspi_ret)
        PRINTM(INFO, "register_user failed\n");

    return gspi_ret;
}

/**
 *  @brief wlan driver call this function to unregister to bus driver
 *
 *  This function will be used to unregister wlan driver.
 *
 *  @return 	   NA
 */
void
sbi_unregister(void)
{
    unregister_user(&gspi_notifier);
}

/** 
 *  @brief fake function for gspi interface hardware
 *
 *  @param priv    A pointer to wlan_private structure	
 *  @return 	   WLAN_STATUS_SUCCESS
 */
int
sbi_get_cis_info(wlan_private * priv)
{
    ENTER();

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief fake function for gspi interface hardware
 *
 *  @param card_p  not used
 *  @return 	   WLAN_STATUS_SUCCESS
 */
int
sbi_probe_card(void *card_p)
{
    return WLAN_STATUS_SUCCESS;
}

#define IPFIELD_ALIGN_OFFSET    2

/** 
 *  @brief This function read the current interrupt status register.
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @param ireg    A pointer to hold the return interrupt status value 	
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_get_int_status(wlan_private * priv, u8 * ireg)
{
    int ret = WLAN_STATUS_SUCCESS;
    u8 tmp;
    struct sk_buff *skb;
    u8 *cmdBuf;
    wlan_adapter *Adapter = priv->adapter;

    disable_host_int_mask(priv, HIM_DISABLE);
    ret = gspi_read_host_int_status(priv, &tmp);
    enable_irq(priv->wlan_dev.netdev->irq);

    /* re-map bit 0 and bit 1 for WLAN module since the definition is different */

    *ireg = tmp & (~(GHIS_TxDnLdRdy | GHIS_RxUpLdRdy));

    if (tmp & GHIS_TxDnLdRdy) {
        priv->wlan_dev.dnld_sent = DNLD_RES_RECEIVED;
        *ireg |= HIS_TxDnLdRdy;
    }

    if (tmp & GHIS_RxUpLdRdy) {
        *ireg |= HIS_RxUpLdRdy;
    }

    if (*ireg & HIS_RxUpLdRdy) {

        if (!(skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE))) {
            PRINTM(ERROR, "No free skb\n");
            priv->stats.rx_dropped++;
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

        skb_reserve(skb, IPFIELD_ALIGN_OFFSET); /*16 Byte Align the IP fields */

        /* skb->tail is passed as we are calling skb_put after we
         * are reading the data */
        if (sbi_card_to_host(priv, MVMS_DAT,
                             &priv->wlan_dev.upld_len,
                             skb->data,
                             MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) < 0) {
            PRINTM(ERROR, "ERROR: Data Transfer from device failed\n");
            if (skb)
                kfree_skb(skb);
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
        PRINTM(DATA, "Data <= FW\n");

        skb_put(skb, priv->wlan_dev.upld_len);

        list_add_tail((struct list_head *) skb,
                      (struct list_head *) &Adapter->RxSkbQ);
    }

    if (*ireg & HIS_CmdUpLdRdy) {

        if (!Adapter->CurCmd) {
            cmdBuf = priv->wlan_dev.upld_buf;
        } else {
            cmdBuf = Adapter->CurCmd->BufVirtualAddr;
        }

        if (sbi_card_to_host(priv, MVMS_CMD,
                             &priv->wlan_dev.upld_len,
                             cmdBuf, WLAN_UPLD_SIZE) < 0) {
            PRINTM(ERROR, "ERROR: Data Transfer from device failed\n");
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
    }
  done:
    enable_host_int_mask(priv, HIM_ENABLE);
    PRINTM(INFO, "GSPI int status = %02x:%02x\n", *ireg, Adapter->HisRegCpy);

    return ret;
}

/** 
 *  @brief initial the gspi hardware
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_card_init(wlan_private * priv)
{
    io_card_rec_p cardp = priv->wlan_dev.card;
    u16 host_int_mask;

    gspi_write_reg(cardp, SPU_BUS_MODE_REG, BUS_MODE_16_NO_DELAY);
    gspi_read_reg(cardp, CHIPREV_REG, &cardp->chiprev);
    PRINTM(INFO, "Chiprev is %x\n", cardp->chiprev);
    priv->adapter->chip_rev = cardp->chiprev;

    /* Read the HOST_INT_STATUS_REG for ACK the first interrrupt got
     * from the bootloader. If we don't do this we get a interrupt
     * as soon as we register the irq. */
    gspi_read_reg(cardp, HOST_INT_STATUS_REG, &host_int_mask);

    cardp->user_arg = (void *) priv->wlan_dev.netdev;
    if (gspi_register_irq(cardp->ctrlr) != GSPI_OK) {
        PRINTM(INFO, "gspi_register_irq failed\n");
        return WLAN_STATUS_FAILURE;
    }
    enable_host_int_mask(priv, HIM_ENABLE);
    gspi_init_HOST_INT_CTRL_REG(priv);
    priv->wlan_dev.netdev->irq = cardp->ctrlr->irq;

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function check the firmware download status
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_verify_fw_download(wlan_private * priv)
{
    int i;
    u32 scr4;

    for (i = 0; i < MAX_FIRMWARE_POLL_TRIES; ++i) {

        if (gspi_read_reg32(priv, SCRATCH_4_REG, &scr4) < 0) {
            PRINTM(INFO, "Read from Scratch 4 failed !!!\n");
            return WLAN_STATUS_FAILURE;
        }

        if (scr4 == FIRMWARE_DNLD_OK) {
            PRINTM(INFO, "FW download successful !!!\n");
            return WLAN_STATUS_SUCCESS;
        }

        mdelay(100);
    }

    return WLAN_STATUS_FAILURE;
}

/** 
 *  @brief This function download the firmware to the hardware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param firmware     A pointer to firmware 
 *  @param firmwarelen  the len of firmware
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_download_wlan_fw_image(wlan_private * priv, const u8 * firmware,
                           int firmwarelen)
{
    int ret;
    u16 dlimage[1024];
    u16 len;
    u32 cnt = 0;
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    ENTER();

    PRINTM(INFO, "Downloading FW of size %d bytes\n", firmwarelen);

    /* Wait initially for the first non-zero value */

    do {
        udelay(100);
        gspi_read_reg(cardp, SCRATCH_1_REG, &len);
    } while (!len);

    for (;;) {
        if (wait_for_hostintstatus(cardp)) {
            PRINTM(ERROR, "FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        gspi_read_reg(cardp, SCRATCH_1_REG, &len);

        if (!len) {
            break;
        }

        if (len & 1) {
            PRINTM(INFO, "CRC Error\n");
            len &= ~1;
        } else {
            PRINTM(INFO, ".");
        }

        memcpy(dlimage, firmware + cnt, len);
        gspi_write_data_direct(cardp, (u8 *) dlimage, CMD_RDWRPORT_REG,
                               (len / 2) + 1);
        gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
        cnt += len;
    }

    PRINTM(INFO, "\nFW Image of Size %d bytes downloaded, cnt %d\n",
           firmwarelen, cnt);

    ret = WLAN_STATUS_SUCCESS;

    LEAVE();
    return ret;
}

/** 
 *  @brief This function will call sbi_download_wlan_fw_image to download the firmware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware_w_helper(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->fmimage != NULL) {
        return sbi_download_wlan_fw_image(priv,
                                          Adapter->fmimage,
                                          Adapter->fmimage_len);
    } else {
        PRINTM(MSG, "No external FW image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/**
 *  @brief This function is used to download firmware to hardware
 * 
 *  @param priv         	A pointer to wlan_private structure
 *  @param firmware 		A pointer to fimware
 *  @param firmwarelen		firmware length
 *  @return 	        	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware_image(wlan_private * priv, const u8 * firmware,
                        int firmwarelen)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 dlimage[FIRMWARE_DNLD_PCKCNT];
    int fwblknow;
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    for (fwblknow = 0; fwblknow < firmwarelen;
         fwblknow += FIRMWARE_DNLD_PCKCNT) {
        gspi_write_reg(cardp, SCRATCH_1_REG, FIRMWARE_DNLD_PCKCNT);

        if (wait_for_hostintstatus(cardp)) {
            PRINTM(ERROR, "FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        memcpy(dlimage, firmware + fwblknow, FIRMWARE_DNLD_PCKCNT);
        gspi_write_data_direct(cardp, (u8 *) dlimage, CMD_RDWRPORT_REG,
                               (FIRMWARE_DNLD_PCKCNT / 2) + 1);
        gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);

        PRINTM(INFO, ".");
    }

    PRINTM(INFO, "\nDownload %d bytes of FW\n", firmwarelen);

    /* Writing 0 to Scr1 is to indicate the end of Firmware dwld */
    gspi_write_reg(cardp, SCRATCH_1_REG, FIRMWARE_DNLD_END);
    gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
    gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);

    ret = WLAN_STATUS_SUCCESS;

    LEAVE();
    return ret;
}

/** 
 *  @brief This function will call sbi_prog_firmware_image to
 *  download the firmware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->fmimage != NULL) {
        return sbi_prog_firmware_image(priv,
                                       Adapter->fmimage,
                                       Adapter->fmimage_len);
    } else {
        PRINTM(MSG, "No external FW image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/** 
 *  @brief This function will call sbi_prog_firmware_image to
 *  download the helperimage
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_helper(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->helper != NULL) {
        return sbi_prog_firmware_image(priv,
                                       Adapter->helper, Adapter->helper_len);
    } else {
        PRINTM(MSG, "No external helper image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/** 
 *  @brief wlan driver call this function to register the device 
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_register_dev(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    /* Initialize the private structure */
    strncpy(priv->wlan_dev.name, "gspi0", sizeof(priv->wlan_dev.name));
    priv->wlan_dev.ioport = 0;
    priv->wlan_dev.upld_rcv = 0;
    priv->wlan_dev.upld_typ = 0;
    priv->wlan_dev.upld_len = 0;

    sbi_card_init(priv);

    LEAVE();

    return ret;
}

/** 
 *  @brief wlan driver call this function to unregister the device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_unregister_dev(wlan_private * priv)
{
    io_card_rec_p cardp = priv->wlan_dev.card;

    ENTER();

    /* Disable interrupts on the card */
    disable_host_int_mask(priv, 0xff);
    gspi_unregister_irq(cardp->ctrlr);
    PRINTM(INFO, "Sending reset ...\n");
    gspi_reset();

    LEAVE();

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief enable the host interrupt on the GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_enable_host_int(wlan_private * priv)
{
    enable_irq(priv->wlan_dev.netdev->irq);
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Disable the Host interrupt on the GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_disable_host_int(wlan_private * priv)
{
    disable_irq(priv->wlan_dev.netdev->irq);
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function is used to send the data/cmd to hardware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param type 	1--Cmd, 0--Data
 *  @param payload	A point to the data or cmd buffer
 *  @param nb           len of data/cmd buffer 
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_host_to_card(wlan_private * priv, u8 type, u8 * payload, u16 nb)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 writeReg;
    u8 intType;
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    ENTER();

    intType = type ? CIC_CmdDnLdOvr : CIC_TxDnLdOvr;
    writeReg = (type) ? CMD_RDWRPORT_REG : DATA_RDWRPORT_REG;
    priv->wlan_dev.dnld_sent = (type) ? DNLD_CMD_SENT : DNLD_DATA_SENT;

    if (nb & 0x0001)
        nb += 1;

    /* 
     * If the bytes written is not a multiple of four then make it 
     * a multiple of four as the RWPORT is 4 byte aligned from
     * the host
     */

    if (!(nb % 4))
        ret = gspi_write_data_direct(cardp, payload, writeReg, (nb / 2) + 1);
    else
        ret = gspi_write_data_direct(cardp, payload, writeReg, (nb / 2) + 2);

    gspi_write_reg(cardp, CARD_INT_CAUSE_REG, intType);
#ifdef GSPI_TX_RX_DEBUG
    printk("Transmit packet of len %d\n", nb);
    if (type == MVMS_CMD)
        gspi_hexdump8("Write", payload, nb);
    printk("+");
#endif

    LEAVE();

    return ret;
}

/**
 *  @brief This function is used to read data/cmd from the card.
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param type 	1--Cmd, 0--Data
 *  @param nb    	A point to return how many bytes has been read back from hardware
 *  @param payload      A point to data buffer for receive data/cmd
 *  @param npayload     the size of payload buffer
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_card_to_host(wlan_private * priv, u32 type,
                 u32 * nb, u8 * payload, u16 npayload)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 len;
    u16 intType = 0, readReg;
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    ENTER();

    intType = type ? CIC_CmdUpLdOvr : CIC_RxUpLdOvr;
    readReg = type ? CMD_RDWRPORT_REG : DATA_RDWRPORT_REG;

    gspi_read_reg(cardp, (type) ? SCRATCH_2_REG : SCRATCH_1_REG, &len);

    if (!len || len > npayload) {
        PRINTM(INFO, "Error packet of len %d\n", len);
        len = MRVDRV_ETH_RX_PACKET_BUFFER_SIZE;
    }

    if (len & 0x0001)
        len += 1;

    if (!(len % 4))
        ret = gspi_read_data_direct(cardp, payload, readReg, (len / 2) + 1);
    else
        ret = gspi_read_data_direct(cardp, payload, readReg, (len / 2) + 2);

    gspi_write_reg(cardp, CARD_INT_CAUSE_REG, intType);

    *nb = len;
#ifdef GSPI_TX_RX_DEBUG
    printk("Receiving packet of len %d\n", len);
    if (type == MVMS_CMD)
        gspi_hexdump8("Read", payload, len);
    printk("-");
#endif

    LEAVE();

    return ret;
}

/** 
 *  @brief This function is used to read the event cause from card
 *  and re-enable event interrupt.
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_read_event_cause(wlan_private * priv)
{
    gspi_card_rec_p cardp = priv->wlan_dev.card;

    gspi_read_event_scratch(priv);

    /* re-enable the interrupt */
    gspi_write_host_int_status(priv, GHIS_CardEvent);

    /* generate interrupt to firmware */
    gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_HostEvent);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief configure hardware to quit deep sleep state
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
inline int
sbi_exit_deep_sleep(wlan_private * priv)
{
    io_card_rec_p card = priv->wlan_dev.card;

    /* set Wakeup bit */
    return gspi_write_reg(card, HOST_INT_CTRL_REG,
                          HIC_DEFAULT_VALUE | HIC_WakeUp);
}

/** 
 *  @brief clear the Wake up bit in Host Interrupt Control Register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_reset_deepsleep_wakeup(wlan_private * priv)
{
    io_card_rec_p card = priv->wlan_dev.card;

    /* clear wakeup bit */
    return gspi_write_reg(card, HOST_INT_CTRL_REG,
                          HIC_DEFAULT_VALUE & ~HIC_WakeUp);
}

#ifdef ENABLE_PM
/** 
 *  @brief fake function for GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_suspend(wlan_private * priv)
{
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief fake function for GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_resume(wlan_private * priv)
{
    return WLAN_STATUS_SUCCESS;
}
#endif
