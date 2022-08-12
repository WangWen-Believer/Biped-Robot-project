/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_core.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Standard protocol processing (USB v2.0)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
////////////调试信息输出控制/////////////
//输出基本枚举步骤
#define USB_DEBUG0			1
//输出详细通信数据
#define USB_DEBUG1			0
//输出请求字符串描述的请求代码
#define USB_DEBUG_STR_DESC	0
/////////////////////////////////////////

#define ValBit(VAR,Place)    (VAR & (1 << Place))
#define SetBit(VAR,Place)    (VAR |= (1 << Place))
#define ClrBit(VAR,Place)    (VAR &= ((1 << Place) ^ 255))

#ifdef STM32F10X_CL
 #define Send0LengthData()  {PCD_EP_Write (0, 0, 0) ; vSetEPTxStatus(EP_TX_VALID);}
#else
#define Send0LengthData() { _SetEPTxCount(ENDP0, 0); \
    vSetEPTxStatus(EP_TX_VALID); \
  }
#endif /* STM32F10X_CL */

#define vSetEPRxStatus(st) (SaveRState = st)
#define vSetEPTxStatus(st) (SaveTState = st)

#define USB_StatusIn() Send0LengthData()
#define USB_StatusOut() vSetEPRxStatus(EP_RX_VALID)

#define StatusInfo0 StatusInfo.bw.bb1 /* Reverse bb0 & bb1 */
#define StatusInfo1 StatusInfo.bw.bb0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t_uint8_t StatusInfo;

bool Data_Mul_MaxPacketSize = FALSE;
/* Private function prototypes -----------------------------------------------*/
static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Standard_GetConfiguration.
* Description    : Return the current configuration variable address.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 1 , if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
uint8_t *Standard_GetConfiguration(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength =
      sizeof(pInformation->Current_Configuration);
    return 0;
  }
#if USB_DEBUG0		> 0
	Prints("-----------调用用户回调函数------------\r\n");
#endif
  pUser_Standard_Requests->User_GetConfiguration();
  return (uint8_t *)&pInformation->Current_Configuration;
}

/*******************************************************************************
* Function Name  : Standard_SetConfiguration.
* Description    : This routine is called to set the configuration value
*                  Then each class should configure device themself.
* Input          : None.
* Output         : None.
* Return         : Return USB_SUCCESS, if the request is performed.
*                  Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetConfiguration(void)
{

  if ((pInformation->USBwValue0 <=
      Device_Table.Total_Configuration) && (pInformation->USBwValue1 == 0)
      && (pInformation->USBwIndex == 0)) /*call Back usb spec 2.0*/
  {
    pInformation->Current_Configuration = pInformation->USBwValue0;
	#if USB_DEBUG0		> 0
		Prints("-------调用用户回调函数,通常赋值bDeviceState = CONFIGURED--------\r\n");
	#endif
    pUser_Standard_Requests->User_SetConfiguration();
    return USB_SUCCESS;
  }
  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : Standard_GetInterface.
* Description    : Return the Alternate Setting of the current interface.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
uint8_t *Standard_GetInterface(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength =
      sizeof(pInformation->Current_AlternateSetting);
    return 0;
  }
#if USB_DEBUG0		> 0
	Prints("-----------调用用户回调函数------------\r\n");
#endif
  pUser_Standard_Requests->User_GetInterface();
  return (uint8_t *)&pInformation->Current_AlternateSetting;
}

/*******************************************************************************
* Function Name  : Standard_SetInterface.
* Description    : This routine is called to set the interface.
*                  Then each class should configure the interface them self.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetInterface(void)
{
  RESULT Re;
  /*Test if the specified Interface and Alternate Setting are supported by
    the application Firmware*/
  Re = (*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, pInformation->USBwValue0);

  if (pInformation->Current_Configuration != 0)
  {
    if ((Re != USB_SUCCESS) || (pInformation->USBwIndex1 != 0)
        || (pInformation->USBwValue1 != 0))
    {
      return  USB_UNSUPPORT;
    }
    else if (Re == USB_SUCCESS)
    {
		#if USB_DEBUG0		> 0
			Prints("-----------调用用户回调函数------------\r\n");
		#endif
      pUser_Standard_Requests->User_SetInterface();
      pInformation->Current_Interface = pInformation->USBwIndex0;
      pInformation->Current_AlternateSetting = pInformation->USBwValue0;
      return USB_SUCCESS;
    }

  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_GetStatus.
* Description    : Copy the device request data to "StatusInfo buffer".
* Input          : - Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is at end of data block,
*                  or is invalid when "Length" is 0.
*******************************************************************************/
uint8_t *Standard_GetStatus(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 2;
    return 0;
  }

  /* Reset Status Information */
  StatusInfo.w = 0;

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /*Get Device Status */
    uint8_t Feature = pInformation->Current_Feature;

    /* Remote Wakeup enabled */
    if (ValBit(Feature, 5))
    {
      SetBit(StatusInfo0, 1);
    }
    else
    {
      ClrBit(StatusInfo0, 1);
    }      

    /* Bus-powered */
    if (ValBit(Feature, 6))
    {
      SetBit(StatusInfo0, 0);
    }
    else /* Self-powered */
    {
      ClrBit(StatusInfo0, 0);
    }
  }
  /*Interface Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    return (uint8_t *)&StatusInfo;
  }
  /*Get EndPoint Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    uint8_t Related_Endpoint;
    uint8_t wIndex0 = pInformation->USBwIndex0;

    Related_Endpoint = (wIndex0 & 0x0f);
    if (ValBit(wIndex0, 7))
    {
      /* IN endpoint */
      if (_GetTxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* IN Endpoint stalled */
      }
    }
    else
    {
      /* OUT endpoint */
      if (_GetRxStallStatus(Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* OUT Endpoint stalled */
      }
    }

  }
  else
  {
    return NULL;
  }
