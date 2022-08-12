%PLOT Graphical robot animation
%
%	PLOT(ROBOT, Q)
%	PLOT(ROBOT, Q, options)
%
% Displays a graphical animation of a robot based on the
% kinematic model.  A stick figure polyline joins the origins of
% the link coordinate frames.
% The robot is displayed at the joint angle Q, or if a matrix it is
% animated as the robot moves along the trajectory.
%
% The graphical robot object holds a copy of the robot object and
% the graphical element is tagged with the robot's name (.name method).
% This state also holds the last joint configuration 
% drawn (.q method).
%
% If no robot of this name is currently displayed then a robot will
% be drawn in the current figure.  If the robot already exists then
% that graphical model will be found and moved.
%
% MULTIPLE VIEWS OF THE SAME ROBOT
% If one or more plots of this robot already exist then these will all
% be moved according to the argument Q.
%
% MULTIPLE ROBOTS
% Multiple robots can be displayed in the same plot, by using "hold on"
% before calls to plot(robot).
%
% options is a list of any of the following:
% 'workspace' [xmin, xmax ymin ymax zmin zmax]
% 'perspective' 'ortho'		controls camera view mode
% 'erase' 'noerase'		controls erasure of arm during animation
% 'loop' 'noloop'		controls endless loop mode
% 'base' 'nobase'		controls display of base 'pedestal'
% 'wrist' 'nowrist'		controls display of wrist
% 'name', 'noname'		display the robot's name 
% 'shadow' 'noshadow'		controls display of shadow
% 'xyz' 'noa'			wrist axis label
% 'joints' 'nojoints'		controls display of joints
% 'mag' scale			annotation scale factor
%
% The options come from 3 sources and are processed in the order:
% 1. Cell array of options returned by the function PLOTBOTOPT
% 2. Cell array of options returned by the .plotopt method of the
%    robot object.  These are set by the .plotopt method.
% 3. List of arguments in the command line.
%
% GRAPHICAL ANNOTATIONS:
%
% The basic stick figure robot can be annotated with
%  shadow on the floor
%  XYZ wrist axes and labels
%  joint cylinders and axes
%
% All of these require some kind of dimension and this is determined
% using a simple heuristic from the workspace dimensions.  This dimension
% can be changed by setting the multiplicative scale factor using the
% 'mag' option above.
%
% GETTING GRAPHICAL ROBOT STATE:
% q = PLOT(ROBOT)
% Returns the joint configuration from the state of an existing 
% graphical representation of the specified robot.  If multiple
% instances exist, that of the first one returned by findobj() is
% given.
%
% See also: PLOTBOTOPT, DRIVEBOT, FKINE, ROBOT.


% HANDLES:
%
%  A robot comprises a bunch of individual graphical elements and these are 
% kept in a structure which can be stored within the .handle element of a
% robot object:
%	h.robot		the robot stick figure
%	h.shadow	the robot's shadow
%	h.x		wrist vectors
%	h.y
%	h.z
%	h.xt		wrist vector labels
%	h.yt
%	h.zt
%
%  The plot function returns a new robot object with the handle element set.
%
% For the h.robot object we additionally: 
%	- save this new robot object as its UserData
%	- tag it with the name field from the robot object
%
%  This enables us to find all robots with a given name, in all figures,
% and update them.

% MOD.HISTORY
% 12/94	make axis scaling adjust to robot kinematic params
% 4/99	use objects
% 2/01	major rewrite, axis names, drivebot, state etc.
% $Log: plot.m,v $
% Revision 1.4  2002/04/28 03:03:22  pic
% Fixed up newplot logic.
%
% Revision 1.3  2002/04/14 02:35:36  pic
% Cleanup internal structure.
% Improve the newplot behavious, not complete.
%
% Revision 1.2  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.4 $
% Copyright (C) 1993-2002, by Peter I. Corke

