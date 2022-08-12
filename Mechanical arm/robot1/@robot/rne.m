%RNE Compute inverse dynamics via recursive Newton-Euler formulation
%
%	TAU = RNE(ROBOT, Q, QD, QDD)
%	TAU = RNE(ROBOT, [Q QD QDD])
%
% Returns the joint torque required to achieve the specified joint position,
% velocity and acceleration state.
%
% Gravity vector is an attribute of the robot object but this may be 
% overriden by providing a gravity acceleration vector [gx gy gz].
%
%	TAU = RNE(ROBOT, Q, QD, QDD, GRAV)
%	TAU = RNE(ROBOT, [Q QD QDD], GRAV)
%
% An external force/moment acting on the end of the manipulator may also be
% specified by a 6-element vector [Fx Fy Fz Mx My Mz].
%
%	TAU = RNE(ROBOT, Q, QD, QDD, GRAV, FEXT)
%	TAU = RNE(ROBOT, [Q QD QDD], GRAV, FEXT)
%
% where Q, QD and QDD are row vectors of the manipulator state; pos, vel, 
% and accel.
%
% The torque computed also contains a contribution due to armature
% inertia.
%
% RNE can be either an M-file or a MEX-file.  See the manual for details on
% how to configure the MEX-file.  The M-file is a wrapper which calls either
% RNE_DH or RNE_MDH depending on the kinematic conventions used by the robot
% object.
%
% See also: ROBOT, ACCEL, GRAVLOAD, INERTIA.

%
% verified against MAPLE code, which is verified by examples
%

% Copyright (C) 1992-2002, by Peter I. Corke

% MOD.HISTORY
%       6/95    make use of passed in FEXT 
%       4/95    fix bug in use of passed FEXT 
% 11/96	bug for prismatic case 
% 3/99	uses objects
% 12/01	changed into wrapper for DH or MDH conventions
% $Log: rne.m,v $
% Revision 1.2  2002/04/01 12:02:28  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.2 $
%
% Copyright (C) Peter Corke 1999

function tau = rne(robot, varargin)
	if robot.mdh == 0,
		tau = rne_dh(robot, varargin{:});
	else
		tau = rne_mdh(robot, varargin{:});
	end
