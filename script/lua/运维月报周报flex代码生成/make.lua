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

for i=1,90 do
	for j=0,7 do
		ii=2
		if(i%5==1) then
			ii=3
		end
		WriteFile('			tableC_'..i..'_'..(j+ii)..'.text=rptData['..(i-1)..']['..j..'];\n','D:\\Hellma\\mycode\\script\\lua\\��ά�±��ܱ�flex��������\\list.log','a')
		print('tableC_'..i..'_'..(j+ii)..'.text=rptData['..(i-1)..']['..j..']')
	end
	--os.execute('pause')
end