function rnew = plot(robot, tg, varargin)

	%
	% q = PLOT(robot)
	% return joint coordinates from a graphical robot of given name
	%
	if nargin == 1,
		rh = findobj('Tag', robot.name);%返回所有具有Tag属性的图形，并将其设为robot.name
		if ~isempty(rh),
			r = get(rh(1), 'UserData');%返回然后rh（1）确认图形中UserData的值到r中
			rnew = r.q;
		end
		return
	end

	%
	% robot2 = ROBOT(robot, q, varargin)
	%
	np = numrows(tg);%tg的行数
	n = robot.n;

	if numcols(tg) ~= n,
		error('Insufficient columns in q')
	end

	if isfield(robot, 'handles'),%测试robot中是否包括handles字段（the field）
		% handles provided, animate just that robot
		for r=1:repeat,
		    for p=1:np,
			animate( robot, tg(p,:));
		    end
		end

		return;
	end

	% Do the right thing with figure windows.

	% get handle of any existing robot of same name
	rh = findobj('Tag', robot.name);
	% process options
	opt = plot_options(robot, varargin);

	fh = get(0, 'Children');
	if isempty(fh)
		% no figures exist at all, create one
		%disp('no figures at all, creating one')
		figure
		h = create_new_robot(robot, opt);

		% save the handles in the passed robot object, and
		% attach it to the robot as user data.
		robot.handle = h;
		set(h.robot, 'Tag', robot.name);
		set(h.robot, 'UserData', robot);
	else 
		axh = findobj(gcf, 'Type', 'Axes');
		numchildren = length( get(gcf, 'Children') );
		if isempty(axh) | (numchildren <= 1),
			% empty figure, just created, use it
			%disp('Use empty figure')
			axis(opt.dims);
			h = create_new_robot(robot, opt);

			% save the handles in the passed robot object, and
			% attach it to the robot as user data.
			robot.handle = h;
			set(h.robot, 'Tag', robot.name);
			set(h.robot, 'UserData', robot);
		else
			%disp('reusing existing figure');
		end
	end

	% now animate all robots tagged with this name

	rh = findobj('Tag', robot.name);
	for r=1:opt.repeat,
	    for p=1:np,
		for r=rh',
			animate( get(r, 'UserData'), tg(p,:));
		end
	    end
	end

	% save the last joint angles away in the graphical robot
	for r=rh',
		rr = get(r, 'UserData');
		rr.q = tg(end,:);
		set(r, 'UserData', rr);
	end

	if nargout > 0,
		rnew = robot;
	end

%PLOT_OPTIONS
%
%	o = PLOT_OPTIONS(robot, options)
%
% Returns an options structure

function o = plot_options(robot, optin)
	%%%%%%%%%%%%%% process options
	o.erasemode = 'xor';
	o.joints = 1;
	o.wrist = 1;
	o.repeat = 1;
	o.shadow = 1;
	o.wrist = 1;
	o.dims = [];
	o.base = 0;
	o.wristlabel = 'xyz';
	o.projection = 'orthographic';
	o.magscale = 1;
	o.name = 1;

	% read options string in the order
	%	1. robot.plotopt
	%	2. the M-file plotbotopt if it exists
	%	3. command line arguments
	if exist('plotbotopt', 'file') == 2,
		options = plotbotopt;
		options = [options robot.plotopt optin];
	else
		options = [robot.plotopt optin];
	end
	i = 1;
	while i <= length(options),
		switch lower(options{i}),
		case 'workspace'
			o.dims = options{i+1};
			i = i+1;
		case 'mag'
			o.magscale = options{i+1};
			i = i+1;
		case 'perspective'
			o.projection = 'perspective';
		case 'ortho'
			o.projection = 'orthographic';
		case 'erase'
			o.erasemode = 'xor';
		case 'noerase'
			o.erasemode = 'none';
		case 'base'
			o.base = 1;
		case 'nobase'
			o.base = 0;
		case 'loop'
			o.repeat = Inf;
		case 'noloop'
			o.repeat = 1;
		case 'name',
			o.name = 1;
		case 'noname',
			o.name = 0;
		case 'wrist'
			o.wrist = 1;
		case 'nowrist'
			o.wrist = 0;
		case 'shadow'
			o.shadow = 1;
		case 'noshadow'
			o.shadow = 0;
		case 'xyz'
			o.wristlabel = 'XYZ';
		case 'noa'
			o.wristlabel = 'NOA';
		case 'joints'
			o.joints = 1;
		case 'nojoints'
			o.joints = 0;
		otherwise
			error(['unknown option: ' options{i}]);
		end
		i = i+1;
	end

	if isempty(o.dims),
		%
		% simple heuristic to figure the maximum reach of the robot
		%
		L = robot.link;
		reach = 0;
		for i=1:robot.n,
			reach = reach + abs(L{i}.A) + abs(L{i}.D);
		end
		o.dims = [-reach reach -reach reach -reach reach];
		o.mag = reach/10;
	else
		reach = min(abs(dims));
	end
	o.mag = o.magscale * reach/10;

