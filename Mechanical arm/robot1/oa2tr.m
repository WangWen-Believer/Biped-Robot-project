%OA2TR Convert O/A vectors to homogeneous transformation
%
% 	TR = OA2TR(O, A)
%
% Returns a homogeneous tranformation for the specified orientation and 
% approach vectors.  The rotation submatrix is formed from 3 vectors such that
% R = [N O A] and N = O x A.  
% The submatrix is guaranteed to be orthonormal so long as O and A are 
% not parallel.
%
% See also: RPY2TR, EUL2TR

% $Log: oa2tr.m,v $
% Revision 1.3  2002/04/14 10:59:58  pic
% Expanded comment.
%
% Revision 1.2  2002/04/01 11:47:15  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $
% Copyright (C) 1993-2002, by Peter I. Corke

function r = oa2tr(o, a)
	n = cross(o, a);
	r = [unit(n(:)) unit(o(:)) unit(a(:)) zeros(3,1); 0 0 0 1];
