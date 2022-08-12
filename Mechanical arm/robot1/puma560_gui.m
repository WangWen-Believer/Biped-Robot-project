function varargout = puma560_gui(varargin)
% PUMA560_GUI M-file for puma560_gui.fig
%      PUMA560_GUI, by itself, creates a new PUMA560_GUI or raises the existing
%      singleton*.
%
%      H = PUMA560_GUI returns the handle to a new PUMA560_GUI or the handle to
%      the existing singleton*.
%
%      PUMA560_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PUMA560_GUI.M with the given input arguments.
%
%      PUMA560_GUI('Property','Value',...) creates a new PUMA560_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before puma560_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to puma560_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help puma560_gui

% Last Modified by GUIDE v2.5 08-Dec-2011 10:24:56

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @puma560_gui_OpeningFcn, ...%´´½¨º¯Êý¾ä±ú£¬handles
                   'gui_OutputFcn',  @puma560_gui_OutputFcn, ...
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


% --- Executes just before puma560_gui is made visible.
function puma560_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to puma560_gui (see VARARGIN)

% Choose default command line output for puma560_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes puma560_gui wait for user response (see UIRESUME)
% uiwait(handles.puma560_gui);


% --- Outputs from this function are returned to the command line.
function varargout = puma560_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbtn_transformation.
function pushbtn_transformation_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_transformation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_transformation_Callback(hObject, eventdata, handles)
% hObject    handle to menu_transformation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_axesTrans_Callback(hObject, eventdata, handles)
% hObject    handle to menu_axesTrans (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_axesRorate_Callback(hObject, eventdata, handles)
% hObject    handle to menu_axesRorate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_axesComp_Callback(hObject, eventdata, handles)
% hObject    handle to menu_axesComp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
