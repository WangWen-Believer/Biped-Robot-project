function blkStruct = slblocks
%SLBLOCKS Defines the block library for a specific Toolbox or Blockset.

%   Copyright 1986-2003 The MathWorks, Inc.
%   $Revision: 1.7.4.1 $  $Date: 2004/04/10 23:19:15 $

% Name of the subsystem which will show up in the SIMULINK Blocksets
% and Toolboxes subsystem.
blkStruct.Name = 'RTsync Blockset v1.0';

% The function that will be called when the user double-clicks on
% this icon.
blkStruct.OpenFcn = 'rtsynclib';

% End of blocks


