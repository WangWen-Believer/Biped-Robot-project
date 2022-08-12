%UNIT Unitize a quaternion
%
%	QU = UNIT(Q)
%
% Returns a unit quaternion.

% $Log: unit.m,v $
% Revision 1.2  2002/04/01 12:06:48  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function qu = unit(q)
	qu = q / norm(q);
