d1=100;
a2=165;a3=165;
angle1_max=360;
angle1_min=0;
angle2_max=180;
angle2_min=0;
angle3_max=90;
angle3_min=-90;
angle1=angle1_min+(angle1_max-angle1_min)*rand(20000,1);
angle2=angle2_min+(angle2_max-angle2_min)*rand(20000,1);
angle3=angle3_min+(angle3_max-angle3_min)*rand(20000,1);

angle1=angle1';
angle2=angle2';
angle3=angle3';
i=1;
k=angle1;
m=angle2;
n=angle3;
for o=angle1
px=cosd(k(i))*(cosd(m(i))*a2 + cosd(m(i))*cosd(n(i))*a3 - sind(m(i))* sind(n(i))*a3);
py=sind(k(i))*(cosd(m(i))*a2 + cosd(m(i))*cosd(n(i))*a3 - sind(m(i))* sind(n(i))*a3);
pz=d1+a2*sind(m(i))+a3*(sind(m(i))*cosd(n(i))+cosd(m(i))*sind(n(i)));
%plot3(px,py,pz,'*');
plot(px,pz,'.');

hold on;
i=i+1;
end
xlabel('x/cm');
ylabel('z/cm');
%zlabel('z/cm');
 