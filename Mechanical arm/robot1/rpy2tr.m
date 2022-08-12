%RPY2TR Roll/pitch/yaw to homogenous transform
%
% 	TR = RPY2TR([R P Y])
%	TR = RPY2TR(R,P,Y)
%
% Returns a homogeneous tranformation for the specified roll/pitch/yaw angles.
% These correspond to rotations about the Z, Y, X axes respectively.
%
% See also: TR2RPY, EUL2TR

% $Log: rpy2tr.m,v $
% Revision 1.3  2002/04/14 11:00:30  pic
% Fixed error in axis rotation order.
%
% Revision 1.2  2002/04/01 11:47:16  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $
% Copyright (C) 1993-2002, by Peter I. Corke

function r = rpy2tr(roll, pitch, yaw)
        if length(roll) == 3,
                r = rotz(roll(1)) * roty(roll(2)) * rotx(roll(3));
        else
                r = rotz(roll) * roty(pitch) * rotx(yaw);
        end
