%DOUBLE Convert a quaternion object to a 4-element vector

% $Log: double.m,v $
% Revision 1.2  2002/04/01 12:06:47  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) 1999-2002, by Peter I. Corke

function v = double(q)

	v = [q.s q.v];