%CREATE_NEW_ROBOT
% 
%	h = CREATE_NEW_ROBOT(robot, opt)
%
% Using data from robot object and options create a graphical robot in
% the current figure.
%
% Returns a structure of handles to graphical objects.
%
% If current figure is empty, draw robot in it
% If current figure has hold on, add robot to it
% Otherwise, create new figure and draw robot in it.
%	

function h = create_new_robot(robot, opt)
	h.mag = opt.mag;

	%
	% setup an axis in which to animate the robot
	%
	% handles not provided, create graphics
	%disp('in creat_new_robot')
	if ~ishold,
		% if current figure has hold on, then draw robot here
		% otherwise, create a new figure
		%disp('not hold')
		%disp('Create new figure')
		axis(opt.dims);
	end
	xlabel('X')
	ylabel('Y')
	zlabel('Z')
	set(gca, 'drawmode', 'fast');
	grid on


	zlim = get(gca, 'ZLim');
	h.zmin = zlim(1);

	if opt.base,
		b = transl(robot.base);
		line('xdata', [b(1);b(1)], ...
			'ydata', [b(2);b(2)], ...
			'zdata', [h.zmin;b(3)], ...
			'LineWidth', 4, ...
			'color', 'red');
	end
	if opt.name,
		b = transl(robot.base);
		text(b(1), b(2)-opt.mag, [' ' robot.name])
	end
	% create a line which we will
	% subsequently modify.  Set erase mode to xor for fast
	% update
	%
	h.robot = line(robot.lineopt{:}, ...
		'Erasemode', opt.erasemode);
	if opt.shadow == 1,
		h.shadow = line(robot.shadowopt{:}, ...
			'Erasemode', opt.erasemode);
	end

	if opt.wrist == 1,	
		h.x = line('xdata', [0;0], ...
			'ydata', [0;0], ...
			'zdata', [0;0], ...
			'color', 'red', ...
			'erasemode', 'xor');
		h.y = line('xdata', [0;0], ...
			'ydata', [0;0], ...
			'zdata', [0;0], ...
			'color', 'green', ...
			'erasemode', 'xor');
		h.z = line('xdata', [0;0], ...
			'ydata', [0;0], ...
			'zdata', [0;0], ...
			'color', 'blue', ...
			'erasemode', 'xor');
		h.xt = text(0, 0, opt.wristlabel(1), 'erasemode', 'xor');
		h.yt = text(0, 0, opt.wristlabel(2), 'erasemode', 'xor');
		h.zt = text(0, 0, opt.wristlabel(3), 'erasemode', 'xor');

	end

	%
	% display cylinders (revolute) or boxes (pristmatic) at
	% each joint, as well as axis centerline.
	%
	if opt.joints == 1,
		L = robot.link;
		for i=1:robot.n,

			% cylinder or box to represent the joint
			if L{i}.sigma == 0,
				N = 8;
			else
				N = 4;
			end
			[xc,yc,zc] = cylinder(opt.mag/4, N);
			zc(zc==0) = -opt.mag/2;
			zc(zc==1) = opt.mag/2;

			% add the surface object and color it
			h.joint(i) = surface(xc,yc,zc);
			%set(h.joint(i), 'erasemode', 'xor');
			set(h.joint(i), 'FaceColor', 'blue');

			% build a matrix of coordinates so we
			% can transform the cylinder in animate()
			% and hang it off the cylinder
			xyz = [xc(:)'; yc(:)'; zc(:)'; ones(1,2*N+2)]; 
			set(h.joint(i), 'UserData', xyz);

			% add a dashed line along the axis
			h.jointaxis(i) = line('xdata', [0;0], ...
				'ydata', [0;0], ...
				'zdata', [0;0], ...
				'color', 'blue', ...
				'linestyle', '--', ...
				'erasemode', 'xor');
		end
	end

%ANIMATE   move an existing graphical robot
%
%	animate(robot, q)
%
% Move the graphical robot to the pose specified by the joint coordinates q.
% Graphics are defined by the handle structure robot.handle.

function animate(robot, q)

	n = robot.n;
	h = robot.handle;
	L = robot.link;

	mag = h.mag;

	b = transl(robot.base);
	x = b(1);
	y = b(2);
	z = b(3);

	xs = b(1);
	ys = b(2);
	zs = h.zmin;

	% compute the link transforms, and record the origin of each frame
	% for the animation.
	t = robot.base;
	Tn = t;
	for j=1:n,
		Tn(:,:,j) = t;

		t = t * L{j}(q(j));

		x = [x; t(1,4)];
		y = [y; t(2,4)];
		z = [z; t(3,4)];
		xs = [xs; t(1,4)];
		ys = [ys; t(2,4)];
		zs = [zs; h.zmin];
	end
	t = t *robot.tool;

	%
	% draw the robot stick figure and the shadow
	%
	set(h.robot,'xdata', x, 'ydata', y, 'zdata', z);
	if isfield(h, 'shadow'),
		set(h.shadow,'xdata', xs, 'ydata', ys, 'zdata', zs);
	end
	

	%
	% display the joints as cylinders with rotation axes
	%
	if isfield(h, 'joint'),
		xyz_line = [0 0; 0 0; -2*mag 2*mag; 1 1];

		for j=1:n,
			% get coordinate data from the cylinder
			xyz = get(h.joint(j), 'UserData');
			xyz = Tn(:,:,j) * xyz;
			ncols = numcols(xyz)/2;
			xc = reshape(xyz(1,:), 2, ncols);
			yc = reshape(xyz(2,:), 2, ncols);
			zc = reshape(xyz(3,:), 2, ncols);

			set(h.joint(j), 'Xdata', xc, 'Ydata', yc, ...
				'Zdata', zc);

			xyzl = Tn(:,:,j) * xyz_line;
			set(h.jointaxis(j), 'Xdata', xyzl(1,:), ...
				'Ydata', xyzl(2,:), ...
				'Zdata', xyzl(3,:));

		end
	end

	%
	% display the wrist axes and labels
	%
	if isfield(h, 'x'),
		%
		% compute the wrist axes, based on final link transformation
		% plus the tool transformation.
		%
		xv = t*[mag;0;0;1];
		yv = t*[0;mag;0;1];
		zv = t*[0;0;mag;1];

		%
		% update the line segments, wrist axis and links
		%
		set(h.x,'xdata',[t(1,4) xv(1)], 'ydata', [t(2,4) xv(2)], ...
			'zdata', [t(3,4) xv(3)]);
		set(h.y,'xdata',[t(1,4) yv(1)], 'ydata', [t(2,4) yv(2)], ...
			 'zdata', [t(3,4) yv(3)]);
		set(h.z,'xdata',[t(1,4) zv(1)], 'ydata', [t(2,4) zv(2)], ...
			 'zdata', [t(3,4) zv(3)]);
		set(h.xt, 'Position', xv(1:3));
		set(h.yt, 'Position', yv(1:3));
		set(h.zt, 'Position', zv(1:3));
	end
	
	drawnow
