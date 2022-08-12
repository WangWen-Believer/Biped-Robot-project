syms nx ny nz ox oy oz ax ay az px py pz
syms C1 S1 a1 C2 S2 a2
T_H=[ nx ox ax px;
      ny oy ay py;
      nz oz az pz;
      0   0  0  1;
    ];
A1=[ C1 -S1 0 a1*C1
     S1  C1 0 a1*S1
     0   0  1   0
     0   0  0   1
    ];
A2=[ C2 -S2 0 a2*C2
     S2  C2 0 a2*S2
     0   0  1   0
     0   0  0   1
    ];
T_H*inv(A2)
A1*A2;

