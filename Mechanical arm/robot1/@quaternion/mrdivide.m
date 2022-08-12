%MRDIVIDE Compute quaternion quotient.
%
% Invoked on the / operator, handle two cases:
% q1/q2  	multiply one quaternion by inverse of the second.
% q1/s		result is non-unit quaternion, all elements divided by s

% $Log: mrdivide.m,v $
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function qq = mrdivide(q1, q2)

	if isa(q2, 'quaternion'),
		% qq = q1 / q2
		%    = q1 * qinv(q2)

		qq = q1 * inv(q2);
	elseif isa(q2, 'double'),
		qq = quaternion( double(q1) / q2 );
	end
