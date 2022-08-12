%GCAMERA	graphical camera model
%
%	H = GCAMERA(NAME, C, DIMS)
%
%	Create a graphical camera with name NAME, pixel dimensions given by 
%	DIMS = [xmin xmax ymin ymax] for the axes, and calibration matrix C.
%
%  Returns H, the handle to the graphical camera.
%
%  Once created update the camera's view with
%
%	uv = GCAMERA(H, POINTS)
%	uv = GCAMERA(H, POINTS, Tobj)
%	uv = GCAMERA(H, POINTS, Tobj, Tcam)
%
%  where H is the handle previously returned, and POINTS is the data to be
% displayed.  POINTS represents the 3D data to be displayed in the camera
% view.  If POINTS has 3 columns it is treated as a number of 3D points in
% world coordinates, one point per row.  Each point is transformed and displayed
% as a round marker.  If POINTS has 6 columns, each row is treated as the start
% and end 3D coordinate for a line segment, in world coordinates.  Each end of 
% the line is transformed and a line segment displayed.
% The optional arguments, Tobj, represents a transformation that can be applied
% to the object data, POINTS, prior to 'imaging'.  Tcam is the pose of the
% camera which defaults to the orign looking along the Z-axis.
%
%	Copyright (c) Peter Corke, 1999  Machine Vision Toolbox for Matlab

% Peter Corke 1996

function ovar = gcamera(a1, a2, a3, a4)
	if isstr(a1),
		% creating a new camera
		name = a1;
		name
		C = a2;
		C
		%dimcheck(C, 'calibration matrix', 3, 4);
		dims = a3;
		%dimcheck(dims, 'pixel dimensions', 4);

		h = findobj('Name', name);
		if isempty(h),
			h = figure;
			set(h, 'Name', name);
		else
			figure(h);
			clf
		end
		ovar = axes('XLim', dims(1:2), 'YLim', dims(3:4), ...
			 'UserData', C, ...
			'Xgrid', 'on', 'Ygrid', 'on', 'Ydir' , 'reverse');
		%line('LineStyle', 'o', 'Color', 'black');
		line('LineStyle', 'none', ...
			'Marker', 'o', ...
			'Color', 'black', ...
			'EraseMode', 'xor');
		title(name);
	else
		h = a1;
		points = a2;
		nc = numcols(points);
		C = get(h, 'UserData');
		switch nargin,
		case 4,
			Tcam = a4;
			Tobj = a3;
		case 3,
			Tobj = a3;
			Tcam = eye(4);
		otherwise,
			Tobj = eye(4);
			Tcam = eye(4);
		end
		if nc == 3,
			% draw points
			uv = camera(C, points, Tobj, Tcam);
			ovar = uv;
			l = get(h, 'Children');
			set(l, 'Xdata', uv(:,1), 'Ydata', uv(:,2));
		elseif nc == 6,
			% draw lines
			uv_s = camera(C, points(:,1:3), Tobj, Tcam);
			uv_f = camera(C, points(:,4:6), Tobj, Tcam);
			ovar = [uv_s uv_f];
			for c = get(h, 'Children')',
				delete(c);
			end
			line([uv_s(:,1)'; uv_f(:,1)'], ...
				[uv_s(:,2)'; uv_f(:,2)'], ...
				'EraseMode', 'xor', ...
				'LineStyle', '-');
		else
			error('Points matrix should be 3 or 6 columns');
		end
	end
