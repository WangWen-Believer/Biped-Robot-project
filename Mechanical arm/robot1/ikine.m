%IKINE Inverse manipulator kinematics
%
%	Q = IKINE(ROBOT, T)
%	Q = IKINE(ROBOT, T, Q)
%	Q = IKINE(ROBOT, T, Q, M)
%
% Returns the joint coordinates corresponding to the end-effector transform T.
% Note that the inverse kinematic solution is generally not unique, and 
% depends on the initial guess Q (which defaults to 0).
%
%	QT = IKINE(ROBOT, TG)
%	QT = IKINE(ROBOT, TG, Q)
%	QT = IKINE(ROBOT, TG, Q, M)
%
% Returns the joint coordinates corresponding to each of the transforms in 
% the 4x4xN trajectory TG.
% Returns one row of QT for each input transform.  The initial estimate 
% of QT for each time step is taken as the solution from the previous 
% time step.
%
% If the manipulator has fewer than 6 DOF then this method of solution
% will fail, since the solution space has more dimensions than can
% be spanned by the manipulator joint coordinates.  In such a case
% it is necessary to provide a mask matrix, M, which specifies the 
% Cartesian DOF (in the wrist coordinate frame) that will be ignored
% in reaching a solution.  The mask matrix has six elements that
% correspond to translation in X, Y and Z, and rotation about X, Y and
% Z respectively.  The value should be 0 (for ignore) or 1.  The number
% of non-zero elements should equal the number of manipulator DOF.
%
% Solution is computed iteratively using the pseudo-inverse of the
% manipulator Jacobian.
%
% Such a solution is completely general, though much less efficient 
% than specific inverse kinematic solutions derived symbolically.
% 
% This approach allows a solution to obtained at a singularity, but 
% the joint angles within the null space are arbitrarily assigned.
%
% For instance with a typical 5 DOF manipulator one would ignore
% rotation about the wrist axis, that is, M = [1 1 1 1 1 0].
%
%
% See also: FKINE, TR2DIFF, JACOB0, IKINE560.
 
% Copyright (C) 1993-2002, by Peter I. Corke

% MOD.HISTORY
% 2/95	use new 2-argument version of tr2diff(), cleanup
% 3/99	uses objects
% 6/99	initialize qt before loop
% 2/01	remove inv(base) xform, since it is included in fkine
% 10/01	bug in mask for <6 axes
% $Log: ikine.m,v $
% Revision 1.4  2002/04/14 10:15:41  pic
% Fixed error message text.
%
% Revision 1.3  2002/04/01 11:47:13  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.4 $

function qt = ikine(robot, tr, q, m)
	%
	%  solution control parameters
	%
	ilimit = 1000;%循环次数
	stol = 1;%最终误差
    tr
	n = robot.n;
    n
	if nargin == 2,
		q = zeros(n, 1);
        
	else
		q = q(:);
	end
	if nargin == 4,
		m = m(:);
		if length(m) ~= 6,
			error('Mask matrix should have 6 elements');
		end
		if length(find(m)) ~= robot.n 
			error('Mask matrix must have same number of 1s as robot DOF')
		end
	else
		if n < 6,
			disp('For a manipulator with fewer than 6DOF a mask matrix argument should be specified');
		end
		m = ones(6, 1);
	end
		

	tcount = 0;
	if ishomog(tr),		% single xform case
		nm = 2;
		count = 0;
		while nm > stol,
			e = tr2diff(fkine(robot, q'), tr) .* m;
            
			dq = pinv( jacob0(robot, q) ) * e;
            
			q = q + dq;
			nm = norm(dq);
            num
			count = count+1;
			if count > ilimit,
				error('Solution wouldn''t converge')
			end
		end
		qt = q';
	else			% trajectory case
		np = size(tr,3);
        np
		qt = [];
		for i=1:np
			nm = 2;
			T = tr(:,:,i);
			count = 0;
			while nm > stol,
				e = tr2diff(fkine(robot, q'), T) .* m; 
                e
				dq = pinv( jacob0(robot, q) ) * e;               
				q = q + dq;                
				nm = norm(dq);%矩阵的范数表示两矩阵之间的距离，用来统计误差
				count = count+1;
				if count > ilimit,
					fprintf('i=%d, nm=%f\n', i, nm);
					error('Solution wouldn''t converge')
                end        
            end            
			qt = [qt; q']; 
			tcount = tcount + count;
		end
	end
