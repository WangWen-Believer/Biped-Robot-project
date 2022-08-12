% Simscape(TM) Multibody(TM) version: 5.0

% This is a model data file derived from a Simscape Multibody Import XML file using the smimport function.
% The data in this file sets the block parameter values in an imported Simscape Multibody model.
% For more information on this file, see the smimport function help page in the Simscape Multibody documentation.
% You can modify numerical values, but avoid any other changes to this file.
% Do not add code to this file. Do not edit the physical units shown in comments.

%%%VariableName:smiData


%============= RigidTransform =============%

%Initialize the RigidTransform structure array by filling in null values.
smiData.RigidTransform(9).translation = [0.0 0.0 0.0];
smiData.RigidTransform(9).angle = 0.0;
smiData.RigidTransform(9).axis = [0.0 0.0 0.0];
smiData.RigidTransform(9).ID = '';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(1).translation = [0 0 19.999999999999989];  % mm
smiData.RigidTransform(1).angle = 1.6653345369377348e-16;  % rad
smiData.RigidTransform(1).axis = [-0 -1 0];
smiData.RigidTransform(1).ID = 'B[Steering_gear-2:-:Mechanical_2-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(2).translation = [-104.99999999999997 -1.4210854715202004e-14 -1.4210854715202004e-14];  % mm
smiData.RigidTransform(2).angle = 3.1415926535897927;  % rad
smiData.RigidTransform(2).axis = [-0 1 1.3877787807814454e-16];
smiData.RigidTransform(2).ID = 'F[Steering_gear-2:-:Mechanical_2-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(3).translation = [0 0 0];  % mm
smiData.RigidTransform(3).angle = 2.0943951023931953;  % rad
smiData.RigidTransform(3).axis = [-0.57735026918962584 -0.57735026918962584 -0.57735026918962584];
smiData.RigidTransform(3).ID = 'B[Mechanical_down1-1:-:Steering_gear-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(4).translation = [40.000000000000014 40.500000000000021 20];  % mm
smiData.RigidTransform(4).angle = 3.1415926535897931;  % rad
smiData.RigidTransform(4).axis = [0.70710678118654757 -0.70710678118654757 1.1102230246251565e-16];
smiData.RigidTransform(4).ID = 'F[Mechanical_down1-1:-:Steering_gear-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(5).translation = [29.999999999999993 -6.5 9.9999999999999947];  % mm
smiData.RigidTransform(5).angle = 2.0943951023931953;  % rad
smiData.RigidTransform(5).axis = [-0.57735026918962584 -0.57735026918962584 -0.57735026918962584];
smiData.RigidTransform(5).ID = 'B[Steering_gear-1:-:Mechanical_up-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(6).translation = [10.00000000000033 9.9999999999961471 47.000000000000007];  % mm
smiData.RigidTransform(6).angle = 3.1415926535897931;  % rad
smiData.RigidTransform(6).axis = [-1 -6.4378146172286308e-33 1.5111939268818093e-16];
smiData.RigidTransform(6).ID = 'F[Steering_gear-1:-:Mechanical_up-1]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(7).translation = [9.9999999999999805 63.249999999995701 92];  % mm
smiData.RigidTransform(7).angle = 2.0943951023931953;  % rad
smiData.RigidTransform(7).axis = [0.57735026918962584 -0.57735026918962584 0.57735026918962584];
smiData.RigidTransform(7).ID = 'B[Mechanical_up-1:-:Steering_gear-2]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(8).translation = [29.999999999999751 -34.79999999999955 10.000000000000263];  % mm
smiData.RigidTransform(8).angle = 2.0943951023931948;  % rad
smiData.RigidTransform(8).axis = [-0.57735026918962562 -0.5773502691896254 -0.5773502691896264];
smiData.RigidTransform(8).ID = 'F[Mechanical_up-1:-:Steering_gear-2]';

%Translation Method - Cartesian
%Rotation Method - Arbitrary Axis
smiData.RigidTransform(9).translation = [31.565099807529673 -140.02440736027782 -41.666853274991603];  % mm
smiData.RigidTransform(9).angle = 0;  % rad
smiData.RigidTransform(9).axis = [0 0 0];
smiData.RigidTransform(9).ID = 'RootGround[Mechanical_down1-1]';


