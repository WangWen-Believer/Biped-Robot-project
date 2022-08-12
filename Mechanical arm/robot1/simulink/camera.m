%CAMERA	 Camera imaging model
%
%	uv = CAMERA(C, p)
%	uv = CAMERA(C, p, T)
%
%	Implement the perspective, scaling and offset encapsulated in the
%	camera calibration matrix C.  P is a list of 3D world points and
%	the corresponding image plane points are returned in UV.
%	The data in P is one point per row in X, Y, Z order.
%
%       T is a homogeneous transformation of the object coordinate frame
%	wrt to the camera coordinate frame, and can be used to transform
%	the points prior to imaging.
%
% SEE ALSO:	gcamera, camcalp, pulnix
%
%	Copyright (c) Peter Corke, 1999  Machine Vision Toolbox for Matlab

%	pic 1993
function uv = camera(C, p, Tobj, Tcam)

	np = numrows(p);

	% do the camera perspective transform
		
	p = [p'; ones(1, np)];

	% optionally transform all the points
	switch nargin,
		case 3,
			Tcam =  eye(4,4);
		case 2,
			Tcam =  eye(4,4);
			Tobj = eye(4,4);
	end
	p = inv(Tcam)*Tobj * p;

	x = C * p;		% camera transform
	iXY = x(1:2,:) ./ [x(3,:); x(3,:)];
	uv = iXY';
