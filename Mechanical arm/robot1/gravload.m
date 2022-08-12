%GRAVLOAD Compute the gravity loading on manipulator joints
%
%	TAUG = GRAVLOAD(ROBOT, Q)
%	TAUG = GRAVLOAD(ROBOT, Q, GRAV)
%
% Compute the joint gravity loading for the manipulator ROBOT in the
% configuration Q.
%
% If Q is a row vector, the result is a row vector of joint torques.
% If Q is a matrix, each row is interpretted as a joint state vector, and
% the result is a matrix each row being the corresponding joint torques.
%
% Gravity vector can be given explicitly using the GRAV argument, otherwise
% it defaults to the value of the ROBOT object.
%
% See also: ROBOT, RNE, ITORQUE, CORIOLIS.

% $Log: gravload.m,v $
% Revision 1.2  2002/04/01 11:47:13  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1993-2002, by Peter I. Corke

function tg = gravload(robot, q, grav)
	if numcols(q) ~= robot.n
		error('Insufficient columns in q')
	end
	if nargin == 2,
		tg = rne(robot, q, zeros(size(q)), zeros(size(q)));
	elseif nargin == 3,
		tg = rne(robot, q, zeros(size(q)), zeros(size(q)), grav);
	end
	
