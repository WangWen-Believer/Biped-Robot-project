function qdd = sldyn(robot, u)
	n = robot.n;

	q = u(1:n);
	qd = u(n+1:2*n);
	tau = u(2*n+1:3*n);

	qdd = accel(robot, u(1:n), u(n+1:2*n), u(2*n+1:3*n));
