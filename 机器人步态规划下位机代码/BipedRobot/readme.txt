实验器材:
	阿波罗STM32F7开发板
	
实验目的:
	学习UCOSIII的任务创建和删除
	
硬件资源:
	1,DS0(连接在PB1)，DS1(连接在PB0上)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面) 
	3,ALIENTEK 2.8/3.5/4.3/7寸LCD模块(包括MCU屏和RGB屏,都支持) 	
	
实验现象:
	本实验中任务start_task创建了另外两个任务task1_task和task2_task。task1_task在运行5次以后就会
	删除掉task2_task，通过这两个任务来演示UCOSIII的任务创建和删除。
	
注意事项:
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在lcd.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!  

	 

					正点原子@ALIENTEK
					2016-6-26
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com
