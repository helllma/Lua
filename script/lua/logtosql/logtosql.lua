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

--读取文件
function GetFileData(filepath)
	data = io.open(filepath,'r')
	if data ~= nil then
		alldata = data:read('*all')
		io.close(data)
	else
		print('can not open file.')
	end
	return alldata
end

--执行命令行串。返回值执行结果
function GetCMDInfo(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end

--获取日志文件路径
function getPathFilesPaths(path)
	result = {}
	cmd = 'dir '..path..'\\*.log /b /s'
	getdata = io.popen(cmd,'r')	
	for line in getdata:lines()  do
		table.insert(result,line)
	end
	io.close(getdata)
	return result
end

--从日志中获取失败的sql
function getInsertFailSql(path)
	
	WriteFile('',path..'.sql','w')
	getdata = io.open(path,'r')
	totalagentcdr = 0
	totalZXPJ = 0
	for line in getdata:lines()  do
		_,_,sqlagentcdr = string.find(line,'call=insertagentcdr&agentcdrinfo=(.+)')
		if sqlagentcdr ~= nil  then
			print(sqlagentcdr)
			WriteFile(sqlagentcdr..';\n',path..'.sql','a')
			totalagentcdr=totalagentcdr+1
		end
		--table.insert(result,line)
	end
	WriteFile('--totalagentcdr:'..totalagentcdr..';\n',path..'.sql','a')
	_totalagentcdr = _totalagentcdr+totalagentcdr
	_totalZXPJ = _totalZXPJ+totalZXPJ
end
paths = {'D:\\Hellma\\mycode\\script\\lua\\logtosql\\20140724logs'}
_totalagentcdr = 0
_totalZXPJ = 0
--print(GetCMDInfo('dir '..paths[4]..' /b /s'))
for pindex in pairs(paths) do
	filepaths = getPathFilesPaths(paths[pindex])
	for index in pairs(filepaths) do
		--print(index,filepaths[index])
		getInsertFailSql(filepaths[index])
	end
end
print('_totalagentcdr:'.._totalagentcdr,'_totalZXPJ:'.._totalZXPJ)
--573,153
--print(getInsertFailSql(filepaths[1]))