#if USB_DEBUG0		> 0
	Prints("-----------调用用户回调函数------------\r\n");
#endif
  pUser_Standard_Requests->User_GetStatus();
  return (uint8_t *)&StatusInfo;
}

/*******************************************************************************
* Function Name  : Standard_ClearFeature.
* Description    : Clear or disable a specific feature.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_ClearFeature(void)
{
  uint32_t     Type_Rec = Type_Recipient;
  uint32_t     Status;


  if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {/*Device Clear Feature*/
    ClrBit(pInformation->Current_Feature, 5);
    return USB_SUCCESS;
  }
  else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {/*EndPoint Clear Feature*/
    DEVICE* pDev;
    uint32_t Related_Endpoint;
    uint32_t wIndex0;
    uint32_t rEP;

    if ((pInformation->USBwValue != ENDPOINT_STALL)
        || (pInformation->USBwIndex1 != 0))
    {
      return USB_UNSUPPORT;
    }

    pDev = &Device_Table;
    wIndex0 = pInformation->USBwIndex0;
    rEP = wIndex0 & ~0x80;
    Related_Endpoint = ENDP0 + rEP;

    if (ValBit(pInformation->USBwIndex0, 7))
    {
      /*Get Status of endpoint & stall the request if the related_ENdpoint
      is Disabled*/
      Status = _GetEPTxStatus(Related_Endpoint);
    }
    else
    {
      Status = _GetEPRxStatus(Related_Endpoint);
    }

    if ((rEP >= pDev->Total_Endpoint) || (Status == 0)
        || (pInformation->Current_Configuration == 0))
    {
      return USB_UNSUPPORT;
    }


    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      if (_GetTxStallStatus(Related_Endpoint ))
      {
      #ifndef STM32F10X_CL
        ClearDTOG_TX(Related_Endpoint);
      #endif /* STM32F10X_CL */
        SetEPTxStatus(Related_Endpoint, EP_TX_VALID);
      }
    }
    else
    {
      /* OUT endpoint */
      if (_GetRxStallStatus(Related_Endpoint))
      {
        if (Related_Endpoint == ENDP0)
        {
          /* After clear the STALL, enable the default endpoint receiver */
          SetEPRxCount(Related_Endpoint, Device_Property.MaxPacketSize);
          _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
        }
        else
        {
        #ifndef STM32F10X_CL
          ClearDTOG_RX(Related_Endpoint);
        #endif /* STM32F10X_CL */
          _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
        }
      }
    }
	#if USB_DEBUG0		> 0
		Prints("-----------调用用户回调函数------------\r\n");
	#endif
    pUser_Standard_Requests->User_ClearFeature();
    return USB_SUCCESS;
  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_SetEndPointFeature
* Description    : Set or enable a specific feature of EndPoint
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetEndPointFeature(void)
{
  uint32_t    wIndex0;
  uint32_t    Related_Endpoint;
  uint32_t    rEP;
  uint32_t    Status;

  wIndex0 = pInformation->USBwIndex0;
  rEP = wIndex0 & ~0x80;
  Related_Endpoint = ENDP0 + rEP;

  if (ValBit(pInformation->USBwIndex0, 7))
  {
    /* get Status of endpoint & stall the request if the related_ENdpoint
    is Disabled*/
    Status = _GetEPTxStatus(Related_Endpoint);
  }
  else
  {
    Status = _GetEPRxStatus(Related_Endpoint);
  }

  if (Related_Endpoint >= Device_Table.Total_Endpoint
      || pInformation->USBwValue != 0 || Status == 0
      || pInformation->Current_Configuration == 0)
  {
    return USB_UNSUPPORT;
  }
  else
  {
    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      _SetEPTxStatus(Related_Endpoint, EP_TX_STALL);
    }

    else
    {
      /* OUT endpoint */
      _SetEPRxStatus(Related_Endpoint, EP_RX_STALL);
    }
  }
#if USB_DEBUG0		> 0
	Prints("-----------调用用户回调函数------------\r\n");
#endif
  pUser_Standard_Requests->User_SetEndPointFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_SetDeviceFeature.
