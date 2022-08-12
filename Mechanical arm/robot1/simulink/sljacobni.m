function x = sljacobn(dh, u)
	N = numrows(dh);
	x = inv(jacobn(dh, u(1:N))) * u((N+1):(N+6));
