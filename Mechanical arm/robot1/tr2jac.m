%TR2JAC Compute a Jacobian to map differentials between frames
%
%	J = TR2JAC(T)
%
% Returns a 6x6 Jacobian matrix to map differentials (joint velocity) between 
% frames related by the homogeneous transform T.
%
% See also: TR2DIFF, DIFF2TR.

% $Log: tr2jac.m,v $
% Revision 1.3  2002/04/14 11:01:22  pic
% Updated see also line.
%
% Revision 1.2  2002/04/01 11:47:18  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $
% Copyright (C) 1993-2002, by Peter I. Corke

function J = tr2jac(t)
	J = [	t(1:3,1)'	cross(t(1:3,4),t(1:3,1))'
		t(1:3,2)'	cross(t(1:3,4),t(1:3,2))'
		t(1:3,3)'	cross(t(1:3,4),t(1:3,3))'
		zeros(3,3)	t(1:3,1:3)'		];
		
