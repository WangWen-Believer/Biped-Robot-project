%TRINTERP Interpolate homogeneous transformations
%
%	TR = TRINTERP(T0, T1, R)
%
% Returns a homogeneous transform interpolation between T0 and T1 as
% R varies from 0 to 1.  Rotation is interpolated using quaternion
% spherical linear interpolation.
%
% See also: CTRAJ, QINTERP

% Copyright (C) 1993-2002, by Peter I. Corke

% MOD.HISTORY
% 12/94	must have T0 as well as DP
% 3/96	fixed bug: sin/cos(dp(4)) should be of dp(6)
% $Log: trinterp.m,v $
% Revision 1.2  2002/04/01 11:47:19  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

function t = trinterp(T0, T1, r)

	q0 = quaternion(T0);
	q1 = quaternion(T1);

	p0 = transl(T0);
	p1 = transl(T1);

	qr = qinterp(q0, q1, r);
	pr = p0*(1-r) + r*p1;

	t = [qr.r pr; 0 0 0 1];
