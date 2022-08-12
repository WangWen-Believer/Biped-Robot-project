%VISJAC	Image feature Jacobian
%
%	J = VISJAC(UV, CAMDATA, Z)
%
% Return the image-feature Jacobian for point features whose coordinates
% (u,v) comprise rows of UV.  Z is a vector of the depth of each corresponding
% point with respect to the camera.  S is the pixel scale factor in m/pixel.
%
function J = visjac(uv, camdata, z)

	J = [];
	for i=1:numrows(uv),
		% convert pixel units to distances at the image plane

		% now do the Jacobian proper
		Jp = visjac_row(camdata, uv(i,:), z);

		% build up the image Jacobian
		J = [J; Jp];
	end

function J = visjac_row(camdata, uv, z)

	f = camdata(1);
	ax = camdata(2);	% pixels/m
	ay = camdata(3);	% pixels/m
	u0 = camdata(4);	% principal point in pixels
	v0 = camdata(5);	% principal point in pixels

	% convert pixel units to distances at the image plane
	uv_p = [1/ax 0 -u0/ax; 0 1/ay -v0/ay] * [uv(:) ; 1];
	u = uv_p(1);
	v = uv_p(2);

	% now do the Jacobian proper
	J = [f/z 0   -u/z  -u*v/f        (f^2+u^2)/f -v
	     0   f/z -v/z  -(f^2+v^2)/f  u*v/f        u];

	% convert to pixel unit velocities
	J = diag([ax ay]) * J;
