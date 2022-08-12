%FKINE  Forward robot kinematics for serial link manipulator
%
%	TR = FKINE(ROBOT, Q)
%
% Computes the forward kinematics for each joint space point defined by Q.
% ROBOT is a robot object.
%
% For an n-axis manipulator Q is an n element vector or an m x n matrix of
% robot joint coordinates.
% 
% If Q is a vector it is interpretted as the generalized joint coordinates, and
% FKINE(ROBOT, Q) returns a 4x4 homogeneous transformation for the tool of
% the manipulator.
%
% If Q is a matrix, the rows are interpretted as the generalized 
% joint coordinates for a sequence of points along a trajectory.  Q(i,j) is
% the j'th joint parameter for the i'th trajectory point.  In this case
% FKINE(ROBOT, Q) returns 3D matrix where the last subscript is the index
% along the path.
%
% The robot's base or tool transform, if present, are incorporated into the
% result.
%
% See also: LINK, ROBOT.

% MOD HISTORY
% 	6/99	init tt to zeros rather than [], problem with cat() v 5.3
% $Log: fkine.m,v $
% Revision 1.3  2002/04/14 10:14:34  pic
% Update comments.
%
% Revision 1.2  2002/04/01 11:47:13  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $

% Copyright (C) 1993-2002, by Peter I. Corke

function t = fkine(robot, q)
	%
	% evaluate fkine for each point on a trajectory of 
	% theta_i or q_i data
	%

	n = robot.n;
	L = robot.link;

  
	if length(q) == n,%正运动学求解
		t = robot.base;
		for i=1:n,
			t = t * L{i}(q(i));%通过循环，计算最终的位姿矩阵
		end
		t = t * robot.tool;
	else
		if numcols(q) ~= n,
			error('bad data')
		end
		t = zeros(4,4,0);
		for qv=q',		% for each trajectory point
			tt = robot.base;%初始化
			for i=1:n,
				tt = tt * L{i}(qv(i));%计算位姿，正解，每个点的位姿计算72组值
			end
			t = cat(3, t, tt * robot.tool);
		end
    end
   
   
