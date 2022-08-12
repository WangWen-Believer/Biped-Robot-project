%TRANSL Create translational transform
%
%	TR = TRANSL(X, Y, Z)
%	TR = TRANSL( [X Y Z] )
%
% Returns a homogeneous transformation representing a translation of X, Y
% and Z.
%
%	[X Y Z]' = TRANSL(T)
%
% Returns the translational part of a homogenous transform as a 3-element 
% column vector.
%
%	[X Y Z] = TRANSL(TG)
%
% Returns a  matrix of the X, Y and Z elements extracted from a Cartesian 
% trajectory matrix TG.
%
% See also: CTRAJ.

% $Log: transl.m,v $
% Revision 1.2  2002/04/01 11:47:19  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1993-2002, by Peter I. Corke

function r = transl(x, y, z)
	if nargin == 1,
		if ishomog(x),
			r = x(1:3,4);
		elseif ndims(x) == 3,
			r = squeeze(x(1:3,4,:))';
		else
			t = x(:);
			r =    [eye(3)			t;
				0	0	0	1];
		end
	elseif nargin == 3,
		t = [x; y; z];
		r =    [eye(3)			t;
			0	0	0	1];
	end
