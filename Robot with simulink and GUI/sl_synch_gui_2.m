function varargout = sl_synch_gui_2(varargin)
% SL_SYNCH_GUI_2 M-file for sl_synch_gui_2.fig
%      SL_SYNCH_GUI_2, by itself, creates a new SL_SYNCH_GUI_2 or raises the existing
%      singleton*.
%
%      H = SL_SYNCH_GUI_2 returns the handle to a new SL_SYNCH_GUI_2 or the handle to
%      the existing singleton*.
%
%      SL_SYNCH_GUI_2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SL_SYNCH_GUI_2.M with the given input arguments.
%
%      SL_SYNCH_GUI_2('Property','Value',...) creates a new SL_SYNCH_GUI_2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before sl_synch_gui_2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to sl_synch_gui_2_OpeningFcn via varargin.
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

% Last Modified by GUIDE v2.5 22-Jan-2019 10:52:24

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @sl_synch_gui_2_OpeningFcn, ...
                   'gui_OutputFcn',  @sl_synch_gui_2_OutputFcn, ...
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


% --- Executes just before sl_synch_gui_2 is made visible.
function sl_synch_gui_2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure 处理图
% eventdata  reserved - to be defined in a future version of MATLAB 保留的
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to sl_synch_gui_2 (see VARARGIN)命令行参数

% Choose default command line output for sl_synch_gui_2  //synch-同步
handles.output = hObject;

% Update handles structure //更新
guidata(hObject, handles);

% UIWAIT makes sl_synch_gui_2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% Get the value of the manual switch and synch the GUI
%set_param(Object,ParameterName,Value,...ParameterNameN,ValueN)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         这个‘sw’的值在哪里
value = get_param([bdroot '/Manual Switch'],'sw');
if strcmp(value,'0')  % strcmp---Compare strings
    set(handles.checkbox_switch,'Value',0)                  %  set(H,Name,Value)             
else
    set(handles.checkbox_switch,'Value',1)
end

% Get the value of the gain edit box and synch the GUI
value = get_param([bdroot '/Gain'],'Gain');%读取Simulink
set(handles.edit_Gain,'String',value);    %给GUI赋值
%以上各部分是通过读取simulink中的block重点参数
% Set the value of the gain slider, with max/min of +10/-10
slider_position = max(0,min(1,(str2double(value) + 10)/20));
set(handles.slider_Gain,'Value',slider_position);
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
assignin('base','switch_hObject',handles.checkbox_switch)
assignin('base','gain_hObject',handles.edit_Gain)

%% 填充背景图片
ha=axes('units','normalized','position',[0 0 1 1]);
uistack(ha,'down')
II=imread('pic.jpg');
image(II)
colormap winter
set(ha,'handlevisibility','off','visible','off');


% --- Outputs from this function are returned to the command line.
function varargout = sl_synch_gui_2_OutputFcn(hObject, eventdata, handles) 
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
 set_param('sl_synch_2/Gain1','Gain_1',value);
set_param('sl_synch_2/Leftfoot_1','LF_1',value);
set_param('sl_synch_2/Leftfoot_2','LF_2',value);
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
     strRec = [strRec c];
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
