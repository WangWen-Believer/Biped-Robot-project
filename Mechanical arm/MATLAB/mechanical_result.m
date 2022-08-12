syms C1 S1 C2 S2 C3 S3   %representjoint angle's sin cos
syms d1  a2 a3
syms px  py  pz nx ny nz ox oy oz ax ay az
syms angle_1 angle_2 angle_3
%transform 
a=1;
if a==1
   d1=100;a2=165;a3=165; 
   px=100;py=100;pz=173;
   angle_1=atan(px/py)/pi*180;
   if px<0||py<0
    angle_1=angle_1+180;
   end
   C1=cos(angle_1);S1=sin(angle_1);
end
C3=((C1*px+S1*py)^2+(pz-d1)^2-a2^2-a3^2)/(2*a2*a3);
S3=sqrt(1-C3^2);
angle_3=atan(S3/C3)/pi*180
C3=cos(angle_3);S3=sin(angle_3);

C2=(C1*a2*px-S3*a3*d1+S1*a2*py+S3*a3*pz+C1*C3*a3*px+C3*S1*a3*py)/(C3^2*a3^2+2*C3*a2*a3+S3^2*a3^2+a2^2);
S2=-(a2*d1-a2*pz+C3*a3*d1-C3*a3*pz+C1*S3*a3*px+S1*S3*a3*py)/(C3^2*a3^2+2*C3*a2*a3+S3^2*a3^2+a2^2);
angle_2=atan(S2/C2)/pi*180;
