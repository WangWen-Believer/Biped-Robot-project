#include "dma.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////// 	
DMA_HandleTypeDef  UART2TxDMA_Handler;      //DMA句柄


//DMAx的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择,@ref DMA_channel DMA_CHANNEL_0~DMA_CHANNEL_7
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx)
{ 
    __HAL_RCC_DMA1_CLK_ENABLE();//DMA1时钟使能 
    
    __HAL_LINKDMA(&UART2_Handler,hdmatx,UART2TxDMA_Handler);    //将DMA与USART2联系起来(发送DMA)
    
    //Tx DMA配置
    UART2TxDMA_Handler.Instance=DMA_Streamx;                            //数据流选择
    UART2TxDMA_Handler.Init.Channel=chx;                                //通道选择
    UART2TxDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //存储器到外设
    UART2TxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //外设非增量模式
    UART2TxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //存储器增量模式
    UART2TxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //外设数据长度:8位
    UART2TxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //存储器数据长度:8位
    UART2TxDMA_Handler.Init.Mode=DMA_NORMAL;                            //外设流控模式
    UART2TxDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //中等优先级
    UART2TxDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    UART2TxDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    UART2TxDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //存储器突发单次传输
    UART2TxDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //外设突发单次传输
    
    HAL_DMA_DeInit(&UART2TxDMA_Handler);     
    HAL_DMA_Init(&UART2TxDMA_Handler);

} 
void Watit_Sendcomplete(void)
{
		    while(1)
		    {
                if(__HAL_DMA_GET_FLAG(&UART2TxDMA_Handler,DMA_FLAG_TCIF2_6))//等待DMA1_Steam6传输完成
                {
                    __HAL_DMA_CLEAR_FLAG(&UART2TxDMA_Handler,DMA_FLAG_TCIF2_6);//清除DMA1_Steam6传输完成标志
                    HAL_UART_DMAStop(&UART2_Handler);      //传输完成以后关闭串口DMA
					           break; 
                }   
		    }
}







 
 
