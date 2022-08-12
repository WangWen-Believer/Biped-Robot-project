%SUBSASGN Assignment methods on a ROBOT object
%
%	ROBOT.gravity = [gx gy gz]
%	ROBOT.base = 4x4 homog xform
%	ROBOT.tool = 4x4 homog xform
%	ROBOT.qlim = [qlower qupper]	set joint limits
%	ROBOT.offset 		set joint offset vector
%	ROBOT.mdh 		set kinematic convention for all links
%
%	ROBOT.name = 'name'
%	ROBOT.manuf = 'who built it'
%	ROBOT.comment = 'general comment'
%
%	ROBOT.plotopt 	set options for plot(robot)
%	ROBOT.lineopt 	set graphical line drawing option string for links
%	ROBOT.shadowopt set graphical line drawing option string for shadow
%	ROBOT.handle	save graphics handles in object
%	ROBOT.q 	set joint angles for plot(robot)

% $Log: subsasgn.m,v $
% Revision 1.3  2002/04/01 12:02:28  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.3 $
% Copyright (C) 1999-2002, by Peter I. Corke

function r = subsasgn(r, s, v)

	if s(1).type  ~= '.'
		error('only .field supported')
	end
	switch s(1).subs,
	%%%%%%%%% extensions
	case 'tool',
		if ~ishomog(v)
			error('base must be a homogeneous transform');
		end
		r.tool = v;
	case 'base',
		if ~ishomog(v)
			error('base must be a homogeneous transform');
		end
		r.base = v;
	case 'mdh',
		L = r.link;
		for i=1:r.n,
			L{i}.mdh = v;
		end
		r.link = L;
		r.mdh = v;

	case 'offset',
		L = r.link;
		for i=1:r.n,
			L{i}.offset = v(i);
		end
	case 'qlim',
		if numrows(v) ~= r.n,
			error('insufficient rows in joint limit matrix');
		end
		L = r.link;
		for i=1:r.n,
			L{i}.qlim = v(i,:);
		end
	case 'gravity',
		r.gravity = v;
	%%%%%%%%% graphics support
	case 'q',
		r.q = v;
	case 'lineopt',
		r.lineopt = v;
	case 'shadowopt',
		r.shadowopt = v;
	case 'plotopt',
		r.plotopt = v;
	case 'handle',
		r.handle = v;

	%%%%%%%%% descriptive strings
	case 'name',
		r.name = v;
	case 'manuf',
		r.manuf = v;
	case 'comment',
		r.comment = v;
	otherwise, error('Unknown method')
	end
