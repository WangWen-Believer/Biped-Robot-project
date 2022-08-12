function varargout = puma560_control(varargin)
% PUMA560_CONTROL M-file for puma560_control.fig
%      PUMA560_CONTROL, by itself, creates a new PUMA560_CONTROL or raises the existing
%      singleton*.
%
%      H = PUMA560_CONTROL returns the handle to a new PUMA560_CONTROL or the handle to
%      the existing singleton*.
%
%      PUMA560_CONTROL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PUMA560_CONTROL.M with the given input arguments.
%
%      PUMA560_CONTROL('Property','Value',...) creates a new PUMA560_CONTROL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before puma560_control_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to puma560_control_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help puma560_control

% Last Modified by GUIDE v2.5 08-Dec-2011 10:24:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @puma560_control_OpeningFcn, ...
                   'gui_OutputFcn',  @puma560_control_OutputFcn, ...
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


% --- Executes just before puma560_control is made visible.
function puma560_control_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to puma560_control (see VARARGIN)

% Choose default command line output for puma560_control
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes puma560_control wait for user response (see UIRESUME)
% uiwait(handles.puma560_control);
%初始化程序
puma_gui=findobj('Tag','puma560_gui');
if ~isempty(puma_gui),
    %存在PUMA560演示窗口
else
    %不存在PUMA560演示窗口
    uiwait(msgbox('您还没有打开PUMA560演示窗口。程序将自动为您打开！','提示'));
    puma560_gui();
end


