data ={
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','11008','����',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','11002','������',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','11009','�ż���',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','11010','�����',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','13888','���±�',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','14103','����Ӣ',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','15113','֣ɺɺ',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','16111','�',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','16125','���޲�',0)",
"Insert into agentstatus(dtime,status,agentnumber ,agentname, sdbz) values('times','����','16127','����',0)",
}
index = 0

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