l1=75.326;l2=72;Zmax=l1+l2;
a_max=55;b_max=115;c_max=90;%关节最大角度 
time=1;%下蹲所需时间
[c0,c1,c2,c3]=orbit_function(time,0,40);%轨迹规划参数
t=linspace(0,time,20);
height=147.3-(c0+c1*t+c2*t.^2+c3*t.^3);
[a0,a1,a2,a3]=orbit_function(time,0,0);%轨迹规划参数
width=a0+a1*t+a2*t.^2+a3*t.^3;
plot(t,height,t,width);

title('Robot Trajectory Planning' )
xlabel('t');
ylabel('height')
hold on
%[x,y]=solve('l1*sin(x)-l2*sin(y)=0','l1*cos(x)+l2*cos(y)=height','x','y')
%公式就是求出     l1*sin(x)-l2*sin(y)=0
%                l1*cos(x)+l2*cos(y)=height    height是个数组
%求出随着height的变化求出  关节角 x y的角度

SD_1=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_2=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_3=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_4=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_5=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_6=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_7=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_8=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_10=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_11=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_12=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_13=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_14=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_15=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_16=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_17=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_18=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_19=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
SD_20=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
for i=1:40
 syms x y
if i<21
 %求解二元一次方程组
eqns=[l1*sin(x)-l2*sin(y)==0,l1*cos(x)+l2*cos(y)==height(1,i)];
vars=[x y];
[solx,soly]=solve(eqns,vars);
%将解转换成角度   SD->Sit Down
SD_2(1,i)=abs(vpa(solx(2,1)*180/pi,2));
SD_4(1,i)=abs(vpa(soly(2,1)*180/pi,2));
SD_2(1,i)=roundn(SD_2(1,i),-1)+3;
SD_4(1,i)=roundn(SD_4(1,i),-1);

SD_3(1,i)=SD_2(1,i)+SD_4(1,i);
SD_7(1,i)=SD_2(1,i)+3;
SD_8(1,i)=SD_3(1,i);
SD_4(1,i)=SD_4(1,i)+3;
SD_9(1,i)=SD_4(1,i);
end
 if i==20
   [d0,d1,d2,d3]=orbit_function(time,SD_3(1,20),110);%轨迹规划参数 
   D=d0+d1*t+d2*t.^2+d3*t.^3;
   [c0,c1,c2,c3]=orbit_function(time,SD_4(1,20),86.5);%轨迹规划参数 
   C=c0+c1*t+c2*t.^2+c3*t.^3;
 end 
 if (i>20)
   SD_3(1,i)=D(1,i-20); 
   SD_8(1,i)=SD_3(1,i);
   SD_4(1,i)=C(1,i-20); 
   SD_9(1,i)=SD_4(1,i);
   SD_2(1,i)=SD_2(1,20);
   SD_7(1,i)=SD_2(1,20);
   
 end 
end
%*********************************%
time=2;
t=linspace(0,time,40);
plot(t,SD_2)


plot(t,SD_3,'--')
plot(t,SD_4,'.')
legend('height','width','SD_2','SD_3','SD_4')
%******************************************%
%define serial port
%send data to stm32 by serial port
% USART.port='COM11';
% USART.PropertyName='BaudRate';
% USART.PropertyValue=128000;
% obj=serial(USART.port,USART.PropertyName,USART.PropertyValue);
%fopen(obj);
%fclose(obj);
%delete(obj);
%*****************************************%

