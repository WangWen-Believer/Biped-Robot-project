%PLOT Plot a quaternion object 
%
%	PLOT(Q)
%
% Display the quaternion as a rotated coordinate frame.
%
% SEE ALSO: QUATERNION

% $Log: plot.m,v $
% Revision 1.3  2002/04/14 11:02:54  pic
% Changed see also line.
%
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.3 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function plot(Q)
	axis([-1 1 -1 1 -1 1])

	% create unit vectors
	o = [0 0 0]';
	x1 = Q*[1 0 0]';
	y1 = Q*[0 1 0]';
	z1 = Q*[0 0 1]';

	hold on
	plot3([0;x1(1)], [0; x1(2)], [0; x1(3)])
	text(x1(1), x1(2), x1(3), 'X')
	plot3([0;y1(1)], [0; y1(2)], [0; y1(3)])
	text(y1(1), y1(2), y1(3), 'Y')
	plot3([0;z1(1)], [0; z1(2)], [0; z1(3)])
	text(z1(1), z1(2), z1(3), 'Z')
	grid on
	xlabel('X')
	ylabel('Y')
	zlabel('Z')
	hold off