% --- Outputs from this function are returned to the command line.
function varargout = puma560_control_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbtn_yunZ.
function pushbtn_yunZ_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_yunZ (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%运动学正问题
% Forward kinematics is the problem of solving the Cartesian position and 
% orientation of a mechanism given knowledge of the kinematic structure and 
% the joint coordinates.
close(findobj('tag','puma560_gui'));
prompt={'输入时间向量t：','输入起始点坐标:','输入终止点坐标：'};%创建一个初始化对话框
name='参数：';
numlines=1;%对话框中输入框的行数，当为2的时候，输入框可以换行的
defaultanswer={'0:0.056:4','[0 0 0 0 0 0]','[0 pi/2 pi/2 0 -pi/2 0]'};%设置默认初始值
answer=inputdlg(prompt,name,numlines,defaultanswer);%读取对话框的默认初始值
if ~isempty(answer),%answer中返回了三个输入框中数据
    t=str2num(answer{1});
    qz=str2num(answer{2});
    qr=str2num(answer{3});
end
eval('puma560');
figure('Name','PUMA560机器人仿真演示窗口---运动学正问题');
grid on;
q=jtraj(qz,qr,t);
T=fkine(p560,q);              %正运动学求解
subplot(3,1,1);
plot(t, squeeze(T(1,4,:)));%画X方向的
xlabel('Time (s)');
ylabel('X (m)');
grid on;
subplot(3,1,2);
plot(t, squeeze(T(2,4,:)));%画Y方向的
xlabel('Time (s)');
ylabel('Y (m)');
grid on;
subplot(3,1,3);
plot(t, squeeze(T(3,4,:)));%画Z方向的
grid on;
xlabel('Time (s)');
ylabel('Z (m)');

puma_gui=puma560_gui();%动态演示
puma_gui=guihandles(puma_gui);
axes(puma_gui.axes1);
plot(p560,q);
grid on;
hold on;
x=squeeze(T(1,4,:));
y=squeeze(T(2,4,:));
z=squeeze(T(3,4,:));
figure('Name','PUMA560机器人仿真演示窗口---运动学正问题');
plot3(x,y,z);
grid on


% --- Executes on button press in pushbtn_yunN.
function pushbtn_yunN_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_yunN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%运动学逆问题
% Inverse kinematics is the problem of finding the robot joint coordinates,
% given a homogeneous transform representing the last link of the manipulator.
% It is very useful when the path is planned in Cartesian space, for instance 
% a straight line path as shown in the trajectory demonstration.
eval('puma560');
close(findobj('tag','puma560_gui'));
prompt={'输入时间向量：','输入起始点坐标:','输入终止点坐标：'};
name='参数：';
numlines=1;
defaultanswer={'0:0.056:2','transl(0.6,-0.5,0)','transl(0.4,0.5,0.2)'};
answer=inputdlg(prompt,name,numlines,defaultanswer);
if ~isempty(answer),
    t=str2num(answer{1});
    T1=str2num(answer{2});
    T2=str2num(answer{3});
end
T=ctraj(T1,T2,length(t));%每个点的坐标
q=ikine(p560,T);

figure('Name','PUMA560机器人仿真演示窗口---运动学逆问题');
subplot(3,2,1)
plot(t,q(:,1))
xlabel('Time (s)');
ylabel('Joint 1 (rad)')
subplot(3,2,2)
plot(t,q(:,2))
xlabel('Time (s)');
ylabel('Joint 2 (rad)')
subplot(3,2,3)
plot(t,q(:,3))
xlabel('Time (s)');
ylabel('Joint 3 (rad)')
subplot(3,2,4)
plot(t,q(:,4))
xlabel('Time (s)');
ylabel('Joint 4 (rad)')
subplot(3,2,5)
plot(t,q(:,5))
xlabel('Time (s)');
ylabel('Joint 5 (rad)')
subplot(3,2,6)
plot(t,q(:,6))
xlabel('Time (s)');
ylabel('Joint 6 (rad)')
eval('puma560');
puma_gui=guihandles(puma560_gui());
axes(puma_gui.axes1);
plot(p560,q);
grid on

% --- Executes on button press in pushbtn_dongZ.
function pushbtn_dongZ_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_dongZ (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%动力学正问题
% Forward dynamics is the computation of joint accelerations given position and
% velocity state, and actuator torques.  It is useful in simulation of a robot
% control system.
prompt={'输入时间段：'};
name='参数';
numlines=1;
defaultanswer={'[0 2]'};
answer=inputdlg(prompt,name,numlines,defaultanswer);
if ~isempty(answer),
    t0=str2num(answer{1});
end
eval('puma560');
[t,q,qd]=fdyn(nofriction(p560),t0(1),t0(2));
nq=find(all(q==0)==0);
figure('Name','PUMA560机器人仿真演示窗口---动力学正问题(位置)','NumberTitle','off');
for i=1:length(nq),
    subplot(round(length(nq)/2),2,i);
    plot(t,q(:,i));
    xlabel('Time(s)');
    ylabel(['Joint ' num2str(nq(i)) ' (rad)']);
end
nq=find(all(qd==0)==0);
figure('Name','PUMA560机器人仿真演示窗口---动力学正问题(速度)','NumberTitle','off');
for i=1:length(nq),
    subplot(round(length(nq)/2),2,i);
    plot(t,qd(:,i));
    xlabel('Time(s)');
    ylabel(['Joint ' num2str(nq(i)) ' (rad/s)']);
end
puma_gui=guihandles(puma560_gui());
axes(puma_gui.axes1);
plot(p560,q);


% --- Executes on button press in pushbtn_dongN.
function pushbtn_dongN_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_dongN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%动力学逆问题
% Inverse dynamics computes the joint torques required to achieve the specified
% state of joint position, velocity and acceleration.  
% The recursive Newton-Euler formulation is an efficient matrix oriented
% algorithm for computing the inverse dynamics, and is implemented in the 
% function rne().
% Inverse dynamics requires inertial and mass parameters of each link, as well
% as the kinematic parameters.  This is achieved by augmenting the kinematic 
% description matrix with additional columns for the inertial and mass 
% parameters for each link.
prompt={'输入时间向量：','输入起始点：','输入终止点：'};
name='参数';
numlines=1;
defaultanswer={'0:0.056:2','[0 0 0 0 0 0]','[0 pi/2 -pi/2 0 0 0]'};
answer=inputdlg(prompt,name,numlines,defaultanswer);
if ~isempty(answer),
    t=str2num(answer{1});
    qz=str2num(answer{2});
    qr=str2num(answer{3});
end
eval('puma560');
[q,qd,qdd]=jtraj(qz,qr,t);
tau=rne(p560,q,qd,qdd);
taug=gravload(p560,q);
nt=find(all(tau~=0));
ng=find(all(taug~=0));
figure('Name','PUMA560机器人仿真演示窗口---动力学逆问题(无重力)','NumberTitle','off');
for i=1:length(nt),
    subplot(length(nt),1,i);
    plot(t,tau(:,nt(i)));
    xlabel('Time(s)');
    ylabel(['Joint ' num2str(nt(i)) ' torque(Nm)']);
end
figure('Name','PUMA560机器人仿真演示窗口---动力学逆问题(有重力)','NumberTitle','off');
for i=1:length(ng),
    subplot(length(ng),1,i);
    plot(t,taug(:,ng(i)));
    xlabel('Time(s)');
    ylabel(['Joint ' num2str(ng(i)) ' Gravity torque(Nm)']);
end
puma_gui=guihandles(puma560_gui());
axes(puma_gui.axes1);
plot(p560,q);


% --- Executes on button press in pushbtn_trace.
function pushbtn_trace_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_trace (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%轨迹规划：关节空间(jtraj)，直角坐标(ctraj)和基坐标变换(trinterp)三种方案
str={'关节空间','直角坐标'};
[s,v]=listdlg('PromptString','选择方案:','SelectionMode','single','ListString',str); 
switch s,
    case 0,
    case 1,
        prompt={'输入时间向量:','输入起始点坐标:','输入终止点坐标：'};
        name='输入所需参数';
        numlines=1;
        defaultanswer={'0:0.056:2','[0 0 0 0 0 0]','[0 pi/2 -pi/2 0 0 0]'};
        answer=inputdlg(prompt,name,numlines,defaultanswer);
        t=str2num(answer{1});
        qz=str2num(answer{2});
        qr=str2num(answer{3});
        [q,qd,qdd]=jtraj(qz,qr,t);
        nq=find(all(q==0)==0);
        for i=1:length(nq),
            figure('Name','PUMA560机器人仿真演示窗口---轨迹规划(关节空间）');
            subplot(3,1,1);
            plot(t,q(:,nq(i)));
            title('Theta');
            xlabel('Time(s)');
            ylabel(['Joint ' num2str(nq(i)) '(rad)']);
            subplot(3,1,2);
            plot(t,qd(:,nq(i)));
            title('Velocity');
            xlabel('Time(s)');
            ylabel(['Joint ' num2str(nq(i)) 'vel(rad/s)']);
            subplot(3,1,3);
            plot(t,q(:,nq(i)));
            title('Acceleration');
            xlabel('Time(s)');
            ylabel(['Joint ' num2str(nq(i)) 'accel(rad/s^2)']);
        end
        puma_gui=guihandles(puma560_gui());
        axes(puma_gui.axes1);
        eval('puma560');
        plot(p560,q);
    case 2,
        prompt={'输入时间向量：','输入起始点坐标:','输入终止点坐标：'};
        name='输入所需参数：';
        numlines=1;
        defaultanswer={'0:0.056:2','transl(0.6,-0.5,0)','transl(0.4,0.5,0.2)'};
        answer=inputdlg(prompt,name,numlines,defaultanswer);
        if ~isempty(answer),
            t=str2num(answer{1});
            T1=str2num(answer{2});
            T2=str2num(answer{3});
        end
        T=ctraj(T1,T2,length(t));
        h=findobj('tag','puma560_gui');
        if ~isempty(h),
            close(findobj('Tag','puma560_gui'));
        end
        figure('Name','PUMA560机器人仿真演示窗口---轨迹规划（直角坐标）');
        subplot(3,1,1);
        plot(t, squeeze(T(1,4,:)));
        xlabel('Time (s)');
        ylabel('X (m)');
        subplot(3,1,2);
        plot(t, squeeze(T(2,4,:)));
        xlabel('Time (s)');
        ylabel('Y (m)');
        subplot(3,1,3);
        plot(t, squeeze(T(3,4,:)))
        xlabel('Time (s)');
        ylabel('Z (m)');
        figure('Name','PUMA560机器人仿真演示窗口---轨迹规划（直角坐标）');
        plot3(squeeze(T(1,4,:)),squeeze(T(2,4,:)),squeeze(T(3,4,:)));
        eval('puma560');
        q=ikine(p560,T);
        puma_gui=guihandles(puma560_gui());
        axes(puma_gui.axes1);
        plot(p560,q);
end


% --- Executes on button press in pushbtn_exit.
function pushbtn_exit_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_exit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%退出程序
close(findobj('Tag','puma560_control'));
puma_gui=findobj('Tag','puma560_gui');
if ~isempty(puma_gui),close(puma_gui);end


% --- Executes on button press in pushbtn_import.
function pushbtn_import_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_import (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%载入数据
puma=findobj('Tag','puma560_gui');
if ~isempty(puma),
    %如果存在PUMA560演示窗口
    puma=guihandles(puma);
    eval('puma560');
    axes(puma.axes1);
    qz=zeros(1,6);
    plot(p560,qz);
else
    %如果不存在PUMA560演示窗口
    puma=guihandles(puma560_gui());
    axes(puma.axes1);
    qz=zeros(1,6);
    eval('puma560');
    plot(p560,qz);
end


% --- Executes on button press in pushbtn_animation.
function pushbtn_animation_Callback(hObject, eventdata, handles)
% hObject    handle to pushbtn_animation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
T1=transl(0.6,-0.5,0.2);
T2=transl(0.6,0.5,0.2);
T3=transl(0.6,0.5,-0.2);
T4=transl(0.6,-0.5,-0.2);


T={T1,T2,T3,T4,T1};
eval('puma560');
for i=1:1,
    for j=1:5,
        start_point=T{j};
        end_point=T{j+1};
        T0=ctraj(start_point,end_point,36);
        qianhe=findobj('Tag','qianhe');
    if isempty(qianhe),
        qianhe=figure('Name','PUMA560机器人仿真演示窗口（三维坐标）','Tag','qianhe');
        figure(qianhe);%指定当前的图像对象为图形输出对象
        plot3(squeeze(T0(1,4,:)),squeeze(T0(2,4,:)),squeeze(T0(3,4,:)));
        grid on;
        hold on;
    else
        hold on;
        figure(qianhe);
        plot3(squeeze(T0(1,4,:)),squeeze(T0(2,4,:)),squeeze(T0(3,4,:)));
        grid on
    end

        q=ikine(p560,T0);
        puma=findobj('Tag','puma560_gui');
    if ~isempty(puma),
        puma=guihandles(puma);
        axes(puma.axes1);
        cla;
        plot(p560,q);
        grid on
    else
        puma=guihandles(puma560_gui);
        axes(puma.axes1);
        cla;
        plot(p560,q);
        grid on;
    end
    end
end

% --- Executes on slider movement.
function slider_q1_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q1,'String',num2str(val));
drive_robot(handles);


% --- Executes during object creation, after setting all properties.
function slider_q1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_q2_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q2,'String',num2str(val));
drive_robot(handles);

% --- Executes during object creation, after setting all properties.
function slider_q2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_q3_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q3,'String',num2str(val));
drive_robot(handles);

% --- Executes during object creation, after setting all properties.
function slider_q3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_q4_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q4,'String',num2str(val));
drive_robot(handles);