* Description    : Set or enable a specific feature of Device.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetDeviceFeature(void)
{
  SetBit(pInformation->Current_Feature, 5);
#if USB_DEBUG0		> 0
	Prints("-----------调用用户回调函数------------\r\n");
#endif
  pUser_Standard_Requests->User_SetDeviceFeature();
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_GetDescriptorData.
* Description    : Standard_GetDescriptorData is used for descriptors transfer.
*                : This routine is used for the descriptors resident in Flash
*                  or RAM
*                  pDesc can be in either Flash or RAM
*                  The purpose of this routine is to have a versatile way to
*                  response descriptors request. It allows user to generate
*                  certain descriptors with software or read descriptors from
*                  external storage part by part.
* Input          : - Length - Length of the data in this transfer.
*                  - pDesc - A pointer points to descriptor struct.
*                  The structure gives the initial address of the descriptor and
*                  its original size.
* Output         : None.
* Return         : Address of a part of the descriptor pointed by the Usb_
*                  wOffset The buffer pointed by this address contains at least
*                  Length bytes.
*******************************************************************************/
uint8_t *Standard_GetDescriptorData(uint16_t Length, ONE_DESCRIPTOR *pDesc)
{
  uint32_t  wOffset;

  wOffset = pInformation->Ctrl_Info.Usb_wOffset;
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
    return 0;
  }

  return pDesc->Descriptor + wOffset;
}

/*******************************************************************************
* Function Name  : DataStageOut.
* Description    : Data stage of a Control Write Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageOut(void)
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  uint32_t save_rLength;

  save_rLength = pEPinfo->Usb_rLength;	//待接收的数据长度

  	if (pEPinfo->CopyData && save_rLength)
  	{										//如果有数据待要接收
    	uint8_t *Buffer;
    	uint32_t Length;
	#if USB_DEBUG0 	> 0
		Prints("设备接收: ");
		PrintShortIntHex(save_rLength);
		Prints("个数据\r\n");
	#endif
    	Length = pEPinfo->PacketSize;		//端点包长度
    	if (Length > save_rLength)			
    	{									//端点包长度大于待接收数据长度
      		Length = save_rLength;			//可以接收数据,并设置为实际待接收长度
    	}
											//否则本次接收到的是一个包长的数据
    	Buffer = (*pEPinfo->CopyData)(Length);	//返回接收送数据起始地址
    	pEPinfo->Usb_rLength -= Length;		//全局信息修改：待接收长度减去已接收长度
    	pEPinfo->Usb_rOffset += Length;		//全局信息修改：偏移加上已接收长度

  	#ifdef STM32F10X_CL  
    	PCD_EP_Read(ENDP0, Buffer, Length); 
  	#else  								//数据由端点缓冲区拷贝到用户缓冲区
    	PMAToUserBufferCopy(Buffer, GetEPRxAddr(ENDP0), Length);
  	#endif  /* STM32F10X_CL */
	
	#if USB_DEBUG1	> 0
	{
		u16 i = 0;
		u8* temp_buf = Buffer;
		for(i = 0; i < Length; i ++)
		{
			PrintHex(*temp_buf ++);
			if(!((i+1)&0x0f))
			{								//一行最多显示16个数据
				Prints("\r\n");				
			}
		}
		if((i)&0x0f)
		{									//总个数不是16的整数倍,则换行
			Prints("\r\n");					//否则已经上for循环中换行
		}
	}
	#endif
  	}

  	if (pEPinfo->Usb_rLength != 0)
  	{										//如果待接收长度不等于0则使能接收端点继续接收
   	 	vSetEPRxStatus(EP_RX_VALID);/* re-enable for next data reception */
   	 	SetEPTxCount(ENDP0, 0);				//下一个过程可能变成IN状态过程(在数据没有传完的情况下主机改变数据方向)
    	vSetEPTxStatus(EP_TX_VALID);/* Expect the host to abort the data OUT stage */
  	}
  	/* Set the next State*/
  	if (pEPinfo->Usb_rLength >= pEPinfo->PacketSize)
  	{										//如果待接收长度大于等于端点包长度,继续处于OUT数据过程
   	 #if USB_DEBUG0	> 0
		Prints("继续接收中...\r\n");
		#endif
		pInformation->ControlState = OUT_DATA;
  	}
  	else
  	{										//如果待接收长度小于端点包长度
    	if (pEPinfo->Usb_rLength > 0)
    	{									//还有数据要接收则进入最后一次OUT数据过程
      		pInformation->ControlState = LAST_OUT_DATA;
    	}
    	else if (pEPinfo->Usb_rLength == 0)
    	{									//否则等待进入IN状态过程
		#if USB_DEBUG0	> 0
			Prints("最后一次Out数据过程,即将进入IN状态过程\r\n");
		#endif
      		pInformation->ControlState = WAIT_STATUS_IN;
      		USB_StatusIn();					//在端点缓冲区准备0字节的数据,
    	}									//主机IN令牌包到的时候将取走数据并ACK
  	}
}

