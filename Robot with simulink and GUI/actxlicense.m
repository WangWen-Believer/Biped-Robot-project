function lic = actxlicense(progid)

if strcmpi(progid, 'DS.3DVIAPlayerActiveXCtrl')
lic = 'Copyright (c) 2003 ';
return;
end

if strcmpi(progid, 'ADDFLOW.AddFlowCtrl.1')
lic = 'Unlicensed';
return;
end
