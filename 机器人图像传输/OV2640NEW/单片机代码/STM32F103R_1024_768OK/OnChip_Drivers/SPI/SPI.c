#include "SPI.h"
#include "MyBspInc.h"
static SPI_TypeDef* SPI_TypeBuffer[2] = {SPI1, SPI2};
static GPIO_TypeDef* SPI_CS_PORT[2] = {SPI1_CS_GPIO_PORT, SPI2_CS_GPIO_PORT};
const u16 SPI_CS_PIN[2] = {SPI1_CS_PIN, SPI2_CS_PIN};
/*******************************************************************************
* Function Name	: SPI_GpioInit											
* Description   : 初始化SPI使用的MISO,MOSI,SCK复用引脚	
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : None													
* Return        : None
*				：NOne											
*******************************************************************************/
void SPI_GpioInit(u8 SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	if(SPIx == USE_SPI1)
	{
		// SPIx_CS_GPIO, SPIx_MOSI_GPIO, SPIx_MISO_GPIO and SPIx_SCK_GPIO Periph clock enable 
		RCC_APB2PeriphClockCmd(SPI1_CS_GPIO_CLK | SPI1_MOSI_GPIO_CLK | SPI1_MISO_GPIO_CLK |
		             			SPI1_SCK_GPIO_CLK, ENABLE);
		
		// SPI1 Periph clock enable 
		RCC_APB2PeriphClockCmd(SPI1_CLK, ENABLE); 
		
		
		// Configure SPI1 pins: SCK 
		GPIO_InitStructure.GPIO_Pin = SPI1_SCK_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);
		
		//Configure SPI1 pins: MISO
		GPIO_InitStructure.GPIO_Pin = SPI1_MISO_PIN;
		GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);
		
		// Configure SPI1 pins: MOSI
		GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_PIN;
		GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);
	}
	else if(SPIx == USE_SPI2)
	{
		// SPIx_CS_GPIO, SPIx_MOSI_GPIO, SPIx_MISO_GPIO and SPIx_SCK_GPIO Periph clock enable 
		RCC_APB2PeriphClockCmd(SPI2_CS_GPIO_CLK | SPI2_MOSI_GPIO_CLK | SPI2_MISO_GPIO_CLK |
		             			SPI2_SCK_GPIO_CLK, ENABLE);
		
		//SPI2 Periph clock enable 
		RCC_APB1PeriphClockCmd(SPI2_CLK, ENABLE); 
		
		
		//Configure SPI2 pins: SCK 
		GPIO_InitStructure.GPIO_Pin = SPI2_SCK_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStructure);
		
		// Configure SPI2 pins: MISO 
		GPIO_InitStructure.GPIO_Pin = SPI2_MISO_PIN;
		GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStructure);
		
		// Configure SPI2 pins: MOSI 
		GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN;
		GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStructure);
	}
}


/*******************************************************************************
* Function Name	: SPI_SetSpiSoftCS											
* Description   : SPI NSS做普通GPIO使用		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : None													
* Return        : None
*				：NOne											
*******************************************************************************/
void SPI_SetSpiSoftCS(u8 SPIx)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN[SPIx];
	GPIO_Init(SPI_CS_PORT[SPIx], &GPIO_InitStructure);
	
	SPI_SSOutputCmd(SPI_TypeBuffer[SPIx], ENABLE);	//使能软件管理NSS,这样NSS被当做普通GPIO使用
}

/*******************************************************************************
* Function Name	: SPI_WriteByte											
* Description   : 写一个字节  		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : u8 spi_mode		->	配置SPI的模式(时钟和采样)
					0					->	上升沿采集发送数据(时钟空闲为低)	
				 	1					->	下降沿采集数据(时钟空闲为低)
				 	2					->	下降沿采集数据(时钟空闲为高)
				 	3					->	上升沿采集发送数据(时钟空闲为高)				
* Return        : None
*				：NOne											
*******************************************************************************/
void SPI_MsterConfig(u8 SPIx, u8 spi_mode, u8 data_len)
{
	//主机模式,双线全双工,数据位可选(8/16bit),MSB
	//CPOL和CPHA由参数spi_mode决定
	SPI_InitTypeDef   SPI_InitStructure;
	switch(spi_mode)
	{
		case 0:		//上升沿采集发送数据(时钟空闲为低)
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 1:		//下降沿采集数据(时钟空闲为低)
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case 2:		//下降沿采集数据(时钟空闲为高)
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case 3:		//上升沿采集发送数据(时钟空闲为高)
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
		default:
			break;
	}
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//双线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//主机模式
	if(data_len == 8)
	{
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//8位数据
	}
	else if(data_len == 16)
	{
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;	//16位数据
	}
	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	//预分频
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//MSB
	SPI_InitStructure.SPI_CRCPolynomial = 7;			//CRC多项式,CRC默认为关闭
	
	SPI_Init(SPI_TypeBuffer[SPIx], &SPI_InitStructure);	//初始化相应的SPI模块
	SPI_Cmd(SPI_TypeBuffer[SPIx], ENABLE);				//使能SPI
}
/*******************************************************************************
* Function Name	: SPI_WriteByte											
* Description   : 写一个字节  		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : u8 tx_data		->	待发送的数据													
* Return        : u8 data			->	从MISO读取的数据
*				：NOne											
*******************************************************************************/
u16 SPI_WriteByte(u8 SPIx, u16 tx_data)
{
  	u16 data = 0;
	if(SPIx == USE_SPI1)
  	{
  	 	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  		{
  			;
		}
		/*!< Send the byte */
		SPI_I2S_SendData(SPI1, tx_data);
		
		/*!< Wait to receive a byte*/
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		{
		}
		/*!< Return the byte read from the SPI bus */ 
		data = SPI_I2S_ReceiveData(SPI1);
		return data;
  	}
	else if(SPIx == USE_SPI2)
	{
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
  		{
  			;
		}
  
		/*!< Send the byte */
		SPI_I2S_SendData(SPI2, tx_data);
		
		/*!< Wait to receive a byte*/
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
		{
		}
		/*!< Return the byte read from the SPI bus */ 
		data = SPI_I2S_ReceiveData(SPI2);
		return data;
	}
	return 0;
}
/*******************************************************************************
* Function Name	: SPI_ReadByte											
* Description   : 读一个字节		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : u8 dummy_data		->	dummy data(通常为0xff)													
* Return        : u8 data			->	从MISO读取的数据
*				：NOne											
*******************************************************************************/
u16 SPI_ReadByte(u8 SPIx, u16 dummy_data)
{
  	u16 data = 0;
  	if(SPIx == USE_SPI1)
  	{
  	 	/*!< Wait until the transmit buffer is empty */
	  	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	  	{
	  	}
		/*!< Send the byte */
		SPI_I2S_SendData(SPI1, dummy_data);
		
		/*!< Wait until a data is received */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		{
		}
		/*!< Get the received data */
		data = SPI_I2S_ReceiveData(SPI1);
		
		/*!< Return the shifted data */
		return data;
  	}
	else if(SPIx == USE_SPI2)
	{
			/*!< Wait until the transmit buffer is empty */
	  	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	  	{
	  	}
		/*!< Send the byte */
		SPI_I2S_SendData(SPI2, dummy_data);
		
		/*!< Wait until a data is received */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
		{
		}
		/*!< Get the received data */
		data = SPI_I2S_ReceiveData(SPI2);
		
		/*!< Return the shifted data */
		return data;
	}
	return 0;
}