/*******************************************************************************
* Function Name  : DataStageIn.
* Description    : Data stage of a Control Read Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageIn(void)
{
  ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
  uint32_t save_wLength = pEPinfo->Usb_wLength;		//待发送数据长度
  uint32_t ControlState = pInformation->ControlState;

  uint8_t *DataBuffer;
  uint32_t Length;
	
  	if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))
  	{										//如果待发送长度为0且为最后一次发送(如第一次请求设备描述符-18字节
    	if(Data_Mul_MaxPacketSize == TRUE)	//则只会触发一次IN数据过程中断，随后进入OUT状态过程
    	{									//如果带发送数据的长度刚好是包长度的整数倍
      	/* No more data to send and empty packet */
		#if USB_DEBUG0	> 0
			Prints("为端点最大包长整数倍,返回0长度数据(本次传输最后一次发送)\r\n");
		#endif
			
      		Send0LengthData();				//发送0长度数据
      		ControlState = LAST_IN_DATA;	//修改状态为最后一次发送
      		Data_Mul_MaxPacketSize = FALSE;	//恢复标志位FALSE
    	}
    	else 
   	 	{
  		/* No more data to send so STALL the TX Status*/
		#if USB_DEBUG0	> 0
			Prints("IN数据过程完成,即将进入Out状态过程\r\n");
		#endif
      		ControlState = WAIT_STATUS_OUT;	//否则已经是最后最后一次发送
											//将进入OUT状态过程
    	#ifdef STM32F10X_CL      
      		PCD_EP_Read (ENDP0, 0, 0);
    	#endif  /* STM32F10X_CL */ 
    
    	#ifndef STM32F10X_CL 
      		vSetEPTxStatus(EP_TX_STALL);	//改变发送状态为STALL
    	#endif  /* STM32F10X_CL */ 
    	}
	
    	goto Expect_Status_Out;				//跳转到函数最后
  	}

  	Length = pEPinfo->PacketSize;   		//端点0包长度
  	ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA; //如果包长度大于或等于待发送长度，则为最后一次发送

  	if (Length > save_wLength)        		//如果包长度大于待发送的长度，则返回实际待发送的长度
  	{
    	Length = save_wLength;
  	}
	
  	DataBuffer = (*pEPinfo->CopyData)(Length);	//此时Length不为0，将返回用户待发送缓冲区的“首”地址
	
#if USB_DEBUG0	> 0
	Prints("设备正在返回数据->DataStageIn()...\r\n");
	Prints("本次传输返回: ");
	PrintShortIntHex(Length);
	Prints("个数据\r\n");
#endif
	
#if USB_DEBUG1	> 0
{
	u16 i = 0;
	u8* temp_buf = DataBuffer;
	for(i = 0; i < Length; i ++)
	{
		PrintHex(*temp_buf ++);
		if(!((i+1)&0x0f))
		{									//一行最多显示16个数据
			Prints("\r\n");				
		}
	}
	if((i)&0x0f)
	{										//总个数不是16的整数倍,则换行
			Prints("\r\n");					//否则已经上for循环中换行
	}
		
}
#endif
											//即本次用户缓冲区准备发送的第一个元素地址,不一定
#ifdef STM32F10X_CL							//是用户缓冲区首地址
  	PCD_EP_Write (ENDP0, DataBuffer, Length);
#else                                   	//将用户数据拷贝到USB缓冲区
  	UserToPMABufferCopy(DataBuffer, GetEPTxAddr(ENDP0), Length);
#endif /* STM32F10X_CL */ 

	SetEPTxCount(ENDP0, Length);         	//设置端点0的发生数据大小
	
	pEPinfo->Usb_wLength -= Length;     	//全局信息修改：待发送长度减去已经发生了的长度
	pEPinfo->Usb_wOffset += Length;			//全局信息修改：发送偏移加上已发发送了长度
	vSetEPTxStatus(EP_TX_VALID);			//发送状态为VALID
										
	USB_StatusOut();/* Expect the host to abort the data IN stage */

Expect_Status_Out:							//全局信息修改：改变枚举阶段状态，可能有两个状态：
  	pInformation->ControlState = ControlState;//1.继续发送数据过程；2.OUT状态过程
}