% --- Executes during object creation, after setting all properties.
function slider_q4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_q5_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q5,'String',num2str(val));
drive_robot(handles);

% --- Executes during object creation, after setting all properties.
function slider_q5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_q6_Callback(hObject, eventdata, handles)
% hObject    handle to slider_q6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
val=get(hObject,'Value');
set(handles.edit_q6,'String',num2str(val));
drive_robot(handles);

% --- Executes during object creation, after setting all properties.
function slider_q6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_q6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function edit_q1_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q1 as text
%        str2double(get(hObject,'String')) returns contents of edit_q1 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q1,'Min');
slider_max=get(handles.slider_q1,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q1,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_q2_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q2 as text
%        str2double(get(hObject,'String')) returns contents of edit_q2 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q2,'Min');
slider_max=get(handles.slider_q2,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q2,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_q3_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q3 as text
%        str2double(get(hObject,'String')) returns contents of edit_q3 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q3,'Min');
slider_max=get(handles.slider_q3,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q3,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_q4_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q4 as text
%        str2double(get(hObject,'String')) returns contents of edit_q4 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q4,'Min');
slider_max=get(handles.slider_q4,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q4,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_q5_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q5 as text
%        str2double(get(hObject,'String')) returns contents of edit_q5 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q5,'Min');
slider_max=get(handles.slider_q5,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q5,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_q6_Callback(hObject, eventdata, handles)
% hObject    handle to edit_q6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_q6 as text
%        str2double(get(hObject,'String')) returns contents of edit_q6 as a double
val=str2double(get(hObject,'String'));
slider_min=get(handles.slider_q6,'Min');
slider_max=get(handles.slider_q6,'Max');
if val>=slider_min && val<=slider_max,
    set(handles.slider_q6,'Value',val);
    drive_robot(handles);
else
    uiwait(errordlg(['Your Value must be in ' num2str(slider_min) ' ~ ' num2str(slider_max) '!'],'Error'));
    set(hObject,'String','');
end

% --- Executes during object creation, after setting all properties.
function edit_q6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_q6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function drive_robot(handles)
theta1=get(handles.slider_q1,'Value');
theta2=get(handles.slider_q2,'Value');
theta3=get(handles.slider_q3,'Value');
theta4=get(handles.slider_q4,'Value');
theta5=get(handles.slider_q5,'Value');
theta6=get(handles.slider_q6,'Value');
puma=findobj('Tag','puma560_gui');
if ~isempty(puma),
    puma=guihandles(puma);
    axes(puma.axes1);
    cla;
    q=[theta1 theta2 theta3 theta4 theta5 theta6];
    eval('puma560');
    plot(p560,q);
else
    puma=guihandles(puma560_gui());
    axes(puma.axes1);
    cla;
    q=[theta1 theta2 theta3 theta4 theta5 theta6];
    eval('puma560');
    plot(p560,q);
end
