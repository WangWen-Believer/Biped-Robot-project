#include "robotdata.h"
u8 Robot_angle[17][20]={0}; //robot在执行一套动作所需要的角度
u8 SERVO_ExpectPosition[17][7]={{1,1,237,0X01,0Xf4,0X00,0X00},
                             {2,2,8,0X01,0Xf4,0X00,0X00},
													 {3,2,233,0X01,0Xf4,0X00,0X00},
												 	 {4,2,002,0X01,0Xf4,0X00,0X00},
													 {5,1,202,0X01,0Xf4,0X00,0X00},
													 {6,1,226,0X01,0Xf4,0X00,0X00},
													 {7,1,213,0X01,0Xf4,0X00,0X00},
											 		 {8,1,13,0X01,0Xf4,0X00,0X00},
													 {9,2,31,0X01,0Xf4,0X00,0X00},
											  		{10,1,246,0X01,0Xf4,0X00,0X00},
													 {11,0X01,0Xe0,0X00,0X00,0X02,0X00},
													 {12,0X02,0X10,0X00,0X00,0X02,0X00},
													 {13,0X03,0X3a,0X00,0X00,0X02,0X00},
													 {14,0X02,0X9a,0X00,0X00,0X02,0X00},
													 {15,0X01,0XCF,0X00,0X00,0X02,0X00},
													 {16,0X00,0X60,0X00,0X00,0X02,0X00},
													 {17,0X01,0X60,0X00,0X00,0X02,0X00}};//各个舵机的状态信息
