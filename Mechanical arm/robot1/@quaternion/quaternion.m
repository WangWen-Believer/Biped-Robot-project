%QUATERNION Constructor for quaternion objects
% 
%	Q = QUATERNION([s v1 v2 v3])	from 4 elements
%	Q = QUATERNION(v, theta)	from vector plus angle
%	Q = QUATERNION(R)		from a 3x3 or 4x4 matrix
%	Q = QUATERNION(q)		from another quaternion
%
% All versions, except the first, are guaranteed to return a unit quaternion.
%
% A quaternion is a compact method of representing a 3D rotation that has
% computational advantages including speed and numerical robustness.
%
% A quaternion has 2 parts, a scalar s, and a vector v and is typically written
%
%	q = s <vx vy vz>
%
% A unit quaternion is one for which s^2+vx^2+vy^2+vz^2 = 1.
%
% A quaternion can be considered as a rotation about a vector in space where
%	q = cos (theta/2) sin(theta/2) <vx vy vz>
% where <vx vy vz> is a unit vector.
%
% Various functions such as INV, NORM, UNIT and PLOT are overloaded for
% quaternion objects.
%
% Arithmetic operators are also overloaded to allow quaternion multiplication,
% division, exponentiaton, and quaternion-vector multiplication (rotation).
%
% SEE ALSO: QUATERNION/SUBSREF, QUATERNION/PLOT

% CHANGES:
% 12/01	order of arguments to theta,v form, fix bug in same
% $Log: quaternion.m,v $
% Revision 1.6  2002/04/14 11:03:30  pic
% Mention overloaded functions and operators in the help info.
%
% Revision 1.5  2002/04/02 12:27:26  pic
% Remove remnant CVS clash tag.
%
% Revision 1.4  2002/04/01 12:06:48  pic
% General tidyup, help comments, copyright, see also, RCS keys.
%
% $Revision: 1.6 $
%
% Copyright (C) 1999-2002, by Peter I. Corke


function q = quaternion(a1, a2)


	if nargin == 0,
		q.v = [];
		q.s = [];
		q = class(q, 'quaternion');
	elseif isa(a1, 'quaternion')
%	Q = QUATERNION(q)		from another quaternion
		q = a1;
	elseif nargin == 1
		if all(size(a1) == [3 3])
%	Q = QUATERNION(R)		from a 3x3 or 4x4 matrix
			q = quaternion( tr2q(a1) );
		elseif all(size(a1) == [4 4])
			q = quaternion( tr2q(a1(1:3,1:3)) );
		elseif all(size(a1) == [1 4])
%	Q = QUATERNION([s v1 v2 v3])	from 4 elements
			q.s = a1(1);
			q.v = a1(2:4);
			q = class(q, 'quaternion');
		else
			error('unknown dimension of input');
		end
	elseif nargin == 2
%	Q = QUATERNION(v, theta)	from vector plus angle
		q = unit( quaternion( [cos(a2/2) sin(a2/2)*unit(a1(:).')]) );
	end

%TR2Q	Convert homogeneous transform to a unit-quaternion
%
%	Q = tr2q(T)
%
%	Return a unit quaternion corresponding to the rotational part of the
%	homogeneous transform T.
%
%	See also: Q2TR

%	Copyright (C) 1993 Peter Corke
function q = tr2q(t)
	qs = sqrt(trace(t)+1)/2.0;
	kx = t(3,2) - t(2,3);	% Oz - Ay
	ky = t(1,3) - t(3,1);	% Ax - Nz
	kz = t(2,1) - t(1,2);	% Ny - Ox

	if (t(1,1) >= t(2,2)) & (t(1,1) >= t(3,3)) 
		kx1 = t(1,1) - t(2,2) - t(3,3) + 1;	% Nx - Oy - Az + 1
		ky1 = t(2,1) + t(1,2);			% Ny + Ox
		kz1 = t(3,1) + t(1,3);			% Nz + Ax
		add = (kx >= 0);
	elseif (t(2,2) >= t(3,3))
		kx1 = t(2,1) + t(1,2);			% Ny + Ox
		ky1 = t(2,2) - t(1,1) - t(3,3) + 1;	% Oy - Nx - Az + 1
		kz1 = t(3,2) + t(2,3);			% Oz + Ay
		add = (ky >= 0);
	else
		kx1 = t(3,1) + t(1,3);			% Nz + Ax
		ky1 = t(3,2) + t(2,3);			% Oz + Ay
		kz1 = t(3,3) - t(1,1) - t(2,2) + 1;	% Az - Nx - Oy + 1
		add = (kz >= 0);
	end

	if add
		kx = kx + kx1;
		ky = ky + ky1;
		kz = kz + kz1;
	else
		kx = kx - kx1;
		ky = ky - ky1;
		kz = kz - kz1;
	end
	nm = norm([kx ky kz]);
	if nm == 0,
		q = quaternion([1 0 0 0]);
	else
		s = sqrt(1 - qs^2) / nm;
		qv = s*[kx ky kz];

		q = quaternion([qs qv]);

	end
