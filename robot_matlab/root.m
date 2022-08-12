function F=root(x)
%ROOT Summary of this function goes here
%   Detailed explanation goes here
l1=75.326;l2=72;height=10;
%F(1) = l1*sin(x)-l2*sin(y);
F(1) = l1*cos(x)+l2*cos(y)-height;
%F(1) = exp(-exp(-(x(1)+x(2)))) - x(2)*(1+x(1)^2);
%F(2) = x(1)*cos(x(2)) + x(2)*sin(x(1)) - 0.5;
end

