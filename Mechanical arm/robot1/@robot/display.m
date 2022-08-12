%DISPLAY Display a robot object

% $Log: display.m,v $
% Revision 1.2  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
% Copyright (C) 1999-2002, by Peter I. Corke

function display(r)
	disp(' ');
	disp([inputname(1), ' = '])
	disp(' ');
	disp(char(r))
	disp(' ');
