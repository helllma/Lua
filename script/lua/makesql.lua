data ={
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','11008','胡静',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','11002','王莉丽',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','11009','张继甜',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','11010','李斌艳',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','13888','李月彬',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','14103','王洪英',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','15113','郑珊珊',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','16111','李俊',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','16125','杨艳波',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','就绪','16127','张艳',0)",
}
index = 0

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

function formatTime(para)
	if para<10 then
		para='0'..para
	end
	return para
end
function getTimes(i)
	h=formatTime(math.floor(i/3600))
	m=formatTime(math.floor(i/60))
	s=formatTime(i%60)
	ret = '2014-4-21 '..h..':'..m..':'..s
	return ret
end


for i=1,1257 do
	print()
	for j=1,#data do
		sql = string.gsub(data[j],'times',getTimes(i))
		nameNum = formatTime(math.floor((i-1)/100))
		WriteFile(sql..';\n','d:\\sqlinfo\\insertagentstatus'..nameNum..'.sql','a')
		--print( sql )
	end
end