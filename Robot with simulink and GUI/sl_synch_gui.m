function varargout = sl_synch_gui(varargin)
% SL_SYNCH_GUI M-file for sl_synch_gui.fig
%      SL_SYNCH_GUI, by itself, creates a new SL_SYNCH_GUI or raises the existing
%      singleton*.
%
%      H = SL_SYNCH_GUI returns the handle to a new SL_SYNCH_GUI or the handle to
%      the existing singleton*.
%
%      SL_SYNCH_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SL_SYNCH_GUI.M with the given input arguments.
%
%      SL_SYNCH_GUI('Property','Value',...) creates a new SL_SYNCH_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before sl_synch_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to sl_synch_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES
%
% Edited by Will Campbell, MathWorks Inc.
% will.campbell@mathworks.com
% January 7, 2010
% Copyright 2010 The MathWorks, Inc.

% Last Modified by GUIDE v2.5 04-Mar-2019 09:57:42

% Begin initialization code - DO NOT EDIT
gui_Singleton = 0;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @sl_synch_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @sl_synch_gui_OutputFcn, ...
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


% --- Executes just before sl_synch_gui is made visible.
function sl_synch_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure 处理图
% eventdata  reserved - to be defined in a future version of MATLAB 保留的
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to sl_synch_gui (see VARARGIN)命令行参数

% Choose default command line output for sl_synch_gui  //synch-同步
handles.output = hObject;

% Update handles structure //更新
guidata(hObject, handles);

% UIWAIT makes sl_synch_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% Get the value of the manual switch and synch the GUI
%set_param(Object,ParameterName,Value,...ParameterNameN,ValueN)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         

%以上各部分是通过读取simulink中的block重点参数
% Set the value of the gain slider, with max/min of +10/-10

%%%%%%%%%%%%%%
%初始化串口参数
hasData = false;%表征串口是否接收到数据
isShow = false;  	%表征是否正在进行数据显示，即是否正在执行函数dataDisp
strRec = '';%已接收的字符串
numRec = 0;    	%接收字符计数
numSend = 0;   	%发送字符计数
%将上述参数作为应用数据，存入窗口对象内
setappdata(hObject,'hasData',hasData);
setappdata(hObject, 'isShow', isShow);
setappdata(hObject,'strRec',strRec);
setappdata(hObject, 'numRec', numRec);
setappdata(hObject, 'numSend', numSend);

% Assign gui, startstop, switch, and gain handles to the base workspace
assignin('base','sl_synch_handles',handles)
assignin('base','startstop_hObject',handles.pushbutton_startstop)

Robot_data=zeros(23,1);
SD_551=xlsread('SD_5');
assignin('base','Robot_data',Robot_data)
assignin('base','SD_55',SD_551)

%% 填充背景图片



% --- Outputs from this function are returned to the command line.
function varargout = sl_synch_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton_startstop.
function pushbutton_startstop_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_startstop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%配置Simulink仿真选项，使其使用当前工作空间
%设置 Simulink从当前工作空间运行
options = simset('SrcWorkspace','current'); %设置matlab和simulink共用相同的工作空间

mystring = get(hObject,'String');
status = get_param(bdroot,'simulationstatus');
if strcmp(mystring,'Start Simulation')
    
    % Check the status of the simulation and start it if it's stopped
    if strcmp(status,'stopped')
        set_param(bdroot,'simulationcommand','start')
    end
    
    % Update the string on the pushbutton
    set(handles.pushbutton_startstop,'String','Stop Simulation')
    
elseif strcmp(mystring,'Stop Simulation')
    
    % Check the status of the simulation and stop it if it's running
    if strcmp(status,'running')
        set_param(bdroot, 'SimulationCommand', 'Stop')
    end
    
    % Update the string on the pushbutton
    set(handles.pushbutton_startstop,'String','Start Simulation')
    
else
    warning('Unrecognized string for pushbutton_startstop') %#ok<WNTAG>
end

