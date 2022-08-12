#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "ltdc.h"
#include "key.h"
#include "sdram.h"
#include "includes.h"
#include "servo.h"
#include "dma.h"
#include "gps.h"
#include "usmart.h"
#include "sdram.h"
#include "mpu.h"
#include "mpu9250.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "adc.h"
#include "w25qxx.h"
#include "malloc.h"
#include "nand.h"    
#include "ftl.h"  
/************************************************
 Biped Robot Control System
 
************************************************/
//start task
#if 1
#define START_TASK_PRIO 3 //task's priority
#define START_STK_SIZE 128
OS_TCB StartTaskTCB;      //set up the task
CPU_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);//task's code
//GPS task  
#define GPS_TASK_PRIO 10 //task's priority
#define GPS_STK_SIZE 256
OS_TCB GPS_TaskTCB;      //set up the task
CPU_STK GPS_TASK_STK[GPS_STK_SIZE];
void GPS_task(void *p_arg);//task's code
//task 2
#define GYROSCOPE_TASK_PRIO 6 //task's priority
#define GYROSCOPE_STK_SIZE 512
OS_TCB  GYROSCOPE_TaskTCB;      //set up the task
CPU_STK GYROSCOPE_TASK_STK[GYROSCOPE_STK_SIZE];
void GYROSCOPE_task(void *p_arg);//task's code
//task 3
#define SERVO_TASK_PRIO 11
#define SERVO_STK_SIZE 512
OS_TCB  SERVO_TaskTCB;
CPU_STK SERVO_TASK_STK[SERVO_STK_SIZE];
void SERVO_task(void *p_arg);
//task4
#define SERVO_RECEIVE_TASK_PRIO 12
#define SERVO_RECEIVE_STK_SIZE 128
OS_TCB  SERVO_RECEIVE_TaskTCB;
CPU_STK SERVO_RECEIVE_TASK_STK[SERVO_RECEIVE_STK_SIZE];
void SERVO_RECEIVE_task(void *p_arg);
//task 5
#define POWER_VOLTAGE_TASK_PRIO 13
#define POWER_VOLTAGE_STK_SIZE 128
OS_TCB  POWER_VOLTAGE_TaskTCB;
CPU_STK POWER_VOLTAGE_TASK_STK[POWER_VOLTAGE_STK_SIZE];
void POWER_VOLTAGE_Task(void *p_arg);
//task6
#define PC_RECEIVE_TASK_PRIO 10
#define PC_RECEIVE_STK_SIZE 512
OS_TCB  PC_RECEIVE_TaskTCB;
CPU_STK PC_RECEIVE_TASK_STK[PC_RECEIVE_STK_SIZE];
void PC_RECEIVE_task(void *p_arg);
//task7
#define ORDER_SERVO_TASK_PRIO 10
#define ORDER_SERVO_STK_SIZE 512
OS_TCB  ORDER_SERVO_TaskTCB;
CPU_STK ORDER_SERVO_TASK_STK[ORDER_SERVO_STK_SIZE];
void ORDER_SERVO_Task(void *p_arg);
//task8
#define EXECUTION_INSTRUCTION_TASK_PRIO 9
#define EXECUTION_INSTRUCTIONO_STK_SIZE 512
OS_TCB  EXECUTION_INSTRUCTION_TaskTCB;
CPU_STK EXECUTION_INSTRUCTION_TASK_STK[EXECUTION_INSTRUCTIONO_STK_SIZE];
void Execution_Instruction_Task(void *p_arg);



#endif
/***************************/
OS_SEM GPS_SEM,SERVO_SEM,PC_SEM,ORDER_SEM,PC_Instruction_SEM;
int h=0,t=54,receive_cnt=0,calculate_cnt=0;
#define Rest_Position 1
#define Go_Up      2
#define Sit_down   3
#define Singing_Me 4
#define Dancing_Me 5
#define	Stop_Me    6
char *buf;