/*******************************************************************************
* Function Name	: SPI_SetCS											
* Description   : SPI NSS做普通GPIO使用,NSS输出高电平 		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : None													
* Return        : None
*				：NOne											
*******************************************************************************/
void SPI_SetCS(u8 SPIx)
{	
	GPIO_SetBits(SPI_CS_PORT[SPIx], SPI_CS_PIN[SPIx]);
}
/*******************************************************************************
* Function Name	: SPI_ClrCS											
* Description   : SPI NSS做普通GPIO使用,NSS输出低电平 		
* Input         : u8 SPIx			->	所使用的SPI 															
* 		        : None													
* Return        : None
*				：NOne											
*******************************************************************************/
void SPI_ClrCS(u8 SPIx)
{	
	GPIO_ResetBits(SPI_CS_PORT[SPIx], SPI_CS_PIN[SPIx]);
}

/*******************************************************************************
* Function Name	: SPI_SetSpeed											
* Description   : 设置SPI速度 		
* Input         : u8 SPIx					->	所使用的SPI															
* 		        : u8 baud_rate_prescaler 	-> 	分频数(SPI1最高4分频,SPI2最高2分频)												
* Return        : None			
*				：None										
*******************************************************************************/
void SPI_SetSpeed(u8 SPIx, u8 baud_rate_prescaler)
{
	uint16_t tmpreg = 0;

	u16 rate_buffer[] = 
					{
						SPI_BaudRatePrescaler_2,     
						SPI_BaudRatePrescaler_4,      
						SPI_BaudRatePrescaler_8,     
						SPI_BaudRatePrescaler_16,     
						SPI_BaudRatePrescaler_32,     
						SPI_BaudRatePrescaler_64,     
						SPI_BaudRatePrescaler_128,      
						SPI_BaudRatePrescaler_256,    
					};
					
	if(baud_rate_prescaler > 7)
	{
		baud_rate_prescaler = 7;
	}
	if(SPIx == USE_SPI1)
	{	
		SPI_Cmd(SPI1, DISABLE);
		tmpreg = SPI1->CR1;
		tmpreg &= 0XFFC7;
		tmpreg |=  rate_buffer[baud_rate_prescaler];
		SPI1->CR1 = tmpreg;
		SPI_Cmd(SPI1, ENABLE);
	}
	else if(SPIx == USE_SPI2)
	{
		SPI_Cmd(SPI2, DISABLE);
		tmpreg = SPI2->CR1;
		tmpreg &= 0XFFC7;
		tmpreg |=  rate_buffer[baud_rate_prescaler];
		SPI2->CR1 = tmpreg;
		SPI_Cmd(SPI2, ENABLE);
	}
}

void SPI_WriteReg(u16 reg, u16 val)
{
		u8 retry;
		reg |= 0x8000;
		while((SPI2->SR&1<<1)==0)//等待发送区空	
		{
			retry++;
			if(retry>200)
			{
				break;
			}
		}		
		SPI2->DR = reg;
		while((SPI2->SR&1<<0)==0) //等待接收完一个byte  
		{	
			;
		}	  						    
		reg = SPI2->DR;          //返回收到的数据
		while((SPI2->SR&1<<1)==0)//等待发送区空	
		{
			retry++;
			if(retry>200)
			{
				break;
			}
		}		
		SPI2->DR = val;
		while((SPI2->SR&1<<0)==0) //等待接收完一个byte  
		{	
			;
		}	  						    
		reg = SPI2->DR;          //返回收到的数据
}

void SPI_Test(u8 SPIx)
{
	u16 i = 0;
	u8 retry;
	u32 reg_val = 0;
	
	SPI_GpioInit(SPIx);
	SPI_SetSpiSoftCS(SPIx);
	SPI_MsterConfig(SPIx, 0, 16);
	SPI_SetSpeed(SPIx, 3);

	//WiFi_SpiWriteReg(0x70, 0x02);
	while(1)
	{
		//Wifi_SpiReadReg(0x6c, &reg_val);
		Delay_nUS(10);
	}
}


