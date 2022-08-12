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
Lenght=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
l1=75.326;l2=72;Zmax=l1+l2;
a_max=55;b_max=115;c_max=90;%关节最大角度 
T=2;%踏步周期2s
t=linspace(0,T,20);
w=2*pi/T;%角速度
Y=5*sin(2*pi/T*t);% 中心点位移 




time=1;%下蹲所需时间
[c0,c1,c2,c3]=orbit_function(time,5,5);%轨迹规划参数
t=linspace(0,time,20);
height=147.3-(c0+c1*t+c2*t.^2+c3*t.^3);
[a0,a1,a2,a3]=orbit_function(time,0,20);%轨迹规划参数
width=a0+a1*t+a2*t.^2+a3*t.^3;
plot(t,height,t,width);
title('Robot Trajectory Planning' )
xlabel('t');
ylabel('lenght')
hold on
%[x,y]=solve('l1*sin(x)-l2*sin(y)=0','l1*cos(x)+l2*cos(y)=height','x','y')
%公式就是求出     l1*sin(x)-l2*sin(y)=0
%                l1*cos(x)+l2*cos(y)=height    height是个数组
%求出随着height的变化求出  关节角 x y的角度
%******************************************************************************************%
%对坐标进行三维求解
syms u lenght
for i=1:20
 %求解二元一次方程组
eqns=[lenght*sin(u)==width(1,i),lenght*cos(u)==height(1,i)];
vars=[lenght,u] ;
[solt,solu]=solve(eqns,vars);
Lenght(1,i)=abs(vpa(solt(1,1),2));%长度
Lenght(1,i)=roundn(Lenght(1,i),-1);
SD_1(1,i)=abs(vpa(solu(1,1)*180/pi,2));
SD_1(1,i)=roundn(SD_1(1,i),-1);
SD_5(1,i)=SD_1(1,i);
SD_6(1,i)=SD_1(1,i);
SD_10(1,i)=SD_1(1,i);
end
syms x y
for i=1:20
eqns=[l1*sin(x)-l2*sin(y)==5,l1*cos(x)+l2*cos(y)==Lenght(1,i)];
vars=[x y];
[solx,soly]=solve(eqns,vars);
SD_2(1,i)=abs(vpa(solx(2,1)*180/pi,2));
SD_4(1,i)=abs(vpa(soly(2,1)*180/pi,2));
SD_2(1,i)=roundn(SD_2(1,i),-1)+3;
SD_4(1,i)=roundn(SD_4(1,i),-1);

SD_3(1,i)=SD_2(1,i)+SD_4(1,i);

SD_7(1,i)=SD_2(1,i);
SD_8(1,i)=SD_3(1,i);
SD_9(1,i)=SD_4(1,i);
end
USART.PropertyValue=128000;
obj=serial(USART.port,USART.PropertyName,USART.PropertyValue);
USART.port='COM4';
USART.PropertyName='BaudRate';