uint8_t m = 0x0a,PC_Instruction=0;
uint8_t SEND_PC[20]={0};
u8 SERVO_CurrentPosition[20][5]={{1,0X02,10,0X00,50},
                           {2,0X02,23,0X00,50},
													 {3,0X02,237,0X00,50},
												 	 {4,0X01,249,0X00,50},
													 {5,0X01,218,0X00,50},
													 {6,0X01,232,0X00,50},
													 {7,0X01,198,0X00,50},
													 {8,0X01,11,0X00,50},
													 {9,0X02,41,0X00,50},
													 {10,0X01,205,0X00,50},
													 {11,0X01,210,0X00,50},
													 {12,0X02,41,0X00,50},
													 {13,0X00,106,0X00,50},
													 {14,0X03,17,0X00,50},
													 {15,0X01,244,0X00,50},
													 {16,0X03,209,0X00,50},
													 {17,0X01,224,0X00,50},
                           {18,0X01,208,0X00,50},
													 {19,0X01,206,0X00,50}};//各个舵机的状态信息                           													 
u8 SERVO_ExpectPosition[20][5]={{1,0X02,10,0X00,50},
															 {2,0X02,23,0X00,50},
															 {3,0X02,237,0X00,50},
															 {4,0X01,249,0X00,50},
															 {5,0X01,218,0X00,50},
															 {6,0X01,232,0X00,50},
															 {7,0X01,198,0X00,50},
															 {8,0X01,11,0X00,50},
															 {9,0X02,41,0X00,50},
															 {10,0X01,205,0X00,50},
															 {11,0X01,210,0X00,50},
															 {12,0X02,41,0X00,50},
															 {13,0X00,106,0X00,50},
															 {14,0X03,17,0X00,50},
															 {15,0X01,244,0X00,50},
															 {16,0X03,209,0X00,50},
															 {17,0X01,224,0X00,50},
															 {18,0X01,208,0X00,50},
															 {19,0X01,206,0X00,50}};//各个舵机的状态信息
void Control_Servo(u8 ID,int angle,u8 point,u16 speed);
void Analysis_Servoangle(u8 *angledata);
/***************************/
u32 FLASH_SIZE;
const u8 TEXT_Buffer[]={"Apollo STM32F7 QSPI TEST"};
#define SIZE sizeof(TEXT_Buffer);

