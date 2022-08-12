%EUL2TR Convert Euler angles to homogeneous transformation
%
% 	TR = EUL2TR([PHI THETA PSI])
% 	TR = EUL2TR(PHI, THETA, PSI)
%
% Returns a homogeneous tranformation for the specified Euler angles.  These 
% correspond to rotations about the Z, Y, Z axes respectively.
%
% See also: TR2EUL, RPY2TR

% $Log: eul2tr.m,v $
% Revision 1.4  2002/04/14 10:12:47  pic
% Change comment to reflect correct axis rotation sequence.
%
% Revision 1.3  2002/04/01 11:47:12  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.4 $
% Copyright (C) 1993-2002, by Peter I. Corke

function r = eul2tr(phi, theta, psi)
        if length(phi) == 3,
                r = rotz(phi(1)) * roty(phi(2)) * rotz(phi(3));
        else
                r = rotz(phi) * roty(theta) * rotz(psi);
        end
