function varargout = Offline_simulation(varargin)
% OFFLINE_SIMULATION MATLAB code for Offline_simulation.fig
%      OFFLINE_SIMULATION, by itself, creates a new OFFLINE_SIMULATION or raises the existing
%      singleton*.
%
%      H = OFFLINE_SIMULATION returns the handle to a new OFFLINE_SIMULATION or the handle to
%      the existing singleton*.
%
%      OFFLINE_SIMULATION('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in OFFLINE_SIMULATION.M with the given input arguments.
%
%      OFFLINE_SIMULATION('Property','Value',...) creates a new OFFLINE_SIMULATION or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Offline_simulation_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Offline_simulation_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Offline_simulation

% Last Modified by GUIDE v2.5 02-Mar-2019 10:11:27

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Offline_simulation_OpeningFcn, ...
                   'gui_OutputFcn',  @Offline_simulation_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Offline_simulation is made visible.
function Offline_simulation_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Offline_simulation (see VARARGIN)

% Choose default command line output for Offline_simulation
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Offline_simulation wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Offline_simulation_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
