%ACCEL Compute manipulator forward dynamics
%
%	QDD = ACCEL(ROBOT, Q, QD, TORQUE)
%	QDD = ACCEL(ROBOT, [Q QD TORQUE])
%
% Returns a vector of joint accelerations that result from applying the 
% actuator TORQUE to the manipulator ROBOT in state Q and QD.
%
% Uses the method 1 of Walker and Orin to compute the forward dynamics.
% This form is useful for simulation of manipulator dynamics, in
% conjunction with a numerical integration function.
%
% See also: RNE, ROBOT, ODE45.

% MOD HISTORY
% 4/99 add object support
% 1/02 copy rne code from inertia.m to here for speed
% $Log: accel.m,v $
% Revision 1.3  2002/04/01 11:47:10  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $

% Copyright (C) 1999-2002, by Peter I. Corke

function qdd = accel(robot, Q, qd, torque)
	n = robot.n;

	if nargin == 2,
	        q = Q(1:n);
		qd = Q(n+1:2*n);
		torque = Q(2*n+1:3*n);
	else
		q = Q;
		if length(q) == robot.n,
			q = q(:);
			qd = qd(:);
		end
	end

	% compute current manipulator inertia
	%   torques resulting from unit acceleration of each joint with
	%   no gravity.
	M = rne(robot, ones(n,1)*q', zeros(n,n), eye(n), [0;0;0]);

	% compute gravity and coriolis torque
	%    torques resulting from zero acceleration at given velocity &
	%    with gravity acting.
	tau = rne(robot, q', qd', zeros(1,n));	

	qdd = inv(M) * (torque(:) - tau');

