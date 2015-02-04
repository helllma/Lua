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

--��ȡ�ļ�
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

--ִ�������д�������ִֵ�н��
function GetCMDInfo(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end

--��ȡ��־�ļ�·��
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

--����־�л�ȡʧ�ܵ�sql
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