u8 *backbuf;								 
int main(void)
{
	  OS_ERR err;
	  CPU_SR_ALLOC();
	
	#if 1
		Write_Through();                //透写
		Cache_Enable();                 //打开L1-Cache
	  MPU_Memory_Protection();        //保护相关存储区域
		HAL_Init();				        //初始化HAL库
	  usmart_dev.init(108);		//初始化USMAR  
		Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
		delay_init(216);                //延时初始化
    MYDMA_Config(DMA1_Stream6,DMA_CHANNEL_4);//初始化DMA	
		LED_Init();
		SDRAM_Init();                   //初始化SDRAM
		uart_init();		        //串口初始化
	  MPU9250_Init();             	//初始化MPU9250
	  MY_ADC_Init();
   	W25QXX_Init();		            //初始化W25QXX
	  my_mem_init(SRAMIN);            //初始化内部内存池
    my_mem_init(SRAMEX);            //初始化外部SDRAM内存池
//    printf("Biped Robot Control System\n");
	 
		FLASH_SIZE=32*1024*1024;	//FLASH 大小为32M字节
	  while(W25QXX_ReadID()!=W25Q256)								//检测不到W25Q256
	{
		
		printf("QSPI Check Failed\n");
		delay_ms(200);
		printf("Please Check!\n");
		delay_ms(200);
		LED0_Toggle;		//DS0闪烁
	}
	while(mpu_dmp_init())         
    {   
			printf("MPU9250 Error\n");

		delay_ms(200);
 		
		LED0_Toggle;//DS0闪烁 
    }
//		printf("MPU9250 successful\n");
		 	while(FTL_Init())			    //检测NAND FLASH,并初始化FTL
	{
		printf("NAND Error!\n");
		delay_ms(500);				 
		printf("Please Check!\n");
		delay_ms(500);				 
		LED0_Toggle;//DS0闪烁
	}
	backbuf=mymalloc(SRAMIN,NAND_ECC_SECTOR_SIZE);	//申请一个扇区的缓存
	buf=mymalloc(SRAMIN,NAND_ECC_SECTOR_SIZE);		//申请一个扇区的缓存
	
#endif	  
#if servo_initialization
	  /*在设置舵机时，均采用广播ID 0XFE 所有舵机都能接受指令*/									
	  #endif

#if 1
	  OSInit(&err);		            //初始化UCOSIII
	  OS_CRITICAL_ENTER();//进入临界区
  	//创建开始任务
	  OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				         (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
		
	
								 
	  OS_CRITICAL_EXIT();	//退出临界区	 
	  OSStart(&err);      //开启UCOSIII
    while(1);
#endif
}
//开始任务任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u//统计任务  
   OSStatTaskCPUUsageInit(&err);  	              
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,设置默认的时间片长度
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	
	OS_CRITICAL_ENTER();	//进入临界区
	OSSemCreate ((OS_SEM *) &GPS_SEM,    //初始化信号量
                 (CPU_CHAR *)"GPS_SEM",
                 (OS_SEM_CTR )0,
                 (OS_ERR *) err);	
	OSSemCreate ((OS_SEM *) &SERVO_SEM,
                 (CPU_CHAR *)"SERVO_SEM",
                 (OS_SEM_CTR )0,
                 (OS_ERR *) err);		
	OSSemCreate ((OS_SEM *) &PC_SEM,    //来自Computer信息
                 (CPU_CHAR *)"PC_SEM",
                 (OS_SEM_CTR )0,
                 (OS_ERR *) err);	
	OSSemCreate ((OS_SEM *) &ORDER_SEM,    //得到舵机执行指令
                 (CPU_CHAR *)"ORDER_SEM",
                 (OS_SEM_CTR )0,
                 (OS_ERR *) err);		
	OSSemCreate ((OS_SEM *) &PC_Instruction_SEM,    //得到pc执行指令
                 (CPU_CHAR *)"PC_Instruction_SEM",
                 (OS_SEM_CTR )0,
                 (OS_ERR *) err);									 
	//创建TASK1任务
	OSTaskCreate   ((OS_TCB 	* )&GPS_TaskTCB,		
				         (CPU_CHAR	* )"GPS task", 		
                 (OS_TASK_PTR )GPS_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )GPS_TASK_PRIO,     
                 (CPU_STK   * )&GPS_TASK_STK[0],	
                 (CPU_STK_SIZE)GPS_STK_SIZE/10,	
                 (CPU_STK_SIZE)GPS_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
                 (OS_ERR 	* )&err);		
		//创建TASK2任务
	OSTaskCreate((OS_TCB 	* )&GYROSCOPE_TaskTCB,		
				       (CPU_CHAR	* )"Gyrocope_task", 		
                 (OS_TASK_PTR )GYROSCOPE_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )GYROSCOPE_TASK_PRIO,     	
                 (CPU_STK   * )&GYROSCOPE_TASK_STK[0],	
                 (CPU_STK_SIZE)GYROSCOPE_STK_SIZE/10,	
                 (CPU_STK_SIZE)GYROSCOPE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);	
	//创建SERVO read任务
		OSTaskCreate((OS_TCB 	* )&SERVO_TaskTCB,		
				         (CPU_CHAR	* )"Servo_task", 		
                 (OS_TASK_PTR )SERVO_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )SERVO_TASK_PRIO,     	
                 (CPU_STK   * )&SERVO_TASK_STK[0],	
                 (CPU_STK_SIZE)SERVO_STK_SIZE/10,	
                 (CPU_STK_SIZE)SERVO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);
	//创建servo_receive	
		OSTaskCreate((OS_TCB 	* )&SERVO_RECEIVE_TaskTCB,		
				         (CPU_CHAR	* )"SERVO_RECEIVE_TaskTCB", 		
                 (OS_TASK_PTR )SERVO_RECEIVE_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )SERVO_RECEIVE_TASK_PRIO,     	
                 (CPU_STK   * )&SERVO_RECEIVE_TASK_STK[0],	
                 (CPU_STK_SIZE)SERVO_RECEIVE_STK_SIZE/10,	
                 (CPU_STK_SIZE)SERVO_RECEIVE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);			
			//创建pc_receive	
		OSTaskCreate((OS_TCB 	* )&PC_RECEIVE_TaskTCB,		
				         (CPU_CHAR	* )"PC_RECEIVE_TaskTCB", 		
                 (OS_TASK_PTR )PC_RECEIVE_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )PC_RECEIVE_TASK_PRIO,     	
                 (CPU_STK   * )&PC_RECEIVE_TASK_STK[0],	
                 (CPU_STK_SIZE)PC_RECEIVE_STK_SIZE/10,	
                 (CPU_STK_SIZE)PC_RECEIVE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);

			//创建PC_Instruction_SEM	
		OSTaskCreate((OS_TCB 	* )&EXECUTION_INSTRUCTION_TaskTCB,		
				         (CPU_CHAR	* )"EXECUTION_INSTRUCTION_TaskTCB", 		
                 (OS_TASK_PTR )Execution_Instruction_Task, 			
                 (void		* )0,					
                 (OS_PRIO	  )EXECUTION_INSTRUCTION_TASK_PRIO,     	
                 (CPU_STK   * )&EXECUTION_INSTRUCTION_TASK_STK[0],	
                 (CPU_STK_SIZE)EXECUTION_INSTRUCTIONO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EXECUTION_INSTRUCTIONO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);




								 
