%DISPLAY Display the value of a quaternion object

% $Log: display.m,v $
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function display(q)

	disp(' ');
	disp([inputname(1), ' = '])
	disp(' ');
	disp(['  ' char(q)])
	disp(' ');
