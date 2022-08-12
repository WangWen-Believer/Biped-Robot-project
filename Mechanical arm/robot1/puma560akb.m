%PUMA560AKB Load kinematic and dynamic data for a Puma 560 manipulator
%
%	PUMA560AKB
%
% Defines the object 'p560m' in current workspace which describes the 
% kinematic and dynamic characterstics of a Unimation Puma 560 manipulator 
% modified DH conventions and using the data and conventions of:
%
%	Armstrong, Khatib and Burdick 1986.
%	"The Explicit Dynamic Model and Inertial Parameters of the Puma 560 Arm"
%
% Also define the vector qz which corresponds to the zero joint
% angle configuration, qr which is the vertical 'READY' configuration,
% and qstretch in which the arm is stretched out in the X direction.
%
% See also: ROBOT, PUMA560, STANFORD, TWOLINK.

% Copyright (C) 1993-2002, by Peter I. Corke
% CHANGES:
% 12/01	convert to object format
% $Log: puma560akb.m,v $
% Revision 1.3  2002/04/01 11:47:15  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.3 $

clear L
%            alpha   A     theta    D	sigma
L{1} = link([0       0       0       0       0], 'mod');
L{2} = link([-pi/2   0       0       0.2435  0], 'mod');
L{3} = link([0       0.4318  0       -0.0934 0], 'mod');
L{4} = link([pi/2    -0.0203 0       .4331   0], 'mod');
L{5} = link([-pi/2   0       0       0       0], 'mod');
L{6} = link([pi/2    0       0       0       0], 'mod');

L{1}.m = 0;
L{2}.m = 17.4;
L{3}.m = 4.8;
L{4}.m = 0.82;
L{5}.m = 0.34;
L{6}.m = .09;

%         rx      ry      rz
L{1}.r = [0   0	  0	];
L{2}.r = [0.068   0.006   -0.016];
L{3}.r = [0   -0.070  0.014 ];
L{4}.r = [0   0	  -0.019];
L{5}.r = [0   0	  0	];
L{6}.r = [0   0	  .032	];

%        Ixx     Iyy      Izz    Ixy     Iyz     Ixz
L{1}.I = [0   0	  0.35    0	  0	  0];
L{2}.I = [.13   .524    .539    0	  0	  0];
L{3}.I = [.066    .0125   .066    0   0	  0];
L{4}.I = [1.8e-3  1.8e-3  1.3e-3  0   0	  0];
L{5}.I = [.3e-3   .3e-3   .4e-3   0   0	  0];
L{6}.I = [.15e-3  .15e-3  .04e-3  0   0	  0];

L{1}.Jm =  291e-6;
L{2}.Jm =  409e-6;
L{3}.Jm =  299e-6;
L{4}.Jm =  35e-6;
L{5}.Jm =  35e-6;
L{6}.Jm =  35e-6;

L{1}.G =  -62.6111;
L{2}.G =  107.815;
L{3}.G =  -53.7063;
L{4}.G =  76.0364;
L{5}.G =  71.923;
L{6}.G =  76.686;

% viscous friction (motor referenced)
% unknown

% Coulomb friction (motor referenced)
% unknown

%
% some useful poses
%
qz = [0 0 0 0 0 0]; % zero angles, L shaped pose
qr = [0 -pi/2 pi/2 0 0 0]; % ready pose, arm up
qstretch = [0 0 pi/2 0 0 0]; % horizontal along x-axis

p560m = robot(L, 'Puma560-AKB', 'Unimation', 'AK&B');
clear L
