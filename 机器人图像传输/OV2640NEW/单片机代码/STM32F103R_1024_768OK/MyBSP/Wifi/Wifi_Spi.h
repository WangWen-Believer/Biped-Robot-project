#ifndef WIFI_SPI_H_H_
#define WIFI_SPI_H_H_
#include "stm32f10x.h"

#include "OnChip_Driver_Inc.h"
/* GSPI Registers Offset. All the resgisters are at DWORD boundary */
#define DEVICEID_CTRL_REG		0x00
#define CHIPREV_REG			0x02

#define IO_READBASE_REG			0x04
#define IO_WRITEBASE_REG		0x08
#define IO_RDWRPORT_REG			0x0C

#define CMD_READBASE_REG		0x10
#define CMD_WRITEBASE_REG		0x14
#define CMD_RDWRPORT_REG		0x18

#define DATA_READBASE_REG		0x1C
#define DATA_WRITEBASE_REG		0x20
#define DATA_RDWRPORT_REG		0x24

#define SCRATCH_1_REG			0x28
#define SCRATCH_2_REG			0x2C
#define SCRATCH_3_REG			0x30
#define SCRATCH_4_REG			0x34

#define TX_FRAME_SEQ_NUM_REG		0x38
#define TX_FRAME_STATUS_REG		0x3C

#define HOST_INT_CTRL_REG		0x40

#define CARD_INT_CAUSE_REG		0x44
#define CARD_INT_STATUS_REG		0x48
#define CARD_INT_EVENT_MASK_REG		0x4C
#define CARD_INT_STATUS_MASK_REG	0x50
#define CARD_INT_RESET_SELECT_REG	0x54

#define HOST_INT_CAUSE_REG		0x58
#define HOST_INT_STATUS_REG		0x5C
#define HOST_INT_EVENT_MASK_REG		0x60
#define HOST_INT_STATUS_MASK_REG	0x64
#define HOST_INT_RESET_SELECT_REG	0x68

#define DELAY_READ_REG			0x6C
#define SPU_BUS_MODE_REG		0x70
#define BUS_MODE_16_NO_DELAY		0x02

#define BIT(n)		(1 << (n))

/* Bit definition for CARD_INT_CAUSE (Card Interrupt Cause) */
#define CIC_TxDnLdOvr			BIT(0)
#define CIC_RxUpLdOvr			BIT(1)
#define CIC_CmdDnLdOvr			BIT(2)
#define CIC_HostEvent			BIT(3)
#define CIC_CmdUpLdOvr			BIT(4)
#define CIC_PwrDown				BIT(5)

/* Bit definition for HOST_INT_STATUS (Host Interrupt Status) */
#define GHIS_TxDnLdRdy			BIT(0)
#define GHIS_RxUpLdRdy			BIT(1)
#define GHIS_CmdDnLdRdy			BIT(2)
#define GHIS_CardEvent			BIT(3)
#define GHIS_CmdUpLdRdy			BIT(4)
#define GHIS_IOWrFifoOvrflow		BIT(5)
#define GHIS_IORdFifoUndrflow		BIT(6)
#define GHIS_DATAWrFifoOvrflow		BIT(7)
#define GHIS_DATARdFifoUndrflow		BIT(8)
#define GHIS_CMDWrFifoOvrflow		BIT(9)
#define GHIS_CMDRdFifoUndrflow		BIT(10)
/* Bit definition for HOST_INT_STATUS_MASK_REG (Host Interrupt Status Mask) */
#define HISM_TxDnLdRdy			BIT(0)
#define HISM_RxUpLdRdy			BIT(1)
#define HISM_CmdDnLdRdy			BIT(2)
#define HISM_CardEvent			BIT(3)
#define HISM_CmdUpLdRdy			BIT(4)
#define HISM_IOWrFifoOvrflow		BIT(5)
#define HISM_IORdFifoUndrflow		BIT(6)
#define HISM_DATAWrFifoOvrflow		BIT(7)
#define HISM_DATARdFifoUndrflow		BIT(8)
#define HISM_CMDWrFifoOvrflow		BIT(9)
#define HISM_CMDRdFifoUndrflow		BIT(10)

/* Bit definition for HOST_INT_CTRL_REG (Host Interrupt Control) */
#define HIC_WakeUp			BIT(0)
#define HIC_WlanRdy			BIT(1)
#define HIC_TxDnldAuto			BIT(5)
#define HIC_RxUpldAuto			BIT(6)
#define HIC_CmdDnldAuto			BIT(7)
#define HIC_CmdUpldAuto			BIT(8)

/* Bit definition for SPU_BUS_MODE_REG (SPU Bus mode register)*/
#define SBM_DataFormat_2		BIT(2)

/* Value to check once the firmware is downloaded */
#define FIRMWARE_DNLD_OK 		0x88888888

/* Value to write to indicate end of firmware dnld */
#define FIRMWARE_DNLD_END 		0x0000
#define FIRMWARE_DNLD_PCKCNT		64
/////////////////////////////////////////////////////////////////
#define WIFI_DUMMY_DATA		0x0000
#define WIFI_SPI			USE_SPI2

void Wifi_SpiInit(void);
void WiFi_SpiWriteReg(u16 reg, u16 val);
void Wifi_SpiReadReg(u16 reg, u32* pval);
void Wifi_SpiTest(void);

/////////////////////////////////////////////////////////////////
#endif

