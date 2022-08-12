%TR2DIFF Convert a transform difference to differential representation
%
%	D = TR2DIFF(T)
%	D = TR2DIFF(T1, T2)
%
% First form converts a homogeneous transform representing an
% infinitessimal motion to a 6-element differential representation.
% Such a homogeneous transform has a rotational submatrix that is,
% approximately, skew symmetric.
%
% Second form returns the 6-element differential motion required to move
% from T1 to T2 in base coordinates.
%
% See also: DIFF2TR.

% Copyright (C) 1993-2002, by Peter I. Corke

% MOD.HISTORY
% 1/95	take mean of both values in the skew-symmetric matrix
% 2/95	add two argument version as part of ikine() revamp
% $Log: tr2diff.m,v $
% Revision 1.3  2002/04/14 11:01:23  pic
% Updated see also line.
%
% Revision 1.2  2002/04/01 11:47:18  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $

function d = tr2diff(t1, t2)
	if nargin == 1,
		d = [	t1(1:3,4);
			0.5*[t1(3,2)-t1(2,3); t1(1,3)-t1(3,1); t1(2,1)-t1(1,2)]];
	else
		d = [	t2(1:3,4)-t1(1:3,4);
			0.5*(	cross(t1(1:3,1), t2(1:3,1)) + ...
				cross(t1(1:3,2), t2(1:3,2)) + ...
				cross(t1(1:3,3), t2(1:3,3)) ...
			)];
	end

