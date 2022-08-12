%STANFORD Load kinematic and dynamic data for Stanford arm
%
% Defines the object 'stanford' in the current workspace which describes the 
% kinematic and dynamic characterstics of the Stanford (Scheinman) arm.
%
% Kinematic data from "Modelling, Trajectory calculation and Servoing of 
% a computer controlled arm".  Stanford AIM-177.  Figure 2.3
% Dynamic data from "Robot manipulators: mathematics, programming and control"
% Paul 1981, Tables 6.4, 6.6
% 
% Note: gear ratios not currently known, though reflected armature inertia 
% is known, so gear ratios set to 1.
%
% Also define the vector qz which corresponds to the zero joint
% angle configuration.
%
% See also: ROBOT, PUMA560, PUMA560AKB, TWOLINK.

% $Log: stanford.m,v $
% Revision 1.2  2002/04/01 11:47:18  pic
% General cleanup of code: help comments, see also, copyright, remnant dh/dyn
% references, clarification of functions.
%
% $Revision: 1.2 $
% Copyright (C) 1990-2002, by Peter I. Corke

% alpha A	theta	D	sigma	m	rx	ry	rz	Ixx	Iyy	Izz	Ixy	Iyz	Ixz	Jm	G
stanford_dyn = [
-pi/2 0	0	0.412	0	9.29	0	.0175	-0.1105	0.276	0.255	0.071	0	0	0	0.953	1
pi/2 0	0	0.154	0	5.01	0	-1.054	0	0.108	0.018	0.100	0	0	0	2.193	1	
0 0	-pi/2	0	1	4.25	0	0	-6.447	2.51	2.51	0.006	0	0	0	0.782	1
-pi/2 0	0	0	0	1.08	0	0.092	-0.054	0.002	0.001	0.001	0	0	0	0.106	1
pi/2 0	0	0	0	0.63	0	0	0.566	0.003	0.003	0.0004	0	0	0	0.097	1
0 0	0	0.263	0	0.51	0	0	1.554	0.013	0.013	0.0003	0	0	0	0.020	1
];

qz = [0 0 0 0 0 0];

stanf = robot(stanford_dyn);
stanf.plotopt = {'workspace', [-2 2 -2 2 -2 2]};
stanf.name = 'Stanford arm';
