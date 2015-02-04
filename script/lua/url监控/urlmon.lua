--sleep
function Sleep(sec)
	os.execute('sleep '..sec)
end
 --执行命令行
function GetCmdResult(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end

urls = {'http://10.111.0.82:9080/SoftPhonePopWindow.jsp?para=015398523927%5E2482%5EIPCC%5E15307%5E20140722112453%5E12',
		'http://10.111.0.83:9080/SoftPhonePopWindow.jsp?para=015398523927%5E2482%5EIPCC%5E15307%5E20140722112453%5E12',
		'http://10.111.0.79:9080/SoftPhonePopWindow.jsp?para=015398523927%5E2482%5EIPCC%5E15307%5E20140722112453%5E12',
		'http://10.111.0.85:9080/SoftPhonePopWindow.jsp?para=015398523927%5E2482%5EIPCC%5E15307%5E20140722112453%5E12'}

while true do
	print('============================================================================')
	for i=1,#urls do
		result = GetCmdResult('curl --connect-timeout 10 -m 20 --silent -I '..urls[i])
		if(string.find(result,'HTTP/1.1 200 OK')==nil) then
			os.execute('mshta javascript:confirm("连接异常：'..result..'");window.close()')
		end
		print(os.date()..' test:'..urls[i]..'\n'..result)
	end
	Sleep(30)
end