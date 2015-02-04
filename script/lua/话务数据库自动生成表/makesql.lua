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

function GetReplaced(txt,keyword,replacedword)
	return string.gsub(txt,keyword,replacedword)
end

--sqlģ��
modelfile = 'model.sql'
--�滻�Ĺؼ���
replacekeywords = '10_2013'
--�������
makeyears = '2015'
--�������ݿ������Ӧ���
orginfo = {10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28}


all = GetFileData(modelfile)
for orgid in ipairs(orginfo) do
	content = GetReplaced(all,replacekeywords,orginfo[orgid]..'_'..makeyears)
	WriteFile(content..'\n',makeyears..'allsql.sql','a')
end

