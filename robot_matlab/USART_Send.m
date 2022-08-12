function [ back ] = USART_Send( usart,Data_1 )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
back='send complete';
%fopen(obj);

fwrite(usart,Data_1);

%fclose(obj);
end