/*******************************************************************************
* Function Name  : NoData_Setup0.
* Description    : Proceed the processing of setup request without data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NoData_Setup0(void)
{
	RESULT Result = USB_UNSUPPORT;
	uint32_t RequestNo = pInformation->USBbRequest;
	uint32_t ControlState;

  	if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  	{
    #if USB_DEBUG0	> 0
		Prints("标准请求->设备");		
	#endif
		/* Device Request*/
    	/* SET_CONFIGURATION*/
    	if (RequestNo == SET_CONFIGURATION)
    	{												//只有在设置配有以后才能启用非零端点
		#if USB_DEBUG0	> 0
			Prints("->设置配置\r\n");		
		#endif
      		Result = Standard_SetConfiguration();			//执行了这条语句bDeviceState = CONFIGURED;
    	}

    	/*SET ADDRESS*/
    	else if (RequestNo == SET_ADDRESS)
    	{
      		if ((pInformation->USBwValue0 > 127) || (pInformation->USBwValue1 != 0)
          	|| (pInformation->USBwIndex != 0)
          	|| (pInformation->Current_Configuration != 0))
       		/* Device Address should be 127 or less*/
      		{
        		ControlState = STALLED;
			#if USB_DEBUG0	> 0
				Prints("地址范围错误,STALLED->函数返回\r\n");		
			#endif
        		goto exit_NoData_Setup0;
      		}
      		else
      		{
			#if USB_DEBUG0	> 0
				Prints("请求设置地址\r\n");		
			#endif
				Result = USB_SUCCESS;
	
	      	#ifdef STM32F10X_CL
	         	SetDeviceAddress(pInformation->USBwValue0);
	      	#endif  /* STM32F10X_CL */
      		}
		}
    	/*SET FEATURE for Device*/
    	else if (RequestNo == SET_FEATURE)
    	{
      		if ((pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP)
          		&& (pInformation->USBwIndex == 0)
          		&& (ValBit(pInformation->Current_Feature, 5)))
      		{
      		#if USB_DEBUG0	> 0
				Prints("设置Feature\r\n");		
		  	#endif
				Result = Standard_SetDeviceFeature();
      		}
      		else
      		{
        		Result = USB_UNSUPPORT;
      		}
    	}
    	/*Clear FEATURE for Device */
    	else if (RequestNo == CLEAR_FEATURE)
    	{
      		if (pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP
          		&& pInformation->USBwIndex == 0
          		&& ValBit(pInformation->Current_Feature, 5))
      		{
      		#if USB_DEBUG0	> 0
				Prints("清除Feature\r\n");		
		  	#endif
				Result = Standard_ClearFeature();
      		}
      		else
      		{
      		#if USB_DEBUG0	> 0
				Prints("->不支持的设备接收请求\r\n");		
			#endif
				Result = USB_UNSUPPORT;
      		}
    	}

  	}

  	/* Interface Request*/
  	else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  	{
  	#if USB_DEBUG0	> 0
		Prints("标准请求->Interface");		
	#endif
		/*SET INTERFACE*/
    	if (RequestNo == SET_INTERFACE)
    	{
		#if USB_DEBUG0	> 0
			Prints("->设置Interface\r\n");		
		#endif
			Result = Standard_SetInterface();
    	}
  	}

  	/* EndPoint Request*/
  	else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  	{
	#if USB_DEBUG0	> 0
		Prints("标准请求->EndPoint");		
	#endif
		/*CLEAR FEATURE for EndPoint*/
    	if (RequestNo == CLEAR_FEATURE)
    	{
    	#if USB_DEBUG0	> 0
			Prints("->清除Feature\r\n");		
		#endif
			Result = Standard_ClearFeature();
    	}
    	/* SET FEATURE for EndPoint*/
    	else if (RequestNo == SET_FEATURE)
    	{
    	#if USB_DEBUG0	> 0
			Prints("->设置EndPointFeature\r\n");		
		#endif
			Result = Standard_SetEndPointFeature();
    	}
  	}
  	else
  	{
  	#if USB_DEBUG0	> 0
		Prints("->不支持的请求\r\n");		
	#endif
		Result = USB_UNSUPPORT;
  	}


  	if (Result != USB_SUCCESS)
  	{										//如果是标准请求以外的请求，调用用户提供的回调函数
	#if USB_DEBUG0	> 0
		Prints("标准请求以外的请求, ------调用用户提供的回调函数------\r\n");		
	#endif    
		Result = (*pProperty->Class_NoData_Setup)(RequestNo);
    	if (Result == USB_NOT_READY)
    	{
			ControlState = PAUSE;
		#if USB_DEBUG0	> 0
			Prints("USB_NOT_READY,PAUSE->函数返回\r\n");		
		#endif
		
      	goto exit_NoData_Setup0;
   	 	}
  	}

  	if (Result != USB_SUCCESS)
  	{
		ControlState = STALLED;
	#if USB_DEBUG0	> 0
		Prints("不支持的控制传输请求,STALLED->函数返回\r\n");		
	#endif
    goto exit_NoData_Setup0;
  	}
										//正常情况下,在无数据过程的控制传输中,SETUP以后是IN状态过程
  	ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */
	
  	USB_StatusIn();						//准备好0字节数据在端点缓冲区,在主机下一个IN令牌包时返回,主机再ACK

exit_NoData_Setup0:
  	pInformation->ControlState = ControlState;
  	return;
}

