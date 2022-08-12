%MPOWER Raise quaternion to integer power
%
% Compound the quaternion with itself.  Invoked by means of the caret
% operator.

% $Log: mpower.m,v $
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function qp = mpower(q, p)

	% check that exponent is an integer
	if (p - floor(p)) ~= 0,
		error('quaternion exponent must be integer');
	end

	qp = q;

	% multiply by itself so many times
	for i = 2:abs(p),
		qp = qp * q;
	end

	% if exponent was negative, invert it
	if p<0,
		qp = inv(qp);
	end