%============= Solid =============%
%Center of Mass (CoM) %Moments of Inertia (MoI) %Product of Inertia (PoI)

%Initialize the Solid structure array by filling in null values.
smiData.Solid(4).mass = 0.0;
smiData.Solid(4).CoM = [0.0 0.0 0.0];
smiData.Solid(4).MoI = [0.0 0.0 0.0];
smiData.Solid(4).PoI = [0.0 0.0 0.0];
smiData.Solid(4).color = [0.0 0.0 0.0];
smiData.Solid(4).opacity = 0.0;
smiData.Solid(4).ID = '';

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(1).mass = 0.35388123925916748;  % kg
smiData.Solid(1).CoM = [-2.0672213112603073 0.73993158412362559 0.38496495600426506];  % in
smiData.Solid(1).MoI = [0.39421540878839695 1.8340530605419632 1.7378175113949084];  % kg*in^2
smiData.Solid(1).PoI = [0.0017552888954182611 7.3065115745790759e-06 -8.8255934582819962e-05];  % kg*in^2
smiData.Solid(1).color = [1 0.59999999999999998 0];
smiData.Solid(1).opacity = 1;
smiData.Solid(1).ID = 'Mechanical_2*:*默认';

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(2).mass = 0.17231370325263051;  % kg
smiData.Solid(2).CoM = [0.390140411567028 0.44736889324027335 2.9501120113583115];  % in
smiData.Solid(2).MoI = [0.38545567866683639 0.23408133014447782 0.34933295486600241];  % kg*in^2
smiData.Solid(2).PoI = [-0.0060183157749503008 -0.00057849701808370887 -5.5052174746495825e-05];  % kg*in^2
smiData.Solid(2).color = [1 0.59999999999999998 0];
smiData.Solid(2).opacity = 1;
smiData.Solid(2).ID = 'Mechanical_up*:*默认';

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(3).mass = 0.034054902991438166;  % kg
smiData.Solid(3).CoM = [0.80836046823907637 0.79309464376725547 0.39369750612129728];  % in
smiData.Solid(3).MoI = [0.01008097667456675 0.0087038067955549584 0.015347426681111172];  % kg*in^2
smiData.Solid(3).PoI = [-7.7624921452682584e-08 -2.126473110715128e-07 5.2995495050997507e-05];  % kg*in^2
smiData.Solid(3).color = [1 0.59999999999999998 0];
smiData.Solid(3).opacity = 1;
smiData.Solid(3).ID = 'Steering_gear*:*默认';

%Inertia Type - Custom
%Visual Properties - Simple
smiData.Solid(4).mass = 0.074256928095078556;  % kg
smiData.Solid(4).CoM = [0.52676213212225831 0.39374349076724924 0.42288773796655349];  % in
smiData.Solid(4).MoI = [0.12010627898418672 0.12752618473443239 0.18301639677432388];  % kg*in^2
smiData.Solid(4).PoI = [2.2368916396533597e-06 0.00048211848745449942 8.5890160158897882e-06];  % kg*in^2
smiData.Solid(4).color = [1 0.59999999999999998 0];
smiData.Solid(4).opacity = 1;
smiData.Solid(4).ID = 'Mechanical_down1*:*默认';


%============= Joint =============%
%X Revolute Primitive (Rx) %Y Revolute Primitive (Ry) %Z Revolute Primitive (Rz)
%X Prismatic Primitive (Px) %Y Prismatic Primitive (Py) %Z Prismatic Primitive (Pz) %Spherical Primitive (S)
%Constant Velocity Primitive (CV) %Lead Screw Primitive (LS)
%Position Target (Pos)

%Initialize the RevoluteJoint structure array by filling in null values.
smiData.RevoluteJoint(2).Rz.Pos = 0.0;
smiData.RevoluteJoint(2).ID = '';

smiData.RevoluteJoint(1).Rz.Pos = 164.25675267182606;  % deg
smiData.RevoluteJoint(1).ID = '[Steering_gear-1:-:Mechanical_up-1]';

smiData.RevoluteJoint(2).Rz.Pos = 136.00220165932078;  % deg
smiData.RevoluteJoint(2).ID = '[Mechanical_up-1:-:Steering_gear-2]';

