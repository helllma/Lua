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

for i=0,1000 do
	print( (2947+i)/(3119+i) )
	WriteFile((2947+i)/(3119+i)..'\n','d:\\test.txt','a')
end