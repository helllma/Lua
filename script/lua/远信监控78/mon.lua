 --ִ��������
function GetCmdResult(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end
--д�ļ������� content���ļ����ݣ�filepath �ļ�����·��,type д�뷽ʽ��wд�룬a׷��д��
function WriteFile(content,filepath,type)
	if type == nil then
		type = 'w'
	end
	writefile = io.open(filepath,type)
	if writefile == nil then
		print('�ļ�д��ʧ�ܣ�file '..filepath..' open fail!')
		return false 
	end
	writefile:write(content)
	io.close(writefile)
	return true
end
--sleep
function Sleep(sec)
	os.execute('sleep '..sec)
end
--ִ������
function Download()
	os.execute('if exist status.txt del status.txt')
	timestart = os.time()
	os.execute('curl --silent -o status.txt "http://10.111.0.78:9084/pMonitor?call=get&orgid=203"')
	return os.time()-timestart
end
--��ȡ��ǰ�������
function GetLogName()
	return string.gsub(GetCmdResult('echo %COMPUTERNAME%'),'\n','')
end
--��ȡxpϵͳ�µ���ϸϵͳ����Ϣ
function GetXPSysInfo()
	return GetCmdResult('systeminfo')
end
--��ȡ�����б�
function GetTaskInfoInfo()
	return GetCmdResult('tasklist')
end

 --[[
 while true do
	cmd = 'curl -I "http://10.111.0.78:9084/pMonitor?call=get&orgid=203"'
	all = GetCmdResult(cmd)
	if(string.find(all,'HTTP/1.1 200 OK')==nil) then
		WriteFile(os.date()..'\t'..all..'\n','err.log',a)
		print('�����쳣��������־�ļ���err.log')
	end
	Sleep(1)
end
--]]
os.execute('if not exist logs md logs')
print('�Ѿ�������⣬CTRL+Cֹͣ������')
total = 0
 while true do
	times = Download()
	if(times>2) then
		currtime = os.date('%Y%m%d_%H%M%S')
		WriteFile(currtime..'\t��ȡURLʱ��Ϊ'..times..'��\n','logs\\'..GetLogName()..'.err.log','a')
		WriteFile(GetXPSysInfo(),'logs\\'..GetLogName()..'_'..currtime..'.sysinfo.log','a')
		WriteFile(GetTaskInfoInfo(),'logs\\'..GetLogName()..'_'..currtime..'.taskinfo.log','a')
		print(currtime..'\t��⵽��ʱ�������ϸ��¼��ο���err.log')
	end
	Sleep(1)
end