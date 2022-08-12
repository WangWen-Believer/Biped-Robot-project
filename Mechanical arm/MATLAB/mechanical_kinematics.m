syms C1 S1 C2 S2 C3 S3   %representjoint angle's sin cos
syms d1  a2 a3
syms px  py  pz nx ny nz ox oy oz ax ay az
syms angle_1 angle_2 angle_3
%transform 
%**********************
%px=-1;py=-1;
%angle_1=atan(px/py)/pi*180;
%if px<0||py<0
%    angle_1=angle_1+180;
%end
%************************
A1=[ C1 0  S1 0
     S1 0 -C1 0
      0 1  0  d1
      0 0  0  1  ];
A2=[ C2 -S2  0  a2*C2
     S2  C2  0  a2*S2
      0   0  1    0
      0   0  0    1 ];
A3=[ C3 -S3  0  a3*C3
     S3  C3  0  a3*S3
      0   0  1    0
      0   0  0    1 ];
A1*A2*A3;
TH=[ nx ox ax px
     ny oy ay py
     nz oz az pz
     0   0  0  1];

 A4=inv(A1)*TH; %通过与A1*A2进行比较得出angle_1的公式
 A2*A3;
 
 