function [c0,c1,c2,c3 ] = orbit_function( t,start,last )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
c0=start;c1=0;height=last;
A=[ t^2 , t^3;
    2*t , 3*t^2;
   ];
B=[ height-c0-c1*2;
    -c1;
    ];
X=A\B;
c2=X(1,1);
c3=X(2,1);
end