% Assign handles and the startstop object to the base workspace
assignin('base','sl_synch_handles',handles)
assignin('base','startstop_hObject',handles.pushbutton_startstop)


% --- Executes on button press in checkbox_switch.
function checkbox_switch_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_switch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_switch

value = get(hObject,'Value');

if value == 0
    set_param([bdroot '/Manual Switch'],'sw','0')
else
    set_param([bdroot '/Manual Switch'],'sw','1')
end

% Assign handles and the switch object to the base workspace
assignin('base','sl_synch_handles',handles)
assignin('base','switch_hObject',handles.checkbox_switch)



function edit_Gain_Callback(hObject, eventdata, handles)
% hObject    handle to edit_Gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_Gain as text
%        str2double(get(hObject,'String')) returns contents of edit_Gain as a double

value = get(hObject,'String');

% Update the model's gain value
set_param([bdroot '/Gain'],'Gain',value)

% Set the value of the gain slider, with max/min of +10/-10
slider_position = max(0,min(1,(str2double(value) + 10)/20));
set(handles.slider_Gain,'Value',slider_position);

% Update simulation if the model is running
status = get_param(bdroot,'simulationstatus');
if strcmp(status,'running')
    set_param(bdroot, 'SimulationCommand', 'Update')
end

% --- Executes during object creation, after setting all properties.
function edit_Gain_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_Gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider_Gain_Callback(hObject, eventdata, handles)
% hObject    handle to slider_Gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get the value of the gain slider and determine what the gain value should be
slider_position = get(hObject,'Value');
value = num2str(slider_position*20 - 10);

% Update the model's gain value
%% 特别重要这里     set_param();
set_param([bdroot '/Gain'],'Gain',value)
% set_param('sl_synch/Gain1','Gain_1',value);
% set_param('sl_synch/Leftfoot_1','LF_1',value);
% set_param('sl_synch/Leftfoot_2','LF_2',value);
% set_param('sl_synch/Leftfoot_3','LF_3',value);

% Set the value of the gain edit box
set(handles.edit_Gain,'String',value);

% % Update simulation if the model is running
% status = get_param(bdroot,'simulationstatus');
% if strcmp(status,'running')
%     set_param(bdroot, 'SimulationCommand', 'Update')
% end

