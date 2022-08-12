%DIFF2TR Convert a differential to a homogeneous transform
%
% 	TR = DIFF2TR(D)
%
% Returns a homogeneous transform representing differential translation 
% and rotation.  The matrix contains a skew symmetric rotation submatrix.
%
% See also: TR2DIFF.

% $Log: diff2tr.m,v $
% Revision 1.2  2002/04/01 11:47:11  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1993-2002, by Peter I. Corke

function delta = diff2tr(d)
	delta =[	0	-d(6)	d(5)	d(1)
			d(6)	0	-d(4)	d(2)
			-d(5)	d(4)	0	d(3)
			0	0	0	0	];
