function [ back] = stay_here( usart,angle_1,angle_2,angle_3,angle_4,angle_5,angle_6,angle_7,angle_8,angle_9,angle_10,angle_11,angle_12,angle_13,angle_14,angle_15,angle_16,angle_17,angle_18,angle_19,angle_20)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
%1s完成下蹲的动作
back=0;SEND=0;
Send_Data='action:A1:%6.2f,A2:%6.2f,A3:%6.2f,A4:%6.2f,A5:%6.2f,A6:%6.2f,A7:%6.2f,A8:%6.2f,A9:%6.2f,A10:%6.2f,A11:%6.2f,A12:%6.2f,A13:%6.2f,A14:%6.2f,A15:%6.2f,A16:%6.2f,A17:%6.2f,A18:%6.2f,A19:%6.2f,A20:%6.2f&&\n';
%发送数据
for j=1:16
for i=11:90
    SEND=sprintf(Send_Data,angle_1(1,i),angle_2(1,i),angle_3(1,i),angle_4(1,i),angle_5(1,i),angle_6(1,i),angle_7(1,i),angle_8(1,i),angle_9(1,i),angle_10(1,i),angle_11(1,i),angle_12(1,i),angle_13(1,i),angle_14(1,i),angle_15(1,i),angle_16(1,i),angle_17(1,i),angle_18(1,i),angle_19(1,i),angle_20(1,i));
    USART_Send(usart,SEND);
    pause(0.003);
end
end

end 

