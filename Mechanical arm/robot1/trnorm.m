%TRNORM Normalize a homogeneous transformation.
%
%	TN = TRNORM(T) 
%
% Returns a normalized homogeneous tranformation matrix in which the rotation
% submatrix is a proper orthogonal matrix.
% The O and V vectors are normalized and the normal vector is formed from
% O x A.
%
% Finite word length arithmetic can cause transforms to become `unnormalized'.
%
% See also: OA2TR

% $Log: trnorm.m,v $
% Revision 1.2  2002/04/01 11:47:19  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1993-2002, by Peter I. Corke

function r = trnorm(t)
	n = cross(t(1:3,2), t(1:3,3));	% N = O x A
	r = [unit(n) unit(t(1:3,2)) unit(t(1:3,3)) t(1:3,4); 0 0 0 1];
