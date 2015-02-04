 --执行命令行
function GetCmdResult(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end
--写文件；参数 content：文件内容，filepath 文件保存路径,type 写入方式，w写入，a追加写入
function WriteFile(content,filepath,type)
	if type == nil then
		type = 'w'
	end
	writefile = io.open(filepath,type)
	if writefile == nil then
		print('文件写入失败！file '..filepath..' open fail!')
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
--执行下载
function Download()
	os.execute('if exist status.txt del status.txt')
	timestart = os.time()
	os.execute('curl --silent -o status.txt "http://10.111.0.78:9084/pMonitor?call=get&orgid=203"')
	return os.time()-timestart
end
--获取当前计算机名
function GetLogName()
	return string.gsub(GetCmdResult('echo %COMPUTERNAME%'),'\n','')
end
--获取xp系统下的详细系统个信息
function GetXPSysInfo()
	return GetCmdResult('systeminfo')
end
--获取任务列表
function GetTaskInfoInfo()
	return GetCmdResult('tasklist')
end

 --[[
 while true do
	cmd = 'curl -I "http://10.111.0.78:9084/pMonitor?call=get&orgid=203"'
	all = GetCmdResult(cmd)
	if(string.find(all,'HTTP/1.1 200 OK')==nil) then
		WriteFile(os.date()..'\t'..all..'\n','err.log',a)
		print('访问异常：生成日志文件：err.log')
	end
	Sleep(1)
end
--]]
os.execute('if not exist logs md logs')
print('已经启动检测，CTRL+C停止。。。')
total = 0
 while true do
	times = Download()
	if(times>2) then
		currtime = os.date('%Y%m%d_%H%M%S')
		WriteFile(currtime..'\t获取URL时间为'..times..'秒\n','logs\\'..GetLogName()..'.err.log','a')
		WriteFile(GetXPSysInfo(),'logs\\'..GetLogName()..'_'..currtime..'.sysinfo.log','a')
		WriteFile(GetTaskInfoInfo(),'logs\\'..GetLogName()..'_'..currtime..'.taskinfo.log','a')
		print(currtime..'\t检测到超时情况，详细记录请参看，err.log')
	end
	Sleep(1)
end