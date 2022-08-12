%NUMROWS Return number of rows in matrix
%
%	NR = NUMROWS(M)
%
% Return the number of rows in the matrix M.


% Copyright (C) 1993-2002, by Peter I. Corke
% $Log: numrows.m,v $
% Revision 1.2  2002/04/01 11:47:15  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

function r = numrows(m)

	[r,x] = size(m);