/*******************************************************************************
* Function Name  : Data_Setup0.
* Description    : Proceed the processing of setup request with data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Data_Setup0(void)
{
	uint8_t *(*CopyRoutine)(uint16_t);
	RESULT Result;
	uint32_t Request_No = pInformation->USBbRequest;
	
	uint32_t Related_Endpoint, Reserved;
	uint32_t wOffset, Status;
	
	
	
	CopyRoutine = NULL;
	wOffset = 0;

  	/*GET DESCRIPTOR*/
  	if (Request_No == GET_DESCRIPTOR)
  	{							//请求代码为:0x06 
	#if USB_DEBUG0	> 0
		Prints("获取描述符(0x06)(1设备;2配置;3字符;4接口;5端点):\r\n");		
	#endif
    	if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    	{						//标准请求(0x80)
			uint8_t wValue1 = pInformation->USBwValue1;
			
			#if USB_DEBUG0	> 0
				Prints("->设备");
			#endif
      		if (wValue1 == DEVICE_DESCRIPTOR)
      		{						//标准请求->设备描述符18个字节
			#if USB_DEBUG0	> 0
				Prints("->设备描述符(18字节)\r\n");
			#endif
			
        		CopyRoutine = pProperty->GetDeviceDescriptor;
      		}
      		else if (wValue1 == CONFIG_DESCRIPTOR)
      		{						//标准请求->配置描述符9字节(接口描述符(9)和端点描述符(7)必须随配置描述符一起返回)
      		#if USB_DEBUG0	> 0
				Prints("->配置描述符(9字节+(接口)9*x +(端点)7*x)\r\n");
			#endif
			
				CopyRoutine = pProperty->GetConfigDescriptor;//(如果是HID设备,HID描述符要跟在接口描述符后面)
      		}
      		else if (wValue1 == STRING_DESCRIPTOR)
      		{						//标准请求->字符串描述符   (wValue0: 
      		#if USB_DEBUG0	> 0
				Prints("->字符串描述符\r\n");
			#endif
			#if USB_DEBUG_STR_DESC	> 0
				Prints("->0语言ID,1厂商字符串,2产品字符串,3产品序列号--> ");
				PrintHex(pInformation->USBwValue0);
				Prints("\r\n");
			#endif
				CopyRoutine = pProperty->GetStringDescriptor;//0语言ID,1厂商字符串,2产品字符串,3产品序列号)
			}  /* End of GET_DESCRIPTOR */
    	}
  	}

  	/*GET STATUS*/
  	else if ((Request_No == GET_STATUS) && (pInformation->USBwValue == 0)
           && (pInformation->USBwLength == 0x0002)
           && (pInformation->USBwIndex1 == 0))
  	{
    	/* GET STATUS for Device*/
    	if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
       		&& (pInformation->USBwIndex == 0))
    	{
    	#if USB_DEBUG0	> 0
			Prints("获取设备(Device)Status\r\n");		
		#endif
			CopyRoutine = Standard_GetStatus;
    	}

    	/* GET STATUS for Interface*/
    	else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    	{												//回调函数
     	 	if (((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS)
          	&& (pInformation->Current_Configuration != 0))
      		{
      		#if USB_DEBUG0	> 0
				Prints("获取接口(Interface)Status\r\n");		
			#endif
				CopyRoutine = Standard_GetStatus;
      		}
   	 	}

    	/* GET STATUS for EndPoint*/
    	else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    	{
      		Related_Endpoint = (pInformation->USBwIndex0 & 0x0f);
      		Reserved = pInformation->USBwIndex0 & 0x70;
		#if USB_DEBUG0	> 0
				Prints("获取端点(EndPoint)Status\r\n");		
		#endif
      		if (ValBit(pInformation->USBwIndex0, 7))
      		{
        		/*Get Status of endpoint & stall the request if the related_ENdpoint
        		is Disabled*/
        		Status = _GetEPTxStatus(Related_Endpoint);
      		}
      		else
      		{
        		Status = _GetEPRxStatus(Related_Endpoint);
      		}

      		if ((Related_Endpoint < Device_Table.Total_Endpoint) && (Reserved == 0)
          		&& (Status != 0))
      		{
        		CopyRoutine = Standard_GetStatus;
      		}
    	}
  	}

  	/*GET CONFIGURATION*/
	else if (Request_No == GET_CONFIGURATION)
  	{
		if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    	{
		#if USB_DEBUG0	> 0
				Prints("获取设备配置(Configuration)\r\n");		
		#endif
			CopyRoutine = Standard_GetConfiguration;
    	}
  	}
  	/*GET INTERFACE*/
  	else if (Request_No == GET_INTERFACE)
  	{
    	if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        	&& (pInformation->Current_Configuration != 0) && (pInformation->USBwValue == 0)
        	&& (pInformation->USBwIndex1 == 0) && (pInformation->USBwLength == 0x0001)
        	&& ((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS))
    	{
    	#if USB_DEBUG0	> 0
				Prints("获取接口(Interface)\r\n");		
		#endif
			CopyRoutine = Standard_GetInterface;
    	}

  	}
  
	if (CopyRoutine)
	{									//如果是标准请求(有数据过程5种中除了SYNCH_FRAME未实现)
		pInformation->Ctrl_Info.Usb_wOffset = wOffset;
		pInformation->Ctrl_Info.CopyData = CopyRoutine;
		/* sb in the original the cast to word was directly */
		/* now the cast is made step by step */
		(*CopyRoutine)(0);				//参数length  = 0,->获取待发送数据的长度,保存在Ctrl_Info.Usb_wLength中
		Result = USB_SUCCESS;			//本次data_setp0成功
	}
  	else
  	{									//如果为类请求或厂商请求则由用户提供回调函数实现
    #if USB_DEBUG0	> 0
		Prints("->非标准请求\r\n");		
		Prints("-----由用户提供回调函数实现-----(类请求或厂商请求,返回如报告描述,HID描述符)\r\n");		
	#endif
		Result = (*pProperty->Class_Data_Setup)(pInformation->USBbRequest);
    	if (Result == USB_NOT_READY)
    	{								//数据处理过程还未完成，端点将返回NAK以应对后续的请求
			pInformation->ControlState = PAUSE;
		#if USB_DEBUG0	> 0
			Prints("USB_NOT_READY,PAUSE->函数返回\r\n");
		#endif
      		return;
    	}
  	}	

  	if (pInformation->Ctrl_Info.Usb_wLength == 0xFFFF)
  	{									
	    /* Data is not ready, wait it */
	    pInformation->ControlState = PAUSE;
	#if USB_DEBUG0	> 0
		Prints("Data is not ready,PAUSE->函数返回\r\n");
	#endif
    	return;
  	}
  	if ((Result == USB_UNSUPPORT) || (pInformation->Ctrl_Info.Usb_wLength == 0))
  	{									//如果是不支持的请求或不能提供数据给主机请求
    	/* Unsupported request */		//则为STALLED
    	pInformation->ControlState = STALLED;
	#if USB_DEBUG0	> 0
		Prints("Unsupported request,STALLED->函数返回\r\n");
	#endif
    	return;
  	}


  	if (ValBit(pInformation->USBbmRequestType, 7))
  	{									//如果请求方向设备到主机,D7 = 1,有数据的setup过程
    	/* Device ==> Host */			//通常应该为这种情况
    	__IO uint32_t wLength = pInformation->USBwLength;	//请求数据长度
     
    	/* Restrict the data length to be the one host asks for */
    	if (pInformation->Ctrl_Info.Usb_wLength > wLength)	
    	{								//如果待发送长度大于请求长度，则改为实际请求的长度
      		pInformation->Ctrl_Info.Usb_wLength = wLength;
    	}
    
    	else if (pInformation->Ctrl_Info.Usb_wLength < pInformation->USBwLength)
    	{								//如果待发送长度小于请求长度
      		if (pInformation->Ctrl_Info.Usb_wLength < pProperty->MaxPacketSize)
      		{							//如果待发送长度小于最大包长度，则无需通过发送0长度数据来标志包结束
        		Data_Mul_MaxPacketSize = FALSE;
      		}
      		else if ((pInformation->Ctrl_Info.Usb_wLength % pProperty->MaxPacketSize) == 0)
      		{							//如果待发送长度能够被最大包长整除，则需要发送0长度数据来标志包结束
        		Data_Mul_MaxPacketSize = TRUE;
      		}
    	}   
										//这个变量在这里赋值以后就没有再更改过，所以两个值表征的都是最大包长
    	pInformation->Ctrl_Info.PacketSize = pProperty->MaxPacketSize;
	#if USB_DEBUG0	> 0
		Prints("设备返回: ");
		PrintShortIntHex(pInformation->Ctrl_Info.Usb_wLength);
		Prints("个数据\r\n");
	#endif
    	DataStageIn();					//SETUP -> IN(数据IN过程)，将数据填入端点缓冲区，等待下个IN令牌包到
  	}									//的时候取走数据
  	else
  	{									//如果数据方向为主机到设备,则改变相应的通信状态和端口状态
	    pInformation->ControlState = OUT_DATA;
	    vSetEPRxStatus(EP_RX_VALID); /* enable for next data reception */
  	}
  	return;
}

