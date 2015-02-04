 --÷¥––√¸¡Ó––
function GetCmdResult(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end
--[[
all = GetCmdResult('systeminfo')

for ip in string.gfind(all,'%[%d-%]:.-(%d-%.%d-%.%d-%.%d+)') do
	print(ip)
end
--]]


print(GetCmdResult('sdfsdf'))