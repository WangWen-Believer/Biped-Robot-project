%CINERTIA Compute the Cartesian (operational space) manipulator inertia matrix
%
%	M = CINERTIA(ROBOT, Q)
%
% Return the n x n inertia matrix which relates Cartesian force/torque to 
% Cartesian acceleration.
% ROBOT is an n-axis robot object and describes the manipulator dynamics and 
% kinematics, and Q is an n element vector of joint state.
%
% See also: INERTIA, ROBOT, RNE.

% MOD HISTORY
% 	4/99 add object support
% $Log: cinertia.m,v $
% Revision 1.2  2002/04/01 11:47:10  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

% Copyright (C) 1993-2002, by Peter I. Corke

function Mx = cinertia(robot, q)
	J = jacob0(robot, q);
	Ji = inv(J);
	M = inertia(robot, q);
	Mx = Ji' * M * Ji;
