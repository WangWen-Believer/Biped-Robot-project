#include "Wifi_Spi.h"
#include "MyBspInc.h"
////////////////////暂时移除固件数组//////////
//#include	"helper.h"						//
//#include	"gspi8686.h"					//
const unsigned char helperimage[] = 
{
	0,
};
const unsigned char fmimage[] = 
{
	0,
};
//////////////////////////////////////////////
#include <stdio.h>
#include <string.h>


///////////////////////////////////////////
#define ENTER()		do{;}while(0)
#define LEAVE()		do{;}while(0)

#define udelay		Delay_nUS
#define PRINTM		printf

#define WLAN_STATUS_SUCCESS			(0)
#define WLAN_STATUS_FAILURE			(-1)
#define WLAN_STATUS_NOT_ACCEPTED    (-2)

#define	HIM_DISABLE			0xff
#define HIM_ENABLE			0x03

#define HIC_DEFAULT_VALUE 0

typedef u8			gspi_card_rec_p;
typedef u8			io_card_rec_p;
typedef u8			wlan_private;

int
gspi_write_reg(gspi_card_rec_p cardp, u16 reg, u16 val)
{
    WiFi_SpiWriteReg(reg, val);

    return 0;
}

int gspi_read_reg(gspi_card_rec_p cardp, u16 reg, u16 * val)
{
    u32 reg_val = 0;
	Wifi_SpiReadReg(reg, &reg_val);
	*val = (u16)reg_val;
    return 0;
}
/*
int gspi_read_data_direct(gspi_card_rec_p cardp, u8 * data, u16 reg, u16 n)
{
	SPI_ClrCS(WIFI_SPI);
	SPI_WriteByte(WIFI_SPI, reg);
	
	SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);		//提供16个时钟延时
	for(i  = 0; i < n; i ++)
	{						
		temp = SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);	//读高位
		temp <<= 16;
		temp |= SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);//读低位
	}
	
	SPI_SetCS(WIFI_SPI);
}*/
gspi_write_data_direct(gspi_card_rec_p cardp, u8 * data, u16 reg, u16 n)
{
	u16 i;
	u16* temp = (u16*)data;
	n = (n * 2);
	reg |= 0x8000;
	
	SPI_ClrCS(WIFI_SPI);
	SPI_WriteByte(WIFI_SPI, reg);
	for(i = 0; i < (n / 2); i ++)
	{
		SPI_WriteByte(WIFI_SPI, *temp);
		temp ++;
	}
	if ((n % 4) != 0) 
	{
		SPI_WriteByte(WIFI_SPI, 0);
	}
	SPI_SetCS(WIFI_SPI);
}
///////////////////////////////////////////
////////////////////////
void test_dwn(void);
int sbi_register_dev(wlan_private * priv);
////////////////////////

void Wifi_SpiInit(void)
{
	SPI_GpioInit(WIFI_SPI);				//SPI使用端口初始化
	SPI_SetSpiSoftCS(WIFI_SPI);			//使用NSS为普通GPIO
	SPI_MsterConfig(WIFI_SPI, 0, 16);	//配置为主机,16位数据,MSB,模式0
	SPI_SetSpeed(WIFI_SPI, 1);			//设置分频,4分频
}

void WiFi_SpiWriteReg(u16 reg, u16 val)
{
	reg |= 0x8000;
	SPI_ClrCS(WIFI_SPI);
	SPI_WriteByte(WIFI_SPI, reg);
	SPI_WriteByte(WIFI_SPI, val);
	SPI_SetCS(WIFI_SPI);
}

void Wifi_SpiReadReg(u16 reg, u32* pval)
{
	u16 temp_l = 0;
	u32 temp_h = 0; 
	SPI_ClrCS(WIFI_SPI);
	SPI_WriteByte(WIFI_SPI, reg); 
	
	//SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);		//提供16个时钟延时
	Delay_nUS(1);	
	temp_l = SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);	//读低位
	temp_h = SPI_ReadByte(WIFI_SPI, WIFI_DUMMY_DATA);	//读高位
	temp_h <<= 16;
	temp_h |= temp_l;
	SPI_SetCS(WIFI_SPI);
	
	*pval = temp_h;
}

void Wifi_SpiTest(void)
{
	u8 temp = 0;
	u32 reg_val = 0;
	Wifi_SpiInit();
	//WiFi_SpiWriteReg(0x70, 0x02);
	sbi_register_dev(&temp);
	while(1)
	{
		//Wifi_SpiReadReg(0x6C, &reg_val);
		test_dwn();
		Delay_nMS(100);
	}
}

