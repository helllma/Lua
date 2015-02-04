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

--�����ļ�
function GetCustomerData(content)
	for lines in string.gfind(content,'<tr.->(.-)</tr>') do
		info = {}
		for line in string.gfind(lines,'<td.->(.-)</td>') do
			line = string.gsub(line,'(<br>.-)','')
			line = string.gsub(line,'(\n)',' ')
			table.insert(info,line)
		end
		if #info == 5 then
			depname = info[1]
		else
			table.insert(info,1,depname)
		end
		table.insert(customerInfo,info)
	end
end

customerInfo = {}
depname = ''
writepath = 'D:\\Hellma\\mycode\\script\\lua\\�ͻ���Ϣ����\\info.txt'
content = GetFileData('D:\\Hellma\\mycode\\script\\lua\\�ͻ���Ϣ����\\sheet001.htm')
GetCustomerData(content)
for i=1,#customerInfo do
	print(customerInfo[i])
	line = ''
	for j=1,#customerInfo[i] do
		line=line..customerInfo[i][j]..'\t'
	end
	line = line..'\n'
	WriteFile(line,writepath,"a")
end
print(#customerInfo)



