typemap={[100001]=10000002,[100002]=10000002,[100003]=10000003,[100004]=10000003,[100005]=10000004,[100006]=10000004}
typename={
			[10000002]='һ�߽��',[10000003]='���߽��',[10000004]='���߽��',[100001]='һ�߸������',[100002]='һ���������',
			[100003]='���߸������',[100004]='�����������',[100005]='���߸������',[100006]='�����������',[100007]='���̽��',
			[100008]='δ���',[100009]='�Զ���ʧ',[100010]='�ɺ��ԣ����Ϲ�����'
		 }
orgcount={[12]=0,[202]=0,[203]=0,[209]=0}
--print(typemap[100001])

--inname = 'D:\\Hellma\\mycode\\script\\lua\\�¼��ر�ͳ��\\�¼��ر���ͳ��.csv'
--outname = 'D:\\Hellma\\mycode\\script\\lua\\�¼��ر�ͳ��\\�鵵�쳣.csv'
inname = 'D:\\Hellma\\mycode\\script\\lua\\�¼��ر�ͳ��\\Զ��0312-0502����.csv'
outname = 'D:\\Hellma\\mycode\\script\\lua\\�¼��ر�ͳ��\\Զ�Ź鵵�쳣0312-0502����.csv'
info = {}

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
function IsInOrgRange(orgid)
	for index in pairs(orgcount) do	
		if index == orgid then
			return true
		end
	end
	return false
end
--�����ļ�
function GetCustomerData(content)
	test = 0
	for lines in string.gfind(content,'.-\n') do
		closeid = 0
		nodeid = 0
		orgid = 0
		for line in string.gfind(lines,'"(10.-)",.+') do
			nodeid = tonumber(line)
		end		
		for line in string.gfind(lines,'.-,.-,"(10.-)",.+') do
			closeid = tonumber(line)
		end	
		for line in string.gfind(lines,'.-,.-,.-,"(.-)",.+') do
			orgid = tonumber(line)
		end
		if closeid>0 and nodeid>0 then
			if typemap[closeid]~=nodeid then
				lines = string.gsub(lines,'\n','')
				lines = lines..',"�����ж���'..typename[nodeid]..' ʵ���ж�:'..typename[closeid]..'"\n'
				table.insert(info,lines)
				if orgid~=nil and IsInOrgRange(orgid) then
					orgcount[orgid] = orgcount[orgid]+1
				end
			end
		end
		--[[
		if(test == 10) then
			print(test,lines)
			os.exit()
		end
		--]]
		test = test+1
	end
	print(test)
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

all = GetFileData(inname)
GetCustomerData(all)
print(#info,orgcount[12],orgcount[202],orgcount[203],orgcount[209])
--print(all)

WriteFile('',outname,'w')
for _,data in pairs(info) do
	--print(data)
	WriteFile(data,outname,'a')
end