//创建 power voltage collect				
		OSTaskCreate((OS_TCB 	* )&POWER_VOLTAGE_TaskTCB,		
				         (CPU_CHAR	* )"POWER_VOLTAGE_TaskTCB", 		
                 (OS_TASK_PTR )POWER_VOLTAGE_Task, 			
                 (void		* )0,					
                 (OS_PRIO	  )POWER_VOLTAGE_TASK_PRIO,     	
                 (CPU_STK   * )&POWER_VOLTAGE_TASK_STK[0],	
                 (CPU_STK_SIZE)POWER_VOLTAGE_STK_SIZE/10,	
                 (CPU_STK_SIZE)POWER_VOLTAGE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);
//创建 control servo to action				
		OSTaskCreate((OS_TCB 	* )&ORDER_SERVO_TaskTCB,		
				         (CPU_CHAR	* )"ORDER_SERVO_TaskTCB", 		
                 (OS_TASK_PTR )ORDER_SERVO_Task, 			
                 (void		* )0,					
                 (OS_PRIO	  )ORDER_SERVO_TASK_PRIO,     	
                 (CPU_STK   * )&ORDER_SERVO_TASK_STK[0],	
                 (CPU_STK_SIZE)ORDER_SERVO_STK_SIZE/10,	
                 (CPU_STK_SIZE)ORDER_SERVO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, 
                 (OS_ERR 	* )&err);										 
								 
	OS_CRITICAL_EXIT();	//退出临界区
	OSTaskDel((OS_TCB*)0,&err);	//删除start_task任务自身								 
	
}
void GPS_task(void *p_arg)  //  not use this task
{
 	char Jingdu[20],Weidu[20];
	OS_ERR err;
	CPU_TS ts;
	p_arg = p_arg;

	while(1)
	{
	  OSSemPend(&GPS_SEM,0,OS_OPT_PEND_BLOCKING,&ts,&err);//waits for a GPS semaphore		 
		     if(RxBuffer4[3]=='R'&& RxBuffer4[4]=='M'&&RxBuffer4[5]=='C') GPRMC_DAT();   //解析GPS GPRMC协议    
	  else if(RxBuffer4[3]=='G'&& RxBuffer4[4]=='S'&&RxBuffer4[5]=='V') GPGSV_DAT();   //解析GPS GPGSV协议   
	  else if(RxBuffer4[3]=='G'&& RxBuffer4[4]=='S'&&RxBuffer4[5]=='A') GPGSA_DAT();   //解析GPS GPGSA协议   
	  else if(RxBuffer4[3]=='G'&& RxBuffer4[4]=='G'&&RxBuffer4[5]=='A') GPGGA_DAT();   //解析GPS GPGGA协议 
		sprintf(Jingdu,"%.5f",jingdu);
		sprintf(Weidu,"%.5f",weidu);
//		LCD_ShowxNum(10,100,Year,2,16,0X80);
//		LCD_ShowxNum(30,100,Mouth,2,16,0X80);
//		LCD_ShowxNum(50,100,Day,2,16,0X80);
//    LCD_ShowxNum(70,100,Hour,2,16,0X80);
//		LCD_ShowxNum(90,100,Min,2,16,0X80);
//		LCD_ShowxNum(110,100,Sec,2,16,0X80);
//    LCD_ShowString(10,80,200,16,16,Jingdu);
//		LCD_ShowString(10,60,200,16,16,Weidu);		
//		LED0_Toggle; 
	}
}
void GYROSCOPE_task(void *p_arg)
{
		u8 t=0;	            //默认开启上报
		float pitch,roll,yaw,temper; 	        //欧拉角
		short aacx,aacy,aacz;	        //加速度传感器原始数据
		short gyrox,gyroy,gyroz;        //陀螺仪原始数据 
		short temp;		
  	OS_ERR err;
  	p_arg = p_arg;
    while(1)
	 {
		  OSSchedLock(&err);//上锁
	  if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
        {				
				  if((t%10)==0)
		  	{ 
					
          temp=MPU_Get_Temperature();	//得到温度值
		     	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
					MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
					temper=temp/100+(float)(temp%10)/10.0;
//				printf("GYROSCOPE&&temp:%.1f,pitch:%.1f,roll:%.1f,yaw:%.1f&&\n",temper,pitch,roll,yaw);		
         if((t%60)==0)
				 {					 
//					printf("%.1f %.1f %.1f  444\n",pitch,roll,yaw);	
					 t=0;
				 }					 
				}
         		}		
          t++;
			   OSSchedUnlock(&err);	//退出临界区	 
				 OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
				}		
}

