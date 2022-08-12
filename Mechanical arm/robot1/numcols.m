%NUMCOLS Return number of columns in matrix
%
%	NC = NUMCOLS(M)
%
% Return the number of columns in the matrix M.

% Copyright (C) 1993-2002, by Peter I. Corke

% $Log: numcols.m,v $
% Revision 1.2  2002/04/01 11:47:15  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

function c = numcols(m)
	[x,c] = size(m);
