%SHOWLINK show all link parameters of ROBOT object
%
%	SHOWLINK(robot)
%
% Shows details of all link parameters for this robot object, including
% inertial parameters.
%
% See also: LINK/SHOWLINK, LINK.

% Copyright (C) 1999-2002, by Peter I. Corke

function showlink(r)

	l = r.link;
	for i=1:r.n,
		fprintf('Link %d------------------------\n', i);
		showlink(l{i});
	end
