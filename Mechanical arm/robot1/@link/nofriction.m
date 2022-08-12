%NOFRICTION Return link object with zero friction 
%
%	LINK = NOFRICTION(LINK)
%	LINK = NOFRICTION(LINK, 'all')
%
% Return the link object with Coulomb or all friction terms set to zero.
%
% See also: ROBOT/NOFRICTION

% MOD HISTORY
% $Log: nofriction.m,v $
% Revision 1.3  2002/04/01 12:04:20  pic
% Change argument, 'all' for all friction, else just Coulombic.
%
% $Revision: 1.3 $
% Copyright (C) 1999-2002, by Peter I. Corke

function  l2 = nofriction(l, only)

	l2 = link(l);

	if (nargin == 2) & strcmpi(only(1:3), 'all'),
		l2.B = 0;
	end
	l2.Tc = [0 0];
