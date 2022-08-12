%PERTURB Return robot object with perturbed dynamic parameters
%
%	ROBOT = PERTURB(ROBOT, P)
%
% Return a new robot object in which the dynamic parameters (link mass and
% inertia) have been perturbed.  The perturbation is multiplicative so that
% values are multiplied by random numbers in the interval (1-P) to (1+P).
%
% Useful for investigating the robustness of various model-based control 
% schemes.
%
% The name string of the perturbed robot is prefixed by 'P/'.
%

% MOD HISTORY
% $Log: perturb.m,v $
% Revision 1.1  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.1 $

% Copyright (C) 1999-2002, by Peter I. Corke

function  r2 = perturb(r, p)

	if nargin == 1,
		p = 0.1;	% 10 percent disturb by default
	end


	for i=1:r.n,
		l2{i} = r.link{i};
		s = (2*rand-1)*p + 1;
		l2{i}.m = l2{i}.m * s;
		s = (2*rand-1)*p + 1;
		l2{i}.I = l2{i}.I * s;
	end

	r2 = robot(r, l2);		% clone the robot
	r2.name = ['P/' r.name];
