%MTIMES Multiply robot objects
%
% Robot objects can be multiplied r1*r2 which is mechanically equivalent
% to concatenating the two robots, or mounting robot r2 on the end of robot r1.

% $Log: mtimes.m,v $
% Revision 1.2  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
% Copyright (C) 1999-2002, by Peter I. Corke

function r2 = mtimes(r, l)

	if ~isa(r, 'robot')
		error('left arg must be a robot')
	end
	if isa(l, 'robot')
		r2 = robot(r);
		r2.link = [r2.link l.link];
		r2.n = length(r2.link);
	elseif isa(l, 'link')
	end