/*******************************************************************************
* Function Name  : Setup0_Process
* Description    : Get the device request data and dispatch to individual process.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Setup0_Process(void)
{

  	union
  	{
   	 	uint8_t* b;
   	 	uint16_t* w;
  	} pBuf;

#ifdef STM32F10X_CL
  	USB_OTG_EP *ep;
  	uint16_t offset = 0;
 
  	ep = PCD_GetOutEP(ENDP0);
  	pBuf.b = ep->xfer_buff;
#else  
  	uint16_t offset = 1;
  
  	pBuf.b = PMAAddr + (uint8_t *)(_GetEPRxAddr(ENDP0) * 2); /* *2 for 32 bits addr */
#endif /* STM32F10X_CL */

#if USB_DEBUG0		> 0
	Prints("\r\nSetup0 中断-->建立过程\r\n");
#endif		
							
  	if (pInformation->ControlState != PAUSE)
  	{									//获取标准请求的各个字段(8字节)
  	#if USB_DEBUG0		> 0
		Prints("设备可以接收新的数据\r\n");
	#endif
		pInformation->USBbmRequestType = *pBuf.b++; /* bmRequestType */
	    pInformation->USBbRequest = *pBuf.b++; /* bRequest */
	    pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
	    pInformation->USBwValue = ByteSwap(*pBuf.w++); /* wValue */
	    pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
	    pInformation->USBwIndex  = ByteSwap(*pBuf.w++); /* wIndex */
	    pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
	    pInformation->USBwLength = *pBuf.w; /* wLength */
  	}

#if USB_DEBUG1		> 0
	Prints("设备接收数据如下: \r\n");
	PrintHex(pInformation->USBbmRequestType);
	PrintHex(pInformation->USBbRequest);
	
	PrintHex(pInformation->USBwValue0);		//实际低字节(经过高低字节对调)
	PrintHex(pInformation->USBwValue1);		//实际高字节(经过高低字节对调)
	
	PrintHex(pInformation->USBwIndex0);		//实际低字节(经过高低字节对调)
	PrintHex(pInformation->USBwIndex1);		//实际高字节(经过高低字节对调)
	
	PrintHex(pInformation->USBwLength1);	//实际低字节
	PrintHex(pInformation->USBwLength0);	//实际高字节
	Prints("\r\n");
#endif	

  	pInformation->ControlState = SETTING_UP;
  	if (pInformation->USBwLength == 0)
  	{										//无数据过程(如设置地址等,下一步为IN状态过程)
	#if USB_DEBUG0 > 0
		Prints("无数据的建立过程\r\n");
	#endif
	
		/* Setup with no data stage */
		NoData_Setup0();
  	}
  	else
  	{										//有数据过程(下一步为数据过程(OUT或IN))
	#if USB_DEBUG0 > 0
		Prints("有数据的建立过程: ");
		
		#if USB_DEBUG1 > 0
			PrintShortIntHex(pInformation->USBwLength);
		#endif
		Prints("\r\n");
	#endif
		/* Setup with data stage */
  		Data_Setup0();
  	}
  	return Post0_Process();
}

