%ISHOMOG Test if argument is a homogeneous transformation
%
%	H = ISHOMOG(TR)
%
%  Returns true (1) if the argument tr is of dimension 4x4.

% $Log: ishomog.m,v $
% Revision 1.2  2002/04/01 11:47:14  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 2002, by Peter I. Corke

function h = ishomog(tr)
	if ndims(tr) == 2,
		h =  all(size(tr) == [4 4]);
	else
		h = 0;
	end
