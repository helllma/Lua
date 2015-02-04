function getReplayStringTimes(str,subStr)
	times=0
	for i in string.gfind(str,subStr) do
		times = times+1
	end
	return times
end

function GetInfo(text)
	cmd = io.popen('tasklist /fi "WINDOWTITLE eq '..text..'"','r')
	result = cmd:read('*all')
	cmd:close()
	return result
end

function test()
	a=GetInfo(title)
	print(getReplayStringTimes(a,'lua5.1.exe'))
end

title = '75ec9df80957b37ee18668a52fe7bcda0a0033bd813f90bbc4c01bd4f22690027adfd535'
processNum = 2

ag=arg[1]
if  ag~= nil then
	processNum = ag+0
end

num=0
while true do
	a=GetInfo(title)
	if(getReplayStringTimes(a,'lua5.1.exe') < processNum) then
		os.execute('start lua5.1.exe 1022.lua '..title..' '..os.time()+num)
	else
		os.execute('sleep 1')
	end
	num = num+1
end
