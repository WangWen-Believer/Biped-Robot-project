l1=75.326;l2=72;Zmax=l1+l2;
a_max=55;b_max=115;c_max=9;%关节最大角度 
time=2;%下蹲所需时间
[c0,c1,c2,c3]=orbit_function(time,145,95);%轨迹规划参数
t=linspace(0,time,20);
height=c0+c1*t+c2*t.^2+c3*t.^3;
[a0,a1,a2,a3]=orbit_function(time,0,20);%轨迹规划参数
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

h=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
n=[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
for i=1:20
 syms x y
eqns=[l1*sin(x)-l2*sin(y)==width(1,i),l1*cos(x)+l2*cos(y)==height(1,i)];
vars=[x y];
[solx,soly]=solve(eqns,vars);
h(1,i)=solx(2,1)*180/pi;
n(1,i)=soly(2,1)*180/pi+h(1,i);
if solx(1,1)*180/pi>0
h(1,i)=solx(1,1)*180/pi;
n(1,i)=soly(1,1)*180/pi+h(1,i);
end

end
plot(t,h)
plot(t,n,'--')
legend('height','width','angle_1','angle_2')