void SERVO_task(void *p_arg)  //control servo
{
	int i;  
	OS_ERR err;
  p_arg = p_arg;
	while(1)
	{	
		for(i=1;i<=20;i++)
		{
			ReadServo_Position(i);
			OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_STRICT,&err);
		}
//		SYNC_Write_Buff(SERVO_ExpectPosition,18);
//    Write_Position(19,462,50,0);		
//		printf("nihao\n");
	  OSTimeDlyHMSM(0,0,0,350,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}
void SERVO_RECEIVE_task(void *p_arg)
{
	int ID,Length,ERROR,Check_Sum,i;
	CPU_TS ts;
	OS_ERR err;
  p_arg = p_arg;
	while(1)
	{
		 OSSemPend(&SERVO_SEM,0,OS_OPT_PEND_BLOCKING,&ts,&err);//waits for a SERVO semaphore	
  		OSSchedLock(&err);//上锁
     if(Receive_data[0]==0xff&&Receive_data[1]==0xff)
		 {
			 ID=Receive_data[2];                   
			 
			 Length=Receive_data[3];
			 ERROR=Receive_data[4];
			 if(Length==0x04&&ID<=20)  // 得出位置信息
			 {
				 SERVO_CurrentPosition[ID-1][1]=Receive_data[5];
				 SERVO_CurrentPosition[ID-1][2]=Receive_data[6];
				 //将数据整合成角度直接发给电脑
				 SEND_PC[ID-1]=(SERVO_CurrentPosition[ID-1][1]*256+SERVO_CurrentPosition[ID-1][2])/5.12;				 
			 }
			 if(ID==19)
			 {
//				 for(i=1;i<=20;i++)
//				 
//				 printf(" ID=%d, Position=%d,%d",i, SERVO_CurrentPosition[i-1][1], SERVO_CurrentPosition[i-1][2]);
//				 printf("\n");
				 printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d  10101\n",
		  SEND_PC[0],SEND_PC[1],SEND_PC[2],SEND_PC[3],SEND_PC[4],SEND_PC[5],SEND_PC[6],SEND_PC[7],SEND_PC[8],SEND_PC[9],SEND_PC[10],SEND_PC[11],SEND_PC[12],SEND_PC[13],SEND_PC[14],SEND_PC[15],SEND_PC[16],SEND_PC[17],SEND_PC[18],SEND_PC[19]);
				 
				 
				 
			 }
			 Check_Sum=0;
      
		 }
  	OSSchedUnlock(&err);//解锁			 
	}
}
void PC_RECEIVE_task(void *p_arg)
{
	char *Pc_Data;  //解析数据
	u8 key,i=0;
	CPU_TS ts;
	OS_ERR err;
  p_arg = p_arg;
  while(1)
	{
		 OSSemPend(&PC_SEM,0,OS_OPT_PEND_BLOCKING,&ts,&err);//waits for a SERVO semaphore			
		//进行解析
		if ( (Pc_Data = strstr ( Receive_PC_Data, "action" ) ) != 0 )//步态执行
		 {
			  Analysis_Servoangle(Receive_PC_Data);
		 }
		else if ( (Pc_Data = strstr ( Receive_PC_Data, "storage" ) ) != 0 )//接收步态存储数据
		 {
			  receive_cnt+=1;
        buf=Receive_PC_Data;
//			 将放入缓存的数据放到存放到机器人的flash中
        key=FTL_WriteSectors(buf,receive_cnt,NAND_ECC_SECTOR_SIZE,1);//写入扇区
     		if(key==0)printf("Write data successed\n");//写入成功
       	else      printf("Write data failed\n");//写入失败			    
			}
//		 		else if ( (Pc_Data = strstr ( Receive_PC_Data, "SitDown_storage" ) ) != 0 )//接收步态存储数据
//		 {
//			  calculate_cnt+=1;
//			  receive_cnt=100+calculate_cnt;
//        buf=Receive_PC_Data;
////			 将放入缓存的数据放到存放到机器人的flash中
//        key=FTL_WriteSectors(buf,receive_cnt,NAND_ECC_SECTOR_SIZE,1);//写入扇区
//     		if(key==0)printf("Write data successed\n");//写入成功
//       	else      printf("Write data failed\n");//写入失败			    
//			}
					else if ( (Pc_Data = strstr ( Receive_PC_Data, "HAHAHA" ) ) != 0 )//接收步态存储数据
		 {
			  receive_cnt+=1;
        buf=Receive_PC_Data;
//			 将放入缓存的数据放到存放到机器人的flash中
        key=FTL_WriteSectors(buf,receive_cnt+100,NAND_ECC_SECTOR_SIZE,1);//写入扇区
     		if(key==0)printf("Write data successed\n");//写入成功
       	else      printf("Write data failed\n");//写入失败			    
			}
		 else if ( (Pc_Data = strstr ( Receive_PC_Data, "STORAGE_OVER" ) ) != 0 )//接收将数据进行步态存储
		 {
//			 for(i=1;i<=receive_cnt;i++)
//			 {
//			    key=FTL_ReadSectors(buf,i+100,NAND_ECC_SECTOR_SIZE,1);//读取扇区	
//			 	  if(key==0)//读取成功
//				{
//					printf("success receive cnt=%d\n",i);
//					printf("%s",buf);//输出数据					
//				}
//				else printf("error receive"); 
//		 	}				 
       receive_cnt=0;
			 calculate_cnt=0;			 
		 }
			 	else if ( (Pc_Data = strstr ( Receive_PC_Data, "Rest_position" ) ) != 0 )//归位
		 {
			   SYNC_Write_Buff(Servo_State,20);	  //控制舵机
			  printf("OWO");
		 }	 
		    else if ( (Pc_Data = strstr ( Receive_PC_Data, "Go_up" ) ) != 0 )//前进
		 {			 		 
    		  for(i=1;i<101;i++)
			 {
			 	 key=FTL_ReadSectors(buf,i,NAND_ECC_SECTOR_SIZE,1);//读取扇区	
			 	  if(key==0)//读取成功
				{
//					printf("success receive cnt=%d\n",i);
//					printf("%s\n",buf);//输出数据	
					Analysis_Servoangle(buf);
					OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err); //延时100
				}			
			}
	   }
		    else if ( (Pc_Data = strstr ( Receive_PC_Data, "Sit_down" ) ) != 0 )//下蹲
		 {
    		  for(i=1;i<41;i++)
			 {
			 	 key=FTL_ReadSectors(buf,i+100,NAND_ECC_SECTOR_SIZE,1);//读取扇区	
			 	  if(key==0)//读取成功
				{
//					printf("success receive cnt=%d\n",i);
//					printf("%s\n",buf);//输出数据	
					Analysis_Servoangle(buf);
					OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err); //延时100
				}			
			}
		 }
		  else if ( (Pc_Data = strstr ( Receive_PC_Data, "Stand_up" ) ) != 0 )//下蹲
		 {
    		  for(i=1;i<41;i++)
			 {
			 	 key=FTL_ReadSectors(buf,141-i,NAND_ECC_SECTOR_SIZE,1);//读取扇区	
			 	  if(key==0)//读取成功
				{
//					printf("success receive cnt=%d\n",i);
//					printf("%s\n",buf);//输出数据	
					Analysis_Servoangle(buf);
					OSTimeDlyHMSM(0,0,0,90,OS_OPT_TIME_HMSM_STRICT,&err); //延时100
				}			
			}
		 }
		    else if ( (Pc_Data = strstr ( Receive_PC_Data, "Singing" ) ) != 0 )//唱歌
		 {
			 printf("I'm very well");
	 }			
		    else if ( (Pc_Data = strstr ( Receive_PC_Data, "Dancing" ) ) != 0 )//唱歌
		 {
      printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		  SEND_PC[0],SEND_PC[1],SEND_PC[2],SEND_PC[3],SEND_PC[4],SEND_PC[5],SEND_PC[6],SEND_PC[7],SEND_PC[8],SEND_PC[9],SEND_PC[10],SEND_PC[11],SEND_PC[12],SEND_PC[13],SEND_PC[14],SEND_PC[15],SEND_PC[16],SEND_PC[17],SEND_PC[18],SEND_PC[19],SEND_PC[20],SEND_PC[21],SEND_PC[22]);
		 }					 
		 		else if ( (Pc_Data = strstr ( Receive_PC_Data, "Stop" ) ) != 0 )//唱歌
		 {
      printf("nihao");
		 }
		 	else if ( (Pc_Data = strstr ( Receive_PC_Data, "WOLE" ) ) != 0 )//唱歌
		 {
       buf=Receive_PC_Data;
			 Analysis_Servoangle(buf);
		 }
		 else ;
			 
          


		 
 	 
	}
		
}
void Execution_Instruction_Task(void *p_arg)
{
	char *buff;
	u8 key,i=0,m=0;
	buff=&m;
	CPU_TS ts;
	OS_ERR err;
  p_arg = p_arg;
	
	  while(1)
	{
		
		 OSSemPend(&PC_Instruction_SEM,0,OS_OPT_PEND_BLOCKING,&ts,&err);//waits for a Instruction semaphore		
    
//		 switch(PC_Instruction)
//		 {
//			case Rest_Position:break;
//			case Go_Up: 
		
//       printf("王大锤\n");	
			for(i=1;i<21;i++)
			{
				printf("i=%d\n",i);
				//NAND_ECC_SECTOR_SIZE
	     key=FTL_ReadSectors(buff,i,50,1);//读取扇区
			if(key==0)
			{
				printf("Read data successed\n");//读取成功
				printf("%d",buff);
			}
      else      printf("Read data failed\n");//读取失败	
								
    Analysis_Servoangle(buff);
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时100
			}
//	
// 			
//			break;
//			case Sit_down:   break;		 
//			case Singing_Me: break;
//			case Dancing_Me: break;
//			case Stop_Me:    break;
//			default:         break;
//		 }	 
	}
}
void Analysis_Servoangle(u8 *angledata)  //PC SEND DATA TO ROBOT
{
	char *Pc_Data,point;  //解析数据
	char PC_DATA[6]={0};
	float angle[23]={0};
	char check_data[3]={0};
	char *checkdata=check_data;
	u8 i,j;
	OS_ERR err;
 
	for(i=0;i<20;i++)
  {
		 sprintf(checkdata,"A%d:",i+1);	
     //printf("%s",check_data);		
		 if ( (Pc_Data = strstr ( angledata,checkdata) ) != 0 )				 //将各个角度解析出来     数据固定为 XXX.XX
		 {
//			 printf("ok\n");
			 //取出数据
					 for(j=0;j<6;j++)
					 {
						 if(i<9)
						 PC_DATA[j]=*(Pc_Data+3+j);
						 else
						 PC_DATA[j]=*(Pc_Data+4+j); 
					 }						 
			 //将接收到的字符串转成float型     
				angle[i]=0;	
        if(PC_DATA[0] == '-'||PC_DATA[1] == '-')	
				  {point=-1;}
				else  {point=1;}					
				 if(PC_DATA[0] != ' '&&PC_DATA[0] != '-')	
						 angle[i]+=(PC_DATA[0]-'0')*100;							
				 if(PC_DATA[1] != ' '&&PC_DATA[1] != '-')	
						 angle[i]+=(PC_DATA[1]-'0')*10;
			//	 if(PC_DATA[2] != '-')	
						 angle[i]+=(PC_DATA[2]-'0');
			//	 if(PC_DATA[4] != '-')	
						 angle[i]+=(PC_DATA[4]-'0')/10.0;
			//	 if(PC_DATA[5] != '-')	
						 angle[i]+=(PC_DATA[5]-'0')/100.0;
//				 angle[i]*=point;
        switch(i+1)
				{	
					case 3:	if(angle[i]>=113) angle[i]=113;  break;
					case 8: if(angle[i]>=113) angle[i]=113;  break;					
					default: break;
				}					
			 //赋值给EXPECT_DATA中
			 Control_Servo(i+1,angle[i],point,50);//将数据传输过去	        			 
		 } 
	}
			  /*************发送舵机执行信号量********************/			
         OSSemPost(&ORDER_SEM,OS_OPT_POST_1,&err);//发送信号量				 //赋值给执行机构
}

