%RNE	Compute inverse dynamics via recursive Newton-Euler formulation
%
%	TAU = RNE(ROBOT, Q, QD, QDD)
%	TAU = RNE(ROBOT, [Q QD QDD])
%
%	Returns the joint torque required to achieve the specified joint position,
%	velocity and acceleration state.
%
%	Gravity vector is an attribute of the robot object but this may be 
%	overriden by providing a gravity acceleration	vector [gx gy gz].
%
%	TAU = RNE(ROBOT, Q, QD, QDD, GRAV)
%	TAU = RNE(ROBOT, [Q QD QDD], GRAV)
%
%	An external force/moment acting on the end of the manipulator may also be
%	specified by a 6-element vector [Fx Fy Fz Mx My Mz].
%
%	TAU = RNE(ROBOT, Q, QD, QDD, GRAV, FEXT)
%	TAU = RNE(ROBOT, [Q QD QDD], GRAV, FEXT)
%
%	where	Q, QD and QDD are row vectors of the manipulator state; pos, vel, and accel.
%
%	The torque computed also contains a contribution due to armature
%	inertia.
%
%	See also ROBOT, FROBOT, ACCEL, GRAVLOAD, INERTIA.
%
%	Should be a MEX file.

%
% verified against MAPLE code, which is verified by examples
%

%	Copyright (C) 1992 Peter Corke

% MOD.HISTORY
%       6/95    make use of passed in FEXT 
%       4/95    fix bug in use of passed FEXT 
%	11/96	bug for prismatic case 
%	3/99	uses objects
%
%	Copyright (C) Peter Corke 1999

function tau = rne(robot, a1, a2, a3, a4, a5)
	if robot.mdh ~= 0,
		error('Jacobian only valid for standard D&H parameters')
	end

	z0 = [0;0;1];
	grav = robot.gravity;	% default gravity from the object
	fext = zeros(6, 1);

	n = robot.n;
	if numcols(a1) == 3*n,
		Q = a1(:,1:n);
		Qd = a1(:,n+1:2*n);
		Qdd = a1(:,2*n+1:3*n);
		np = numrows(Q);
		if nargin >= 3,	
			grav = a2;
		end
		if nargin == 4,
			fext = a3;
		end
	else
		np = numrows(a1);
		Q = a1;
		Qd = a2;
		Qdd = a3;
		if numcols(a1) ~= n | numcols(Qd) ~= n | numcols(Qdd) ~= n | ...
			numrows(Qd) ~= np | numrows(Qdd) ~= np,
			error('bad data');
		end
		if nargin >= 5,	
			grav = a4;
		end
		if nargin == 6,
			fext = a5;
		end
	end
	
	tau = zeros(np,n);

	for p=1:np,
		q = Q(p,:)';
		qd = Qd(p,:)';
		qdd = Qdd(p,:)';
	
		Fm = [];
		Nm = [];
		pstarm = [];
		Rm = [];
		w = zeros(3,1);
		wd = zeros(3,1);
		v = zeros(3,1);
		vd = grav;

	%
	% init some variables, compute the link rotation matrices
	%
		for j=1:n,
			link = robot.link{j};
			Tj = link(q(j));
			Rm{j} = tr2rot(Tj);
			if link.RP == 'R',
				D = link.D;
			else
				D = q(j);
			end
			alpha = link.alpha;
			pstarm(:,j) = [link.A; D*sin(alpha); D*cos(alpha)];
		end

	%
	%  the forward recursion
	%
		for j=1:n,
			link = robot.link{j};

			R = Rm{j}';
			pstar = pstarm(:,j);
			r = link.r;

			%
			% statement order is important here
			%
			if link.RP == 'R',
				% revolute axis
				wd = R*(wd + z0*qdd(j) + ...
					cross(w,z0*qd(j)));
				w = R*(w + z0*qd(j));
				%v = cross(w,pstar) + R*v;
				vd = cross(wd,pstar) + ...
					cross(w, cross(w,pstar)) +R*vd;

			else
				% prismatic axis
				w = R*w;
				wd = R*wd;
				vd = R*(z0*qdd(j)+vd) + ...
					cross(wd,pstar) + ...
					2*cross(w,R*z0*qd(j)) +...
					cross(w, cross(w,pstar));
			end

			vhat = cross(wd,r) + ...
				cross(w,cross(w,r)) + vd;
			F = link.m*vhat;
			N = link.I*wd + cross(w,link.I*w);
			Fm = [Fm F];
			Nm = [Nm N];
		end

	%
	%  the backward recursion
	%

		f = fext(1:3);		% force/moments on end of arm
		nn = fext(4:6);

		for j=n:-1:1,
			link = robot.link{j};
			pstar = pstarm(:,j);
			
			%
			% order of these statements is important, since both
			% nn and f are functions of previous f.
			%
			if j == n,
				R = eye(3,3);
			else
				R = Rm{j+1};
			end
			r = link.r;
			nn = R*(nn + cross(R'*pstar,f)) + ...
				cross(pstar+r,Fm(:,j)) + ...
				Nm(:,j);
			f = R*f + Fm(:,j);
			R = Rm{j};
			if link.RP == 'R',
				% revolute
				tau(p,j) = nn'*(R'*z0) + ...
					link.G^2 * ( link.Jm*qdd(j) + ...
						friction(link, qd(j)) ...
					);
			else
				% prismatic
				tau(p,j) = f'*(R'*z0) + ...
					link.G^2 * ( link.Jm*qdd(j) + ...
						friction(link, qd(j)) ...
					);
			end
		end
	end
