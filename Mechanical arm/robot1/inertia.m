%INERTIA Compute the manipulator inertia matrix
%
%	INERTIA(ROBOT, Q)
%
% Returns the n x n symmetric inertia matrix which relates joint torque 
% to joint acceleration.
% ROBOT describes the manipulator dynamics and kinematics, and Q is
% an n element vector of joint state.
%
% See also: RNE, CINERTIA, ITORQUE, CORIOLIS, GRAVLOAD.


% MOD HISTORY
% 4/99 add objects
% 6/99	init M to zeros rather than [], problem with cat() v 5.3
% $Log: inertia.m,v $
% Revision 1.2  2002/04/01 11:47:13  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

% Copyright (C) Peter Corke 1993

function M = inertia(robot, q)
	n = robot.n;

	if length(q) == robot.n,
		q = q(:)';
	end

	M = zeros(n,n,0);
	for Q = q',
		m = rne(robot, ones(n,1)*Q', zeros(n,n), eye(n), [0;0;0]);
		M = cat(3, M, m);
	end
