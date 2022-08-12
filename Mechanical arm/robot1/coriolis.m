%CORIOLIS Compute the manipulator Coriolis matrix
%
% 	C = CORIOLIS(ROBOT, Q, QD)
%
% Returns the n element Coriolis/centripetal torque vector at the specified 
% pose and velocity.
% ROBOT is a robot object and describes the manipulator dynamics and 
% kinematics.
%
% If Q and QD are row vectors, CORIOLIS(DYN,Q,QD) is a row vector 
% of joint torques.
% If Q and QD are matrices, each row is interpretted as a joint state 
% vector, and CORIOLIS(DYN,Q,QD) is a matrix each row being the 
% corresponding joint %	torques.
%
% See also: ROBOT, RNE, ITORQUE, GRAVLOAD.


% Copyright (C) 1993-2002, by Peter I. Corke
% MOD HISTORY
% 	4/99 add object support
% $Log: coriolis.m,v $
% Revision 1.2  2002/04/01 11:47:11  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $

function c = coriolis(robot, q, qd)
	c = rne(robot, q, qd, zeros(size(q)), [0;0;0]);
