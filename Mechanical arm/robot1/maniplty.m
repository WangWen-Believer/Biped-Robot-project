%MANIPLTY Manipulability measure
%
%	M = MANIPLTY(ROBOT, Q)
%	M = MANIPLTY(ROBOT, Q, WHICH)
%
% Computes the manipulability index for the manipulator at the given pose.
%
% For an n-axis manipulator Q may be an n-element vector, or an m x n
% joint space trajectory.
%
% If Q is a vector MANIPLTY returns a scalar manipulability index.
% If Q is a matrix MANIPLTY returns a column vector of  manipulability 
% indices for each pose specified by Q.
%
% The argument WHICH can be either 'yoshikawa' (default) or 'asada' and
% selects one of two manipulability measures.
% Yoshikawa's manipulability measure gives an indication of how far 
% the manipulator is from singularities and thus able to move and 
% exert forces uniformly in all directions.
%
% Asada's manipulability measure is based on the manipulator's
% Cartesian inertia matrix.  An n-dimensional inertia ellipsoid
% 	X' M(q) X = 1
% gives an indication of how well the manipulator can accelerate
% in each of the Cartesian directions.  The scalar measure computed
% here is the ratio of the smallest/largest ellipsoid axis.  Ideally
% the ellipsoid would be spherical, giving a ratio of 1, but in
% practice will be less than 1.
%
% See also: INERTIA, JACOB0.

% MOD HISTORY
% 4/99	object support, matlab local functions
% 6/99	change switch to allow abbreviations of measure type
% $Log: maniplty.m,v $
% Revision 1.2  2002/04/01 11:47:14  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

% Copyright (C) 1993-2002, by Peter I. Corke

function w = maniplty(robot, q, which)
	n = robot.n;

	if nargin == 2,
		which = 'yoshikawa';
	end

	if length(q) == robot.n,
		q = q(:)';
	end

	w = [];
	switch which,
	case 'yoshikawa',
	case 'yoshi',
	case 'y',
		for Q = q',
			w = [w; yoshi(robot, Q)];
		end
	case 'asada'
	case 'a'
		for Q = q',
			w = [w; asada(robot, Q)];
		end
	end

function m = yoshi(robot, q)
	J = jacob0(robot, q);
	m = sqrt(det(J * J'));

function m = asada(robot, q)
	J = jacob0(robot, q);
	Ji = inv(J);
	M = inertia(robot, q);
	Mx = Ji' * M * Ji;
	e = eig(Mx);
	m = min(e) / max(e);
