%INV Invert a unit-quaternion
%
%	QI = inv(Q)
%
% Return the inverse of the unit-quaternion Q.
%

% $Log: inv.m,v $
% Revision 1.2  2002/04/01 12:06:17  pic
% Removed unneccessary normalization.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function qi = inv(q)

	qi = quaternion([q.s -q.v]);
