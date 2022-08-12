%TR2ROT Return rotational submatrix of a homogeneous transformation
%
%	R = TR2ROT(T)
%
% Return R the 3x3 orthonormal rotation matrix from the homogeneous 
% transformation T.
%
% SEE ALSO: ROT2TR

% $Log: tr2rot.m,v $
% Revision 1.2  2002/04/01 11:47:19  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1999-2002, by Peter I. Corke

function R = tr2rot(T)

	if ~ishomog(T)
		error('input must be a homogeneous transform');
	end

	R = T(1:3,1:3);
