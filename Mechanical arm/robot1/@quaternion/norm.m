%NORM Compute the norm of a quaternion
%
%	QN = norm(Q)
%
% Return a unit-quaternion corresponding to the quaternion Q.
%

% $Log: norm.m,v $
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1993-2002, by Peter I. Corke

function n = norm(q)

	n = norm(double(q));