void ORDER_SERVO_Task(void *p_arg)//控制舵机
{
	
	CPU_TS ts;
	OS_ERR err;
  p_arg = p_arg;
	while(1)
	{
		OSSemPend(&ORDER_SEM,0,OS_OPT_PEND_BLOCKING,&ts,&err);//waits for a SERVO semaphore
	 
//      printf("a3:%d\n",SERVO_ExpectPosition[2][2]);
//			printf("a4:%d\n",SERVO_ExpectPosition[3][2]);
		  SYNC_Write_Buff(SERVO_ExpectPosition,20);	  //控制舵机
		//发送数据                                                             
	}
}

void POWER_VOLTAGE_Task(void *p_arg)
{
	  int i=0;
	  float voltage=0;
	  OS_ERR err;
  	p_arg = p_arg;
	   while(1)
		 {	
      OSSchedLock(&err);//上锁				 
  	  voltage+=Get_Adc(ADC_CHANNEL_4);
			OSSchedUnlock(&err);//解锁     
	    i++;	 	  	
	  if(i==20)
		{
//			voltage=voltage*3.3/4096/20*10/1.5;
			voltage=voltage*33/122880;
//			printf("%.1f 333\n",voltage);
			voltage=0;
			i=0;
		}		
	  OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
	}
	  
}
void Control_Servo(u8 ID,int angle,u8 point,u16 time)
{
	u8 i;
	int  number;
	i=ID-1;
	 	
	if(ID==7||ID==4)
	{
	  if(point==1)
			point=0;
		else
			point=1;
	}
	/****************/
	if(ID==3) point=0;
	if(ID==8) point=1;
	/****************/
	number=Together_Number(&Servo_State[i][1],&Servo_State[i][2]);//取出标准数据来
	if (point==1)//前倾
	number=number+(int)(angle*5.12);
	else
	number=number-(int)(angle*5.12);	
	Split_Number(&SERVO_ExpectPosition[i][1],&SERVO_ExpectPosition[i][2], number);
	Split_Number(&SERVO_ExpectPosition[i][3],&SERVO_ExpectPosition[i][4], time);
}
