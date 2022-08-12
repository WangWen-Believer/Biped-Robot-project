%UNIT Unitize a vector
%
%	VN = UNIT(V)
%
% Returns a unit vector aligned with V.

% $Log: unit.m,v $
% Revision 1.2  2002/04/01 11:47:20  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1990-2002, by Peter I. Corke

function u = unit(v)
	u = v / norm(v,'fro');