////////////////////////////////////////////
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
    io_card_rec_p cardp = 0;//priv->wlan_dev.card;

    gspi_write_reg(cardp, HOST_INT_CTRL_REG,
                   HIC_DEFAULT_VALUE & ~(HIC_TxDnldAuto
                                         | HIC_RxUpldAuto | HIC_CmdDnldAuto
                                         | HIC_CmdUpldAuto));
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
    gspi_write_reg(0, HOST_INT_STATUS_MASK_REG,
                   HISM_TxDnLdRdy | HISM_RxUpLdRdy | HISM_CmdDnLdRdy
                   | HISM_CardEvent | HISM_CmdUpLdRdy);

    LEAVE();

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
    io_card_rec_p cardp = 0;//priv->wlan_dev.card;
    u16 host_int_mask;
	u16 chiprev;
    gspi_write_reg(cardp, SPU_BUS_MODE_REG, BUS_MODE_16_NO_DELAY);
    gspi_read_reg(cardp, CHIPREV_REG, &chiprev);
    PRINTM("Chiprev is %x\n", chiprev);
    //priv->adapter->chip_rev = cardp->chiprev;

    /* Read the HOST_INT_STATUS_REG for ACK the first interrrupt got
     * from the bootloader. If we don't do this we get a interrupt
     * as soon as we register the irq. */
    gspi_read_reg(cardp, HOST_INT_STATUS_REG, &host_int_mask);

    //cardp->user_arg = (void *) priv->wlan_dev.netdev;
    /*if (gspi_register_irq(cardp->ctrlr) != GSPI_OK) {
        PRINTM(INFO, "gspi_register_irq failed\n");
        return WLAN_STATUS_FAILURE;
    }
	*/
    enable_host_int_mask(priv, HIM_ENABLE);
	
    gspi_init_HOST_INT_CTRL_REG(priv);
    //priv->wlan_dev.netdev->irq = cardp->ctrlr->irq;

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
////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** 
 *  @brief wlan driver call this function to register the device 
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int sbi_register_dev(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    /* Initialize the private structure */
    /*strncpy(priv->wlan_dev.name, "gspi0", sizeof(priv->wlan_dev.name));
    priv->wlan_dev.ioport = 0;
    priv->wlan_dev.upld_rcv = 0;
    priv->wlan_dev.upld_typ = 0;
    priv->wlan_dev.upld_len = 0;
	*/
    sbi_card_init(priv);

    LEAVE();

    return ret;
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
    gspi_card_rec_p cardp = 0;//priv->wlan_dev.card;

    for (fwblknow = 0; fwblknow < firmwarelen;
         fwblknow += FIRMWARE_DNLD_PCKCNT) {
        gspi_write_reg(cardp, SCRATCH_1_REG, FIRMWARE_DNLD_PCKCNT);

        if (wait_for_hostintstatus(cardp)) {
            PRINTM(  "FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        memcpy(dlimage, firmware + fwblknow, FIRMWARE_DNLD_PCKCNT);
        gspi_write_data_direct(cardp, (u8 *) dlimage, CMD_RDWRPORT_REG,
                               (FIRMWARE_DNLD_PCKCNT / 2) + 1);
        gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);

        PRINTM(  ".");
    }

    PRINTM(  "\nDownload %d bytes of FW\n", firmwarelen);

    /* Writing 0 to Scr1 is to indicate the end of Firmware dwld */
    gspi_write_reg(cardp, SCRATCH_1_REG, FIRMWARE_DNLD_END);
    gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
    gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);

    ret = WLAN_STATUS_SUCCESS;

    LEAVE();
    return ret;
}
///////////////////////////////////////////////
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
    gspi_card_rec_p cardp = 0;//priv->wlan_dev.card;

    ENTER();

    PRINTM(  "Downloading FW of size %d bytes\n", firmwarelen);

    /* Wait initially for the first non-zero value */

    do {
        udelay(100);
        gspi_read_reg(cardp, SCRATCH_1_REG, &len);
    } while (!len);

    for (;;) {
        if (wait_for_hostintstatus(cardp)) {
            PRINTM(  "FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        gspi_read_reg(cardp, SCRATCH_1_REG, &len);

        if (!len) {
            break;
        }

        if (len & 1) {
            PRINTM(  "CRC Error\n");
            len &= ~1;
        } else {
            PRINTM(  ".");
        }

        memcpy(dlimage, firmware + cnt, len);
        gspi_write_data_direct(cardp, (u8 *) dlimage, CMD_RDWRPORT_REG,
                               (len / 2) + 1);
        gspi_write_reg(cardp, HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(cardp, CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
        cnt += len;
    }

    PRINTM(  "\nFW Image of Size %d bytes downloaded, cnt %d\n",
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
    //wlan_adapter *Adapter = priv->adapter;
    
	if (1) {
        return sbi_download_wlan_fw_image(priv,
                                          fmimage,
                                          sizeof(fmimage));
    } else {
        PRINTM(  "No external FW image\n");
        return WLAN_STATUS_FAILURE;
    }
}
////////////////////////////////////////////////////////

////////////////////////helper//////////////////////////



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
    //wlan_adapter *Adapter = priv->adapter;
    if (1) {
        return sbi_prog_firmware_image(priv,
                                       helperimage, sizeof(helperimage));
    } else {
        PRINTM(  "No external helper image\n");
        return WLAN_STATUS_FAILURE;
    }
}
////////////////////////helper//////////////////////////

////////////////////////verify///////////////////////////
#define MAX_FIRMWARE_POLL_TRIES		100

static int gspi_read_reg32(wlan_private * priv, u16 reg, u32 * data)
{
	Wifi_SpiReadReg(reg, data);
	return 0;
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
            PRINTM("Read from Scratch 4 failed !!!\n");
            return WLAN_STATUS_FAILURE;
        }

        if (scr4 == FIRMWARE_DNLD_OK) {
            PRINTM("FW download successful !!!\n");
            return WLAN_STATUS_SUCCESS;
        }

        Delay_nMS(100);
    }

    return WLAN_STATUS_FAILURE;
}
////////////////////////verify///////////////////////////
void test_dwn(void)
{
   /* Download the helper */
    wlan_private * priv;
    int ret;
    ret = sbi_prog_helper(priv);

    if (ret) {
        PRINTM(  "Bootloader in invalid state!\n");
        ret = WLAN_STATUS_FAILURE;
       
    }
    /* Download the main firmware via the helper firmware */
    if (sbi_prog_firmware_w_helper(priv)) {
        PRINTM(  "Wlan FW download failed!\n");
        ret = WLAN_STATUS_FAILURE;
        
    }

    /* check if the fimware is downloaded successfully or not */
    if (sbi_verify_fw_download(priv)) {
        PRINTM(  "FW failed to be active in time!\n");
        ret = WLAN_STATUS_FAILURE;
        
    }
}
