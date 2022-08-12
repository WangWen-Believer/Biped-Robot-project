%NOFRICTION Return robot object with zero link friction 
%
%	ROBOT = NOFRICTION(ROBOT)
%
% Return the robot object but with non-linear friction coefficients set to
% zero.  
%
% 	ROBOT = NOFRICTION(ROBOT, 'all')
%
% Return the robot object but with all friction coefficients set to zero.  
%
% Non-linear (Coulomb) friction can cause numerical problems when integrating
% the equations of motion (FDYN).
%
% The resulting robot object has its name string modified by prepending 'NF/'.
%
% See also: LINK/NOFRICTION

% MOD HISTORY
% $Log: nofriction.m,v $
% Revision 1.3  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.3 $

% Copyright (C) 1999-2002, by Peter I. Corke

function  r2 = nofriction(r, varargin)

	r2 = robot(r);

	for i=1:r2.n,
		l2{i} = nofriction(r.link{i}, varargin{:});
	end

	r2.link = l2;
	r2.name = ['NF/' r.name];
