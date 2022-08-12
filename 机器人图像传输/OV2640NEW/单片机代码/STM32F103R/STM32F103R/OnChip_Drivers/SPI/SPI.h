
#ifndef SPI_H_H_
#define SPI_H_H_
#include "stm32f10x.h"

//////////////////////SPI1/////////////////
#define USE_SPI1					   0
#define SPI1_CLK                       RCC_APB2Periph_SPI1
//SCK
#define SPI1_SCK_PIN                   GPIO_Pin_5         		/* PA.05 */
#define SPI1_SCK_GPIO_PORT             GPIOA                    /* GPIOA */
#define SPI1_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA
//MISO
#define SPI1_MISO_PIN                  GPIO_Pin_6               /* PA.06 */
#define SPI1_MISO_GPIO_PORT            GPIOA                    /* GPIOA */
#define SPI1_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA
//MOSI
#define SPI1_MOSI_PIN                  GPIO_Pin_7           	/* PA.07 */
#define SPI1_MOSI_GPIO_PORT            GPIOA                 	/* GPIOA */
#define SPI1_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA
//CS
#define SPI1_CS_PIN                    GPIO_Pin_4           	/* PA.4 */
#define SPI1_CS_GPIO_PORT              GPIOA                	/* GPIOA */
#define SPI1_CS_GPIO_CLK               RCC_APB2Periph_GPIOA

//////////////////////SPI2/////////////////
#define USE_SPI2					   1
#define SPI2_CLK                       RCC_APB1Periph_SPI2
//SCK
#define SPI2_SCK_PIN                   GPIO_Pin_13       		/* PA.13 */
#define SPI2_SCK_GPIO_PORT             GPIOB            		/* GPIOB */
#define SPI2_SCK_GPIO_CLK              RCC_APB2Periph_GPIOB
//MISO
#define SPI2_MISO_PIN                  GPIO_Pin_14          	/* PB.14 */
#define SPI2_MISO_GPIO_PORT            GPIOB              		/* GPIOB */
#define SPI2_MISO_GPIO_CLK             RCC_APB2Periph_GPIOB
//MOSI
#define SPI2_MOSI_PIN                  GPIO_Pin_15        		/* PB.15 */
#define SPI2_MOSI_GPIO_PORT            GPIOB             		/* GPIOB */
#define SPI2_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOB
//CS
#define SPI2_CS_PIN                    GPIO_Pin_12     			/* PB.12 */
#define SPI2_CS_GPIO_PORT              GPIOB           			/* GPIOB */
#define SPI2_CS_GPIO_CLK               RCC_APB2Periph_GPIOB

void SPI_Test(u8 SPIx);

void SPI_GpioInit(u8 SPIx);
void SPI_SetSpiSoftCS(u8 SPIx);
void SPI_SetCS(u8 SPIx);
void SPI_ClrCS(u8 SPIx);
void SPI_MsterConfig(u8 SPIx, u8 spi_mode, u8 data_len);
u16 SPI_WriteByte(u8 SPIx, u16 tx_data);
u16 SPI_ReadByte(u8 SPIx, u16 dummy_data);
void SPI_SetSpeed(u8 SPIx, u8 baud_rate_prescaler);

#endif
