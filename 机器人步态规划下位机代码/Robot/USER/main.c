#include "allconfig.h"
#define Servo_init 0   //初始化舵机
#define SIZE sizeof(TEXT_Buffer)
void Control_Servo(u8 ID,float angle,u8 point,int time);
//void Flash_Angle(void);
extern u8 angle_7[20];
extern u8 angle_8[20];
const u8 TEXT_Buffer[]={"Apollo STM32F7 QSPI TEST"};
//extern u8 SERVO_ExpectPosition[17][7];
	u32 FLASH_SIZE;
	u8 datatemp[SIZE];
int main(void)
{
  u16 i,j,k=0;
	u8 t=0;

	
	Cache_Enable();                 //打开L1-Cache
	HAL_Init();				        //初始化HAL库
	Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
	delay_init(216);                //延时初始化
//	LED_Init();                     //初始化LED
//	KEY_Init();                     //初始化按键
//	SDRAM_Init();                   //初始化SDRAM
//	LCD_Init();                     //LCD初始化    
//	W25QXX_Init();		            //初始化W25QXX
	MYDMA_Config(DMA1_Stream6,DMA_CHANNEL_4);//初始化DMA	
	POINT_COLOR=RED; 
	uart_init(1000000);//舵机通道
//  LCD_ShowString(20,50,200,16,16,"Biped Robot Control System");
	#if Servo_init  
			        //串口初始化 
//		ReadServo_state(0xfe,1);                              //读取状态
		while(1)
		{
			t=KEY_Scan(0);
//			if(t==WKUP_PRES)  //KEY0按下
//	  	{
//			 delay_ms(5);
//		 	 LCD_ShowString(30,150,200,16,16,"Start Transimit....");                                     			          
      if(k==0)
			{			
         
			  Servo_Lock(DISABLE);//关闭锁保护		
        EnableTorque(0xfe);//开扭矩				
			  Set_Servo_ID(10);
			  Servo_Lock(ENABLE);//锁保护
      k++;
			}
			delay_ms(100);
			if(k==1)
			{ 
		    Write_Position(2,502,0,1000);    //转至指定位置 设定速度 时间                                       			          		   
		 	  delay_ms(120);				
   			}			  
//    }
    j=20;
	 for(i=0;i<=5;i++)
  	{								  
	    delay_ms(10);
	    LCD_ShowxNum(j,230,Receive_data[i],3,16,0x80);
	    j+=30;
		}
		LED1_Toggle;	
		}
	
	
	
	#endif

//	delay_ms(100);
//  W25QXX_Check();		
//  FLASH_SIZE=32*1024*1024;	//FLASH 大小为32M字节	
//	Flash_Angle();//取出数据
//SYNC_Write_Buff(SERVO_ExpectPosition,17);
//		Write_Position(20,512,0,1000); 

  while(1)
  {	  
//		LCD_ShowxNum(80,80,angle_7[0],2,32,0);
//		  LCD_ShowxNum(120,80,angle_7[1],2,32,0);
//		  LCD_ShowxNum(80,120,angle_8[0],2,32,0);
//		  LCD_ShowxNum(120,120,angle_8[1],2,32,0);
		  delay_ms(20);
//			t=KEY_Scan(0);			
//		  LED0_Toggle;
//		if(t==WKUP_PRES)
//		{

//				Control_Servo(1,14,0,500);  //倾斜
//				Control_Servo(5,8.6,0,500);
//				 
//				Control_Servo(6,18.6,0,500);
//		    Control_Servo(10,2.7,0,500);
//				SYNC_Write_Buff(SERVO_ExpectPosition,17);	
       Write_Position(15,400,0,500); 		
//		    delay_ms(500);
//        for(i=0;i<20;i++)    //抬脚
//			{
//				Control_Servo(1,angle_7[i],1,25);
//				Control_Servo(8,angle_8[i],0,25);
//				Control_Servo(9,angle_8[i]-angle_7[i],1,25);
//				SYNC_Write_Buff(SERVO_ExpectPosition,17);		
//				delay_ms(25);
//			}

//			
//	   } 
//		 if(t==KEY1_PRES)  
//		 {
//			      for(i=19;i>0;i--)    //落脚
//			{
//				Control_Servo(1,angle_7[i],1,25);
//				Control_Servo(8,angle_8[i],0,25);
//				Control_Servo(9,angle_8[i]-angle_7[i],1,25);
//				SYNC_Write_Buff(SERVO_ExpectPosition,17);		
//				delay_ms(25);
//		 }			 
//	}
//		 if(t==KEY2_PRES)//KEY1按下,写入W25Q128
//		{
//			LCD_Fill(0,170,239,319,WHITE);//清除半屏    
// 			LCD_ShowString(30,170,200,16,16,"Start Write QSPI....");
//			W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//从倒数第100个地址处开始,写入SIZE长度的数据
//			LCD_ShowString(30,170,200,16,16,"QSPI Write Finished!");	//提示传送完成
//		}
//		if(t==WKUP_PRES)//KEY0按下,读取字符串并显示
//		{
// 			LCD_ShowString(30,170,200,16,16,"Start Read QSPI.... ");
//			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//从倒数第100个地址处开始,读出SIZE个字节
//			LCD_ShowString(30,170,200,16,16,"The Data Readed Is:   ");	//提示传送完成
//			LCD_ShowString(30,190,200,16,16,datatemp);					//显示读到的字符串
//		} 

}
	}

void Control_Servo(u8 ID,float angle,u8 point,int time)
{
	u8 i;
	u16 number;
	i=ID-1;
	 	
	if(ID==7||ID==4)
	{
	  if(point==1)
			point=0;
		else
			point=1;
	}
	if(ID==8) point=1;
	
	number=Together_Number(&Servo_State[i][1],&Servo_State[i][2]);//取出标准数据来
	if (point==1)//前倾
	number=number+(int)(angle*5.12);
	else
	number=number-(int)(angle*5.12);	
	Split_Number(&SERVO_ExpectPosition[i][1],&SERVO_ExpectPosition[i][2], number);
	Split_Number(&SERVO_ExpectPosition[i][3],&SERVO_ExpectPosition[i][4], time);
}
//void Flash_Angle(u8 *datatemp)
//{
//	u8 i;
//	LCD_ShowString(30,170,200,16,16,"Start Read QSPI.... ");
//	for	(i=1;i<2;i++)
//	{//建立一个角度数组 robto_angle[17][20]
//		W25QXX_Read(datatemp,FLASH_SIZE-(20*(21-i)),20);					//从倒数第100个地址处开始,读出SIZE个字节
//	}
//	LCD_ShowString(30,170,200,16,16,"The Data Readed Is:   ");	//提示传送完成
//	LCD_ShowString(30,190,200,16,16,datatemp);					//显示读到的字符串
//}
