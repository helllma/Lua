--insert into smsinfo (datatype,dstype,dnumber,snumber,username,date,chatboxid,content) values('sms','deliver','15062200535','','����־�Ͼ�','2012.03.02 20:30','168','���������ʦӰ���㲻��Ҫȥ�����������');
function GetData(filepath)
	getdata = io.open(filepath,'r')
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

data = GetData('sms.csv')
print(#data)
total = 0

lastline=''
allcontent=''
for line in string.gfind(data,'(.-)\n') do
	--print(line)
	if string.find(line,'sms,') ~= nil then
		line = '\n'..line
	end
	allcontent = allcontent..line
	total = total+1
end
print(total)
WriteFile(allcontent,'sms_.csv','w')