%FRICTION Compute friction torque on the LINK object
%
%	TAU = FRICTION(LINK, QD)
%
% Return the friction torque on the link moving at speed QD.  Depending
% on fields in the LINK object viscous and/or Coulomb friction
% are computed.
%
% SEE ALSO: ROBOT/FRICTION

% MOD HISTORY
% 3/99 modify to use on a LINK object
% $Log: friction.m,v $
% Revision 1.3  2002/04/14 10:20:15  pic
% Added see also line.
%
% Revision 1.2  2002/04/01 12:04:51  pic
% General tidyup, comments, clarification, copyright, RCS keys, etc.
%
% $Revision: 1.3 $

% Copyright (C) 1999-2002, by Peter I. Corke

function  tau = friction(l, qd)
	tau = 0.0;

	qd = qd(:);
	tau = l.B * qd;

	tau = tau + (qd > 0) * l.Tc(1) + (qd < 0) * l.Tc(2);
