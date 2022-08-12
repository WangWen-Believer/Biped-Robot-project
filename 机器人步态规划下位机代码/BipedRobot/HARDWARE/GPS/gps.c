#include "gps.h"
#include "sys.h"
extern uint8_t RxBuffer4[400]; 
extern uint8_t Rec_Len;
uint8_t Hour,Min,Sec,Day,Mouth,Year,GPS_VA,weidu_dir,jingdu_dir,star_num,star_num_t,star_run[12],GPS_3D;
float jingdu,weidu;
u16 star_info[12][4],star_info_t[12][4],GPS_ATLI;
void GPRMC_DAT(void);
void GPGSV_DAT(void);
void GPGSA_DAT(void);
void GPGGA_DAT(void);
/****************************************************************************
* 名    称：void GPRMC_DAT(void)
* 功    能：GPS NMEA GPRMC协议解析
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void GPRMC_DAT(void){	
   unsigned char i,i1=0,uf=0;
   float l_g;
		
   for(i=0;i<Rec_Len;i++){
   	  if(RxBuffer4[i]==0x2c){				                         //判断是否是逗号
	  	i1++;
		  uf=0;
	  }	 
	  if(i1==1&&uf==0){	                                             //GPRMC 时间
	  	Hour=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30)+8;		 //时
   	  Min=(RxBuffer4[i+3]-0x30)*10+(RxBuffer4[i+4]-0x30);		     //分
      Sec=(RxBuffer4[i+5]-0x30)*10+(RxBuffer4[i+6]-0x30);		     //秒 
		  i=i+6;		
		  uf=1;	
   	  }	
	  else if(i1==2&&uf==0){	                                     //GPRMC 状态有效性
	  	if(RxBuffer4[i+1]=='A')	GPS_VA=1; 		                     //成功定位
		  else GPS_VA=0;												 //定位未成功
		i++;	
		uf=1;
   	  }	
	  else if(i1==3&&uf==0){	                                     //GPRMC 纬度
	  	if(RxBuffer4[i+1]==0x2c) weidu=0;
	  	else {
//			weidu=((RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30)+	 //计算出纬度值的整数部分
//			       (((((RxBuffer4[i+3]-0x30)*10)+(RxBuffer4[i+4]-0x30))/0.6)*0.01))*3600;
        weidu=(RxBuffer4[i+1]-0x30)*1000+(RxBuffer4[i+2]-0x30)*100+(RxBuffer4[i+3]-0x30)*10+(RxBuffer4[i+4]-0x30);
//			l_g=(((RxBuffer4[i+6]-0x30)*1000)+((RxBuffer4[i+7]-0x30)*100)+     //计算出纬度值的小数部分
//			     ((RxBuffer4[i+8]-0x30)*10)+(RxBuffer4[i+9]-0x30))*0.006;
l_g=(((RxBuffer4[i+6]-0x30)*10000)+((RxBuffer4[i+7]-0x30)*1000)+     //计算出纬度值的小数部分
			     ((RxBuffer4[i+8]-0x30)*100)+(RxBuffer4[i+9]-0x30)*10+(RxBuffer4[i+10]-0x30))/100000.0;
	    	weidu=weidu+l_g;                						 //最终的纬度值 例如34.xxxx
			i=i+9;
		}
		uf=1;	
	  }
	  else if(i1==4&&uf==0){	                                     //GPRMC 纬度	南北半球标示 
	  	if(RxBuffer4[i+1]==0x2c) jingdu_dir=0;
		else if(RxBuffer4[i+1]=='N') weidu_dir=0;                    //北纬
		else if(RxBuffer4[i+1]=='S') weidu_dir=1;                    //南纬
		i++; 
		uf=1;	
	  } 			
	  else if(i1==5&&uf==0){	                                     //GPRMC 经度
	  	if(RxBuffer4[i+1]==0x2c) jingdu=0; 
		else{
//			jingdu=((RxBuffer4[i+1]-0x30)*100+(RxBuffer4[i+2]-0x30)*10+	   //计算出经度值的整数部分
//			(RxBuffer4[i+3]-0x30)+(((((RxBuffer4[i+4]-0x30)*10)+(RxBuffer4[i+5]-0x30))/0.6)*0.01))*3600;
//			l_g=(((RxBuffer4[i+7]-0x30)*1000)+((RxBuffer4[i+8]-0x30)*100)+  //计算出经度值的小数部分 
//			    ((RxBuffer4[i+9]-0x30)*10)+(RxBuffer4[i+10]-0x30))*0.006;
    jingdu=((RxBuffer4[i+1]-0x30)*10000+(RxBuffer4[i+2]-0x30)*1000+	   //计算出经度值的整数部分
			(RxBuffer4[i+3]-0x30)*100+(RxBuffer4[i+4]-0x30)*10)+(RxBuffer4[i+5]-0x30);
			l_g=(((RxBuffer4[i+7]-0x30)*10000)+((RxBuffer4[i+8]-0x30)*1000)+  //计算出经度值的小数部分 
			    ((RxBuffer4[i+9]-0x30)*100)+(RxBuffer4[i+10]-0x30)*10+(RxBuffer4[i+10]-0x30))/100000.0;
	    	jingdu=jingdu+l_g;              								//最终的经度值 例如107.xxxx
			i=i+10;
		}
		uf=1;	
	  }
	  else if(i1==6&&uf==0){	                                     //GPRMC 经度	东西半球 
	  	if(RxBuffer4[i+1]==0x2c) jingdu_dir=0;
		else if(RxBuffer4[i+1]=='E') jingdu_dir=0;                   //东经
		else if(RxBuffer4[i+1]=='W') jingdu_dir=1;                   //西经
		i++; 
		uf=1;	
	  } 
	  else if(i1==7&&uf==0){	                                     //GPRMC 地面速度  
	  	uf=1;	
	  }
	  else if(i1==8&&uf==0){	                                     //GPRMC 速度方向 
	  	uf=1;	
	  }
	  else if(i1==9&&uf==0){	                                     //GPRMC 日期
	  	Day=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30);			 //日
   		Mouth=(RxBuffer4[i+3]-0x30)*10+(RxBuffer4[i+4]-0x30);		 //月
   		Year=(RxBuffer4[i+5]-0x30)*10+(RxBuffer4[i+6]-0x30);		 //年		
		i=i+6;
		uf=1;	
   	  }	
   }																 
}							
/****************************************************************************
* 名    称：void GPGSV_DAT(void)
* 功    能：GPS NMEA GPGSV协议解析
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void GPGSV_DAT(void){	
   unsigned char i,i1=0,no=0,uf=0,gsv_no=0;  
   for(i=0;i<Rec_Len;i++){
   	  if(RxBuffer4[i]==0x2c){
	  	i1++;
		uf=0;
	  }	 
	  if(i1==1&&uf==0){	                                         //GPGSV语句数   	      
		uf=1;	
   	  }	
	  else if(i1==2&&uf==0){	                                 //GPGSV 语句号 0-2
	    gsv_no=RxBuffer4[i+1]-0x31;
		i++;		
		uf=1;	
   	  }	
	  else if(i1==3&&uf==0){	                                 //卫星数
	  	star_num=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30);
		i=i+2;	
		uf=1;	
   	  }	
	  else if((i1==4||i1==8||i1==12||i1==16)&&uf==0){	          //卫星 序号 	   00-32
	  	no=i1/4;
		if(RxBuffer4[i+1]==0x2c||RxBuffer4[i+1]=='*') star_info[(no-1)+gsv_no*4][0]=0xff;  //无序号
		else star_info[(no-1)+gsv_no*4][0]=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30); //序号值  
		//i++;
		uf=1;	
	  }
	  else if((i1==5||i1==9||i1==13||i1==17)&&uf==0){	          //卫星 序号  仰角	00-90
	  	if(RxBuffer4[i+1]==0x2c||RxBuffer4[i+1]=='*') star_info[(no-1)+gsv_no*4][1]=0xff;  //无仰角
		else star_info[(no-1)+gsv_no*4][1]=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30); //有效的仰角值 
		uf=1;	
	  }															   
	  else if((i1==6||i1==10||i1==14||i1==18)&&uf==0){	          //卫星 序号  方位角	00-359
	  	if(RxBuffer4[i+1]==0x2c||RxBuffer4[i+1]=='*') star_info[(no-1)+gsv_no*4][2]=0xff;    //无方位角
		else star_info[(no-1)+gsv_no*4][2]=(RxBuffer4[i+1]-0x30)*100+			 //有效的方位角值
			 (RxBuffer4[i+2]-0x30)*10+(RxBuffer4[i+3]-0x30); 
		uf=1;	
	  }	
	  else if((i1==7||i1==11||i1==15||i1==19)&&uf==0){	          //卫星 序号 信号强度	00-99
	  	if(RxBuffer4[i+1]==0x2c||RxBuffer4[i+1]=='*') star_info[(no-1)+gsv_no*4][3]=0xff;  //无信号强度
		else star_info[(no-1)+gsv_no*4][3]=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30); //有效的信号强度
		uf=1;	
	  }	  
   }      
}	   

/****************************************************************************
* 名    称：void GPGSA_DAT(void)
* 功    能：GPS NMEA GPGSA协议解析
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void GPGSA_DAT(void){	
   unsigned char i,i1=0,uf=0;  
   for(i=0;i<Rec_Len;i++){
   	  if(RxBuffer4[i]==0x2c){				    //协议里的数据间隔符-逗号
	  	i1++;
		uf=0;
	  }	 
	  if(i1==1&&uf==0){	                        //GPGSA 模式 ：M = 手动， A = 自动。   	      
		uf=1;	
   	  }	
	  else if(i1==2&&uf==0){	                //定位型式 1 = 未定位， 2 = 二维定位， 3 = 三维定位。
	    GPS_3D=RxBuffer4[i+1]-0x30;
		i++;		
		uf=1;	
   	  }	
	  else if((i1==3||i1==4||i1==5||i1==6||i1==7||i1==8||i1==9||i1==10||i1==11||i1==12||i1==13||i1==14)&&uf==0){ //有效信号的卫星编号
	  	if(RxBuffer4[i+1]==0x2c) star_run[i1-3]=0x2c;
		else star_run[i1-3]=(RxBuffer4[i+1]-0x30)*10+(RxBuffer4[i+2]-0x30);
		i=i+2;	
		uf=1;	
   	  }		  
   }	  
}

/****************************************************************************
* 名    称：void GPGGA_DAT(void)
* 功    能：GPS NMEA GPGGA协议解析
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void GPGGA_DAT(void){	
   unsigned char i,i1=0,uf=0;  
   for(i=0;i<Rec_Len;i++){
   	  if(RxBuffer4[i]==0x2c){					//协议里的数据间隔符-逗号
	  	i1++;
		uf=0;
	  }	 
	  if(i1==1&&uf==0){	                          	      
		uf=1;	
   	  }	
	  else if(i1==9&&uf==0){	                //GPS 测量的海拔高度
	    if(RxBuffer4[i+1]==0x2c) GPS_ATLI=0;	//如果此处是逗号。标示无效
	    else GPS_ATLI=atoi(&RxBuffer4[i+1]);	//海拔值	
		  uf=1;	
   	  }	 
   }	  
}

