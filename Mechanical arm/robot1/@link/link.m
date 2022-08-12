%LINK create a new LINK object
%
% A LINK object holds all information related to a robot link such as
% kinematics of the joint, rigid-body inertial parameters, motor and
% transmission parameters.
%
%	L = LINK
%	L = LINK(link)
%
% Create a default link, or a clone of the passed link.
%
%	A = LINK(q)
%
% Compute the link transform matrix for the link, given the joint
% variable q.
%
%	L = LINK([alpha A theta D])
% 	L =LINK([alpha A theta D sigma])
% 	L =LINK([alpha A theta D sigma offset])
% 	L =LINK([alpha A theta D], CONVENTION)
% 	L =LINK([alpha A theta D sigma], CONVENTION)
% 	L =LINK([alpha A theta D sigma offset], CONVENTION)
%
% If sigma or offset are not provided they default to zero.  Offset is a
% constant amount added to the joint angle variable before forward kinematics
% and is useful if you want the robot to adopt a 'sensible' pose for zero
% joint angle configuration.
%
% The optional CONVENTION argument is 'standard' for standard D&H parameters 
% or 'modified' for modified D&H parameters.  If not specified the default
% 'standard'.
% Handling the different kinematic conventions is now hidden within the LINK
% object.
%
% Conceivably all sorts of stuff could live in the LINK object such as
% graphical models of links and so on.
%
% For robot models prior to Toolbox release 5 (pre Matlab objects) the
% following object constructors are provided.
%
% 	L = LINK(DYN_ROW)		create from row of legacy DYN matrix
%	L = LINK(DYN_ROW, CONVENTION)	create from row of legacy DYN matrix
%
% SEE ALSO: LINK/SUBSREF, LINK/SUBSASGN, SHOWLINK, ROBOT.

% MOD HISTORY
% 3/99 modify to use on a LINK object
% 6/99 fix the number of fields inthe object, v5.3 doesn't let me change them
% mod by  Francisco Javier Blanco Rodriguez <jblanco@abedul.usal.es>
% $Log: link.m,v $
% Revision 1.6  2002/04/14 11:02:01  pic
% Updated see also line.
%
% Revision 1.5  2002/04/14 10:20:42  pic
% Added see also line.
%
% Revision 1.4  2002/04/01 12:04:51  pic
% General tidyup, comments, clarification, copyright, RCS keys, etc.
%
% $Revision: 1.6 $
% Copyright (C) 1999-2002, by Peter I. Corke

function l = link(dh, convention)


	if nargin == 0,
		% create an 'empty' link
		l.alpha = 0;
		l.A = 0;
		l.theta = 0;
		l.D = 0;
		l.sigma = 0;
		l.mdh = 0;
		l.offset = 0;
		
		% it's a legacy DYN matrix
		l.m = [];
		l.r = [];
		v = [];
		l.I = [];
		l.Jm = [];
		l.G = [];
		l.B = 0;
		l.Tc = [0 0];
		l.qlim = [];

		l = class(l, 'link');

	elseif isa(dh, 'link')
		% clone passed link
		l = dh;
	elseif length(dh) <= 6,
		% legacy DH matrix
		% link([alpha A theta D sigma])

		if length(dh) < 4,
				error('must provide <alpha A theta D> params');
		end
		l.alpha = dh(1);
		l.A = dh(2);
		l.theta = dh(3);
		l.D = dh(4);
		l.sigma = 0;
		if length(dh) >= 5,
			l.sigma = dh(5);
		end
		if nargin > 1
			if strncmp(convention, 'mod', 3) == 1,
				l.mdh = 1;
			elseif strncmp(convention, 'sta', 3) == 1,
				l.mdh = 0;
			else
				error('convention must be modified or standard');
			end
		else
				l.mdh = 0;	% default to standard D&H
		end
		l.offset = 0;
		if length(dh) >= 6,
			l.offset = dh(6);
		end

		% we know nothing about the dynamics
		l.m = [];
		l.r = [];
		v = [];
		l.I = [];
		l.Jm = [];
		l.G = [];
		l.B = 0;
		l.Tc = [0 0];
		l.qlim = [];

		l = class(l, 'link');
	else
		% legacy DYN matrix

		l.alpha = dh(1);
		l.A = dh(2);
		l.theta = dh(3);
		l.D = dh(4);
		if length(dh) == 4,
			l.sigma = 0;
		else
			l.sigma = dh(5);
		end
		l.mdh = 0;	% default to standard D&H
		l.offset = 0;
		
		% it's a legacy DYN matrix
		l.m = dh(6);
		l.r = dh(7:9)';		% a column vector
		v = dh(10:15);
		l.I = [	v(1) v(4) v(6)
			v(4) v(2) v(5)
			v(6) v(5) v(3)];
		if length(dh) > 15,
			l.Jm = dh(16);
		end
		if length(dh) > 16,
			l.G = dh(17);
		else
			l.G = 1;
		end
		if length(dh) > 17,
			l.B = dh(18);
		else
			l.B = 0.0;
		end
		if length(dh) > 18,
			l.Tc = dh(19:20);
		else
			l.Tc = [0 0];
		end
		l.qlim = [];
		if nargin > 1
			if strncmp(convention, 'mod', 3) == 1,
				l.mdh = 1;
			elseif strncmp(convention, 'sta', 3) == 1,
				l.mdh = 0;
			else
				error('convention must be modified or standard');
			end
		else
				l.mdh = 0;	% default to standard D&H
		end
		l = class(l, 'link');
	end
