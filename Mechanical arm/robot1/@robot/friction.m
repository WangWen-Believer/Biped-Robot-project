%FRICTION Compute friction torque for a ROBOT object
%
%	TAU = FRICTION(ROBOT, QD)
%
% Return the vector of joint friction torques for the specified
% ROBOT object with link velocities of QD.  
%
% SEE ALSO: LINK/FRICTION

% MOD HISTORY
% $Log: friction.m,v $
% Revision 1.1  2002/04/14 10:18:56  pic
% Remove friction from all links of robot.
%
% $Revision: 1.1 $

% Copyright (C) 1999-2002, by Peter I. Corke

function  tau = friction(robot, qd)

	L = robot.link;

	for i=1:robot.n,
		tau(i) = friction(L{i}, qd(i));
	end

