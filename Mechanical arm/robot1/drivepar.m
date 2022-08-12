%DRIVEPAR Compute Cartesian path drive parameters
%
%	DP = DRIVEPAR(T0, T1)
%
% Returns a vector of drive parameters required to plan a Cartesian path 
% from T0 to T1.
%
% This function has been obsoleted by quaternion-based interpolation in
% TRINTERP.
%
% Ref:
%	Robot manipulators: mathematics, programming and control
%	R.P. Paul, MIT Press, 1981.
%
% See also: CTRAJ, TRINTERP.

% Copyright (C) 1993-2002, by Peter I. Corke

% MOD.HISTORY
%	3/96	fixed bug: sin/cos(dp(4)) should be of dp(6)
% $Log: drivepar.m,v $
% Revision 1.2  2002/04/01 11:47:12  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

function dp = drivepar(t1, t2)
	% Using the notation of Paul, dp is
	%	dp(1)	x
	%	dp(2)	y
	%	dp(3)	z
	%	dp(4)	phi
	%	dp(5)	theta
	%	dp(6)	psi

	dp = zeros(1, 6);

	n1 = t1(1:3,1);
	o1 = t1(1:3,2);
	a1 = t1(1:3,3);
	p1 = t1(1:3,4);
	n2 = t2(1:3,1);
	o2 = t2(1:3,2);
	a2 = t2(1:3,3);
	p2 = t2(1:3,4);
	
	dp(1) = n1'*(p2 - p1);
	dp(2) = o1'*(p2 - p1);
	dp(3) = a1'*(p2 - p1);

	dp(6) = atan2(o1'*a2, n1'*a2);				% psi
	sp = sin(dp(6));
	cp = cos(dp(6));

	dp(5) = atan2(sqrt((n1'*a2)^2 + (o1'*a2)^2), a1'*a2);	% theta
	st = sin(dp(5));
	ct = cos(dp(5));
	vt = 1-ct;

	dp(4) = atan2(-sp*cp*vt*(n1'*n2)+ ...			% phi
		(cp^2*vt+ct)*(o1'*n2)-sp*st*(a1'*n2), ...
		-sp*cp*vt*(n1'*o2)+ ...
		(cp^2*vt+ct)*(o1'*o2)-sp*st*(a1'*o2));
		