/*******************************************************************************
* Function Name  : In0_Process
* Description    : Process the IN token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t In0_Process(void)
{
  	uint32_t ControlState = pInformation->ControlState;
#if USB_DEBUG0 > 0
	Prints("IN0中断-->");
#endif
  	if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  	{									//有数据要发送到主机(如主机请求了设备描述符,当数据写入端点缓冲区后,在主机IN令牌包到的时候主机取走数据,并ACK这时的状态为LAST_IN_DATA)
	#if USB_DEBUG0 > 0
		Prints("In数据过程\r\n");
	#endif
		DataStageIn();					//进入IN数据过程
    	/* ControlState may be changed outside the function */
    	ControlState = pInformation->ControlState;
  	}

  	else if (ControlState == WAIT_STATUS_IN)
  	{									//等待进入IN状态过程(由无数据的控制传输进入到的这个状态SETUP->IN)
		#if USB_DEBUG0 > 0
			Prints("IN状态过程\r\n");
		#endif
		if ((pInformation->USBbRequest == SET_ADDRESS) &&
        (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
    	{								//主机在收到设备返回的0字节数据后回复ACK(进入该中断分支),这时设备启用新的设备地址
		#if USB_DEBUG0 > 0
			Prints("设置设备地址: ");
			PrintHex(pInformation->USBwValue0);
			Prints("\r\n");
		#endif
			SetDeviceAddress(pInformation->USBwValue0);
      		pUser_Standard_Requests->User_SetDeviceAddress();
    	}	
		
    	(*pProperty->Process_Status_IN)();	//调用用户处理的状态IN回调函数
    	ControlState = STALLED;				//结束
  	}

  	else
  	{
    	ControlState = STALLED;			
  	}

  	pInformation->ControlState = ControlState;

  	return Post0_Process();
}

/*******************************************************************************
* Function Name  : Out0_Process
* Description    : Process the OUT token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Out0_Process(void)
{
	uint32_t ControlState = pInformation->ControlState;
#if USB_DEBUG0 > 0
	Prints("Out0中断-->");
#endif
  	if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
	{									//主机终止了控制传输过程
    	/* host aborts the transfer before finish */
    	ControlState = STALLED;
  	}
  	else if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA))
  	{
	#if USB_DEBUG0 > 0
		Prints("Out数据过程\r\n");
	#endif
		DataStageOut();
    	ControlState = pInformation->ControlState; /* may be changed outside the function */
  	}

  	else if (ControlState == WAIT_STATUS_OUT)
  	{
	#if USB_DEBUG0 > 0
		Prints("Out状态过程\r\n");
	#endif
		(*pProperty->Process_Status_OUT)();	//调用用户处理的状态OUT回调函数
  	#ifndef STM32F10X_CL
    	ControlState = STALLED;
  	#endif /* STM32F10X_CL */
  	}


  	/* Unexpect state, STALL the endpoint */
  	else
  	{
	#if USB_DEBUG0 > 0
		Prints("Unexpect state,-----函数返回-----\r\n");
	#endif
		ControlState = STALLED;
  	}

  	pInformation->ControlState = ControlState;

  	return Post0_Process();
}

/*******************************************************************************
* Function Name  : Post0_Process
* Description    : Stall the Endpoint 0 in case of error.
* Input          : None.
* Output         : None.
* Return         : - 0 if the control State is in PAUSE
*                  - 1 if not.
*******************************************************************************/
uint8_t Post0_Process(void)
{
#ifdef STM32F10X_CL  
  	USB_OTG_EP *ep;
#endif /* STM32F10X_CL */
      								//设置端点0接收缓冲大小
  	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);

  	if (pInformation->ControlState == STALLED)
  	{									//如果状态为结束，则设置端点相应的状态
    	vSetEPRxStatus(EP_RX_STALL);
    	vSetEPTxStatus(EP_TX_STALL);
  	}

#ifdef STM32F10X_CL
  	else if ((pInformation->ControlState == OUT_DATA) ||
      (pInformation->ControlState == WAIT_STATUS_OUT))
  	{
	    ep = PCD_GetInEP(0);
	    ep->is_in = 0;
	    OTGD_FS_EP0StartXfer(ep);
	    
	    vSetEPTxStatus(EP_TX_VALID);
  	}
  
  	else if ((pInformation->ControlState == IN_DATA) || 
      (pInformation->ControlState == WAIT_STATUS_IN))
	{
	    ep = PCD_GetInEP(0);
	    ep->is_in = 1;
	    OTGD_FS_EP0StartXfer(ep);    
  	}
#endif /* STM32F10X_CL */

  	return (pInformation->ControlState == PAUSE);
}

/*******************************************************************************
* Function Name  : SetDeviceAddress.
* Description    : Set the device and all the used Endpoints addresses.
* Input          : - Val: device adress.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetDeviceAddress(uint8_t Val)
{
#ifdef STM32F10X_CL 
  PCD_EP_SetAddress ((uint8_t)Val);
#else 
  uint32_t i;
  uint32_t nEP = Device_Table.Total_Endpoint;

  /* set address in every used endpoint */
  for (i = 0; i < nEP; i++)
  {
    _SetEPAddress((uint8_t)i, (uint8_t)i);
  } /* for */
  _SetDADDR(Val | DADDR_EF); /* set device address and enable function */
#endif  /* STM32F10X_CL */  
}

/*******************************************************************************
* Function Name  : NOP_Process
* Description    : No operation function.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NOP_Process(void)
{
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