% --- Executes during object creation, after setting all properties.
function slider_Gain_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_Gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on key press with focus on checkbox_switch and none of its controls.
function checkbox_switch_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to checkbox_switch (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Open_serial.
function Open_serial_Callback(hObject, eventdata, handles)
% hObject    handle to Open_serial (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
mystring = get(hObject,'String');
if get(hObject, 'value')
    str_com=get(handles.Serial_interface,'String');
    val_com=get(handles.Serial_interface,'Value');
    str_rate=get(handles.Baud_rate,'String');
    val_rate=get(handles.Baud_rate,'Value');
    switch val_com
        case 1 
        com_n=str_com{1};
        case 2 
        com_n=str_com{2};
        case 3
        com_n=str_com{3};
        case 4
        com_n=str_com{4} ;       
    end
        switch val_rate
        case 1 
        baud_rate=str2num(str_rate{1});
        case 2 
        baud_rate=str2num(str_rate{2});
        case 3
        baud_rate=str2num(str_rate{3});
        end
    set(handles.Open_serial,'String','关闭串口');
    jiaoyan='none';%无校验位
    data_bits=8;%数据位个数
    stop_bits = 1;
    scom=serial(com_n);%创建串口对象
    %配置串口属性，指定其回调函数
    set(scom, 'BaudRate', baud_rate, 'Parity', jiaoyan, 'DataBits',...
        data_bits, 'StopBits', stop_bits, 'BytesAvailableFcnCount', 10,...
        'BytesAvailableFcnMode', 'byte', 'BytesAvailableFcn', {@bytes, handles},...
        'TimerPeriod', 0.05, 'timerfcn', {@dataDisp, handles});
  
% elseif strcmp(mystring,'关闭串口')  
% %      baud_rate=get(handles.Baud_rate,'Sting')
% %     set(handles.xianshi,'String',baud_rate);
%     set(handles.Open_serial,'String','打开串口');
% end  
    %% 将串口对象的句柄作为用户数据，存入窗口对象
    set(handles.figure1, 'UserData', scom);
    %% 尝试打开串口
    try
        fopen(scom);  %打开串口
    catch   % 若串口打开失败，提示“串口不可获得！”
        msgbox('串口不可获得！');
        set(hObject, 'value', 0);  %弹起本按钮 
        return;
    end
   %% 打开串口后，允许串口发送数据，清空接收显示区，点亮串口状态指示灯，
    set(handles.xianshi, 'string', ''); 			%清空接收显示区
    set(hObject, 'String', '关闭串口');  		%设置本按钮文本为“关闭串口”
else  %若关闭串口
    %% 停止并删除定时器
    t = timerfind;
    if ~isempty(t)
        stop(t);
        delete(t);
    end    
    %% 停止并删除串口对象
    scoms = instrfind;
    stopasync(scoms);
    fclose(scoms);
    delete(scoms);
    set(hObject, 'String', '打开串口');  		%设置本按钮文本为“打开串口”
end   

function dataDisp(obj, event, handles)
%	串口的TimerFcn回调函数
%   串口数据显示
%% 获取参数
hasData = getappdata(handles.figure1, 'hasData'); %串口是否收到数据
strRec = getappdata(handles.figure1, 'strRec');   %串口数据的字符串形式，定时显示该数据
numRec = getappdata(handles.figure1, 'numRec');   %串口接收到的数据个数
%% 若串口没有接收到数据，先尝试接收串口数据
if ~hasData
    bytes(obj, event, handles);
end
%% 若串口有数据，显示串口数据
if hasData
    %% 给数据显示模块加互斥锁
    %% 在执行显示数据模块时，不接受串口数据，即不执行BytesAvailableFcn回调函数
    setappdata(handles.figure1, 'isShow', true); 
    %% 若要显示的字符串长度超过10000，清空显示区
    if length(strRec) > 10000
        setappdata(handles.figure1, 'strRec', strRec);
    end
    %% 显示数据     &&解析数据包
    set(handles.xianshi, 'string', strRec);
    %% 解析数据包
    Robot_data=sscanf(strRec,'%f');
    assignin('base','Robot_data',Robot_data)
    number=length(Robot_data);
    assignin('base','number',number) 
    if number>20  
    set_param([bdroot '/ROBOT_1'],'Gain','Robot_data(1)')
    set_param([bdroot '/ROBOT_2'],'Gain','Robot_data(2)')
    set_param([bdroot '/ROBOT_3'],'Gain','Robot_data(3)')
    set_param([bdroot '/ROBOT_4'],'Gain','Robot_data(4)')
    set_param([bdroot '/ROBOT_5'],'Gain','Robot_data(5)')
    set_param([bdroot '/ROBOT_6'],'Gain','Robot_data(6)')
    set_param([bdroot '/ROBOT_7'],'Gain','Robot_data(7)')
    set_param([bdroot '/ROBOT_8'],'Gain','Robot_data(8)')
    set_param([bdroot '/ROBOT_9'],'Gain','Robot_data(9)')
    set_param([bdroot '/ROBOT_10'],'Gain','Robot_data(10)')
    set_param([bdroot '/ROBOT_11'],'Gain','Robot_data(11)')
    set_param([bdroot '/ROBOT_12'],'Gain','Robot_data(12)')
    set_param([bdroot '/ROBOT_13'],'Gain','Robot_data(13)')
    set_param([bdroot '/ROBOT_14'],'Gain','Robot_data(14)')
    set_param([bdroot '/ROBOT_15'],'Gain','Robot_data(15)')
    set_param([bdroot '/ROBOT_16'],'Gain','Robot_data(16)')
    set_param([bdroot '/ROBOT_17'],'Gain','Robot_data(17)')
    set_param([bdroot '/ROBOT_18'],'Gain','Robot_data(18)')
    set_param([bdroot '/ROBOT_19'],'Gain','Robot_data(19)')
    set_param([bdroot '/ROBOT_20'],'Gain','Robot_data(20)')
    set_param([bdroot '/ROBOT_21'],'Gain','Robot_data(21)')
    set_param([bdroot '/ROBOT_22'],'Gain','Robot_data(22)')
    set_param([bdroot '/ROBOT_23'],'Gain','Robot_data(23)')
    end 
    
    %% 更新接收计数
    set(handles.rec,'string', numRec);
    %% 更新hasData标志，表明串口数据已经显示
    setappdata(handles.figure1, 'hasData', false);
    %% 给数据显示模块解锁
    setappdata(handles.figure1, 'isShow', false);
end    

 
function bytes(obj, ~, handles)
%   串口的BytesAvailableFcn回调函数
%   串口接收数据
%% 获取参数
strRec = getappdata(handles.figure1, 'strRec'); %获取串口要显示的数据
numRec = getappdata(handles.figure1, 'numRec'); %获取串口已接收数据的个数
isShow = getappdata(handles.figure1, 'isShow');  %是否正在执行显示数据操作
%% 若正在执行数据显示操作，暂不接收串口数据
if isShow
    return;
end
%% 获取串口可获取的数据个数
n = get(obj, 'BytesAvailable');
%% 若串口有数据，接收所有数据
if n
    %% 更新hasData参数，表明串口有数据需要显示
    setappdata(handles.figure1, 'hasData', true);
    %% 读取串口数据
    a = fread(obj, n, 'uchar');
    %% 解析数据为要显示的字符串
     c = char(a');
    %% 更新已接收的数据个数
     numRec = numRec + size(a, 1);
    %% 更新要显示的字符串
    %解析数据包
    % package(c ,num);
     strRec = c;
    %% 更新参数
    setappdata(handles.figure1, 'numRec', numRec); %更新已接收的数据个数
    setappdata(handles.figure1, 'strRec', strRec); %更新要显示的字符串
end













    
    
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% --- Executes on selection change in Serial_interface.
function Serial_interface_Callback(hObject, eventdata, handles)
% hObject    handle to Serial_interface (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Serial_interface contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Serial_interface


% --- Executes during object creation, after setting all properties.
function Serial_interface_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Serial_interface (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Baud_rate.
function Baud_rate_Callback(hObject, eventdata, handles)
% hObject    handle to Baud_rate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
val_baud=get(hObject,'value');
% Hints: contents = cellstr(get(hObject,'String')) returns Baud_rate contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Baud_rate


% --- Executes during object creation, after setting all properties.
function Baud_rate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Baud_rate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in xianshi.
function xianshi_Callback(hObject, eventdata, handles)
% hObject    handle to xianshi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns xianshi contents as cell array
%        contents{get(hObject,'Value')} returns selected item from xianshi


% --- Executes during object creation, after setting all properties.
function xianshi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to xianshi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function rec_Callback(hObject, eventdata, handles)
% hObject    handle to rec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rec as text
%        str2double(get(hObject,'String')) returns contents of rec as a double


% --- Executes during object creation, after setting all properties.
function rec_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function trans_Callback(hObject, eventdata, handles)
% hObject    handle to trans (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of trans as text
%        str2double(get(hObject,'String')) returns contents of trans as a double


% --- Executes during object creation, after setting all properties.
function trans_CreateFcn(hObject, eventdata, handles)
% hObject    handle to trans (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Sit_down.
function Sit_down_Callback(hObject, eventdata, handles)
% hObject    handle to Sit_down (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Sit_down';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on button press in Stand_up.
function Stand_up_Callback(hObject, eventdata, handles)
% hObject    handle to Stand_up (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Stand_up';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on button press in Go_up.
function Go_up_Callback(hObject, eventdata, handles)
% hObject    handle to Go_up (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Go_up';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on selection change in sends.
function sends_Callback(hObject, eventdata, handles)
% hObject    handle to sends (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sends contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sends


% --- Executes during object creation, after setting all properties.
function sends_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sends (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Rest_position.
function Rest_position_Callback(hObject, eventdata, handles)
% hObject    handle to Rest_position (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Rest_position';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on button press in Dancing.
function Dancing_Callback(hObject, eventdata, handles)
% hObject    handle to Dancing (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Dancing';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on button press in Singing.
function Singing_Callback(hObject, eventdata, handles)
% hObject    handle to Singing (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Singing';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end

% --- Executes on button press in Stop.
function Stop_Callback(hObject, eventdata, handles)
% hObject    handle to Stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scom = get(handles.figure1, 'UserData');
val = 'Stop';
str = get(scom, 'TransferStatus');
if ~(strcmp(str, 'write') || strcmp(str, 'read&write'))
     fwrite(scom, val, 'uint8', 'async'); %数据写入串口
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_2k_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2k (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_3_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_6_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Realtime_detection_Callback(hObject, eventdata, handles)
% hObject    handle to Realtime_detection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Offline_simulation_Callback(hObject, eventdata, handles)
% hObject    handle to Offline_simulation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% h=Offline_simulation;


% --- Executes on button press in pushbutton16.
function pushbutton16_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton17.
function pushbutton17_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton18.
function pushbutton18_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    set_param([bdroot '/ROBOT_1'],'Gain','Robot_data(1)')
    set_param([bdroot '/ROBOT_2'],'Gain','Robot_data(2)')
    set_param([bdroot '/ROBOT_3'],'Gain','Robot_data(3)')
    set_param([bdroot '/ROBOT_4'],'Gain','Robot_data(4)')
    set_param([bdroot '/ROBOT_5'],'Gain','Robot_data(5)')
    set_param([bdroot '/ROBOT_6'],'Gain','Robot_data(6)')
    set_param([bdroot '/ROBOT_7'],'Gain','Robot_data(7)')
    set_param([bdroot '/ROBOT_8'],'Gain','Robot_data(8)')
    set_param([bdroot '/ROBOT_9'],'Gain','Robot_data(9)')
    set_param([bdroot '/ROBOT_10'],'Gain','Robot_data(10)')
    set_param([bdroot '/ROBOT_11'],'Gain','Robot_data(11)')
    set_param([bdroot '/ROBOT_12'],'Gain','Robot_data(12)')
    set_param([bdroot '/ROBOT_13'],'Gain','Robot_data(13)')
    set_param([bdroot '/ROBOT_14'],'Gain','Robot_data(14)')
    set_param([bdroot '/ROBOT_15'],'Gain','Robot_data(15)')
    set_param([bdroot '/ROBOT_16'],'Gain','Robot_data(16)')
    set_param([bdroot '/ROBOT_17'],'Gain','Robot_data(17)')
    set_param([bdroot '/ROBOT_18'],'Gain','Robot_data(18)')
    set_param([bdroot '/ROBOT_19'],'Gain','Robot_data(19)')
    set_param([bdroot '/ROBOT_20'],'Gain','Robot_data(20)')
    set_param([bdroot '/ROBOT_21'],'Gain','Robot_data(21)')
    set_param([bdroot '/ROBOT_22'],'Gain','Robot_data(22)')
    set_param([bdroot '/ROBOT_23'],'Gain','Robot_data(23)')
    
    set(handles.Robot20,'Value',0);
    set(handles.Robot11,'Value',0);
    set(handles.Robot10,'Value',0);
    set(handles.Robot12,'Value',0);
    set(handles.Robot9,'Value',0);
    set(handles.Robot4,'Value',0);
    
    
    

% --- Executes on button press in pushbutton19.
function pushbutton19_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton20.
function pushbutton20_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton21.
function pushbutton21_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% global SD_123
% SD_123=xlsread('SD_5');
% assignin('base','SD_123',SD_123)
USART.port='COM20';
USART.PropertyName='BaudRate';
USART.PropertyValue=128000;
obj=serial(USART.port,USART.PropertyName,USART.PropertyValue);
SD_1=xlsread('SD_1');SD_2=xlsread('SD_2');SD_3=xlsread('SD_3');SD_4=xlsread('SD_4');
SD_5=xlsread('SD_5');SD_6=xlsread('SD_6');SD_7=xlsread('SD_7');SD_8=xlsread('SD_8');
SD_9=xlsread('SD_9');SD_10=xlsread('SD_10');SD_11=xlsread('SD_11');SD_12=xlsread('SD_12');
SD_13=xlsread('SD_13');SD_14=xlsread('SD_14');SD_15=xlsread('SD_15');SD_16=xlsread('SD_16');
SD_17=xlsread('SD_17');SD_18=xlsread('SD_18');SD_19=xlsread('SD_19');SD_20=xlsread('SD_20');
SD_21=xlsread('SD_21');SD_22=xlsread('SD_22');SD_23=xlsread('SD_23');


fopen(obj);
Gait_go(obj,SD_1,SD_2,SD_3,SD_4,SD_5,SD_6,SD_7,SD_8,SD_9,SD_10,SD_11,SD_12,SD_13,SD_14,SD_15,SD_16,SD_17,SD_18,SD_19,SD_20,SD_21,SD_22,SD_23)
fclose(obj);
% --- Executes on button press in pushbutton22.
function pushbutton22_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function Robot5_Callback(hObject, eventdata, handles)
% hObject    handle to Robot5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_5'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot10_Callback(hObject, eventdata, handles)
% hObject    handle to Robot10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_10'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot4_Callback(hObject, eventdata, handles)
% hObject    handle to Robot4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_4'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot12_Callback(hObject, eventdata, handles)
% hObject    handle to Robot12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_12'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot11_Callback(hObject, eventdata, handles)
% hObject    handle to Robot11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_11'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot16_Callback(hObject, eventdata, handles)
% hObject    handle to Robot16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_16'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot16_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot9_Callback(hObject, eventdata, handles)
% hObject    handle to Robot9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_9'],'Gain',value);

% --- Executes during object creation, after setting all properties.
function Robot9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Robot20_Callback(hObject, eventdata, handles)
% hObject    handle to Robot20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
slider_position = get(hObject,'Value');
value = num2str(slider_position*90);
set_param([bdroot '/ROBOT_20'],'Gain',value);



% --- Executes during object creation, after setting all properties.
function Robot20_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Robot20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton23.
function pushbutton23_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function oneline_CreateFcn(hObject, eventdata, handles)
% hObject    handle to oneline (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% handles.output=hObject;
% tu_biao=importdata('pic.jpg');
% set(handles.oneline,'CDATA',tu_biao);
% guidata(hObject,handles)



% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
ha=axes('units','normalized','position',[0 0 1 1]);
uistack(ha,'down')
II=imread('pic.jpg');
image(II)
colormap winter

strCell ={'机器人线上仿真系统平台'};
for i =1:numel(strCell)  %
    strTemp = strCell{i};
    str=[strTemp;10*ones(1,length(strTemp))];
    str=str(:)';
    text('string',str,'position',[350-60*i 560],'Horizontal','center',...
        'FontName','华文楷体','FontSize',17,'FontWeight','bold','Color','cyan');
end   
    set(ha,'handlevisibility','off','visible','on');

% --- Executes on button press in togglebutton5.
function togglebutton5_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton5


% --- Executes on selection change in popupmenu5.
function popupmenu5_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu5 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu5


% --- Executes during object creation, after setting all properties.
function popupmenu5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu6.
function popupmenu6_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu6 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu6


% --- Executes during object creation, after setting all properties.
function popupmenu6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in listbox6.
function listbox6_Callback(hObject, eventdata, handles)
% hObject    handle to listbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox6 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox6


% --- Executes during object creation, after setting all properties.
function listbox6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit12 as text
%        str2double(get(hObject,'String')) returns contents of edit12 as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit13_Callback(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit13 as text
%        str2double(get(hObject,'String')) returns contents of edit13 as a double


% --- Executes during object creation, after setting all properties.
function edit13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton25.
function pushbutton25_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton25 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton26.
function pushbutton26_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton26 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton27.
function pushbutton27_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in listbox7.
function listbox7_Callback(hObject, eventdata, handles)
% hObject    handle to listbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox7 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox7


% --- Executes during object creation, after setting all properties.
function listbox7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton28.
function pushbutton28_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton29.
function pushbutton29_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton29 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton30.
function pushbutton30_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton30 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton31.
function pushbutton31_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit14_Callback(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit14 as text
%        str2double(get(hObject,'String')) returns contents of edit14 as a double


% --- Executes during object creation, after setting all properties.
function edit14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit15_Callback(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit15 as text
%        str2double(get(hObject,'String')) returns contents of edit15 as a double


% --- Executes during object creation, after setting all properties.
function edit15_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit16_Callback(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit16 as text
%        str2double(get(hObject,'String')) returns contents of edit16 as a double


% --- Executes during object creation, after setting all properties.
function edit16_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit17_Callback(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit17 as text
%        str2double(get(hObject,'String')) returns contents of edit17 as a double


% --- Executes during object creation, after setting all properties.
function edit17_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu7.
function popupmenu7_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu7 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu7


% --- Executes during object creation, after setting all properties.
function popupmenu7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function text27_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes during object creation, after setting all properties.
function offline_CreateFcn(hObject, eventdata, handles)
% hObject    handle to offline (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --------------------------------------------------------------------
function Download_Callback(hObject, eventdata, handles)
% hObject    handle to Download (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
run('DataDownload')
close('sl_synch_gui')
% set(figure1,'visible','off')


% --------------------------------------------------------------------
function Analog_Callback(hObject, eventdata, handles)
% hObject    handle to Analog (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
run('Analog_Simulation')
close('sl_synch_gui')


% --- Executes on button press in pushbutton32.
function pushbutton32_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton33.
function pushbutton33_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton34.
function pushbutton34_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton35.
function pushbutton35_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton35 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton36.
function pushbutton36_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton36 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton37.
function pushbutton37_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton37 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton38.
function pushbutton38_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider32_Callback(hObject, eventdata, handles)
% hObject    handle to slider32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider32_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider33_Callback(hObject, eventdata, handles)
% hObject    handle to slider33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider33_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider34_Callback(hObject, eventdata, handles)
% hObject    handle to slider34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider34_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider35_Callback(hObject, eventdata, handles)
% hObject    handle to slider35 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider35_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider35 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider36_Callback(hObject, eventdata, handles)
% hObject    handle to slider36 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider36_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider36 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider37_Callback(hObject, eventdata, handles)
% hObject    handle to slider37 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider37_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider37 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider38_Callback(hObject, eventdata, handles)
% hObject    handle to slider38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider38_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider39_Callback(hObject, eventdata, handles)
% hObject    handle to slider39 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider39_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider39 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton39.
function pushbutton39_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton39 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_4_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in Download_Switch.
function Download_Switch_Callback(hObject, eventdata, handles)
% hObject    handle to Download_Switch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Download_Switch contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Download_Switch


% --- Executes during object creation, after setting all properties.
function Download_Switch_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Download_Switch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Download_Go.
function Download_Go_Callback(hObject, eventdata, handles)
% hObject    handle to Download_Go (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton42.
function pushbutton42_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton42 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_5_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Download_Data.
function Download_Data_Callback(hObject, eventdata, handles)
% hObject    handle to Download_Data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
mystring = get(hObject,'String');
if strcmp(mystring,'Download')   
    % Update the string on the pushbutton
    set(handles.Download_Data,'String','Stop Download')
    set(handles.uipanel6,'visible','on');
elseif strcmp(mystring,'Stop Download')
    % Update the string on the pushbutton
    set(handles.Download_Data,'String','Download')
    set(handles.uipanel6,'visible','off');
end
