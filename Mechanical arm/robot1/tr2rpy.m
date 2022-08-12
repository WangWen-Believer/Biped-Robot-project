%TR2RPY Convert a homogeneous transform matrix to roll/pitch/yaw angles
%
%	[R P Y] = TR2RPY(TR)
%
% Returns a vector of roll/pitch/yaw angles corresponding to the rotational 
% part of the homogeneous transform TR.
%
% See also:  RPY2TR, TR2EUL

% $Log: tr2rpy.m,v $
% Revision 1.2  2002/04/01 11:47:19  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1993-2002, by Peter I. Corke

function rpy = tr2rpy(m)
	
	rpy = zeros(1,3);

	if abs(m(1,1)) < eps & abs(m(2,1)) < eps,
		% singularity
		rpy(1) = 0;
		rpy(2) = atan2(-m(3,1), m(1,1));
		rpy(3) = atan2(-m(2,3), m(2,2));
	else,
		rpy(1) = atan2(m(2,1), m(1,1));
		sp = sin(rpy(1));
		cp = cos(rpy(1));
		rpy(2) = atan2(-m(3,1), cp * m(1,1) + sp * m(2,1));
		rpy(3) = atan2(sp * m(1,3) - cp * m(2,3), cp*m(2,2) - sp*m(1,2));
	end
