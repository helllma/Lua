orgiddic = {[123317]="PE", [212]="YX", [403]="CX", [404]="HH", [453]="DL", 
[406]="QJ", [407]="LC", [408]="BN", [409]="ZT", [121859]="LJ", 
[121860]="DH", [121861]="DQ", [121862]="BS", [121863]="NJ", [121864]="WS"}

posidbegin = 21

rolecode = {200,201,202,8425,8621}
sqlfilename = 'sqluserinfo.txt'
beginuid = 3302
enduid = 3376

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

WriteFile('',sqlfilename,'w')

for orgid,orgname in pairs(orgiddic) do
	--print(orgid,orgname)
	for i=1,5 do
		sql = "insert into sys_userinfo (userid,orgid,username,login,pw,createdate,positiondialing) values(S_SYS_USERINFO.Nextval,"
		..orgid..",'"..orgname.."_��ϯ_"..i.."','"..orgname.."_��ϯ_"..i.."',1,to_char(SYSDATE,'YYYY-MM-DD HH24:MI:SS'),'"..posidbegin.."00"..i.."');\n"
		print(sql)
		WriteFile(sql,sqlfilename,'a')
	end
	posidbegin = posidbegin+1
end

sqlfilename = 'sqlrole.txt'
WriteFile('',sqlfilename,'w')

for i=beginuid,enduid do
	for _,role in pairs(rolecode) do
		sql = "insert into sys_userrole (userid,roleid) values("..i..","..role..");\n"
		WriteFile(sql,sqlfilename,'a')
	end
end

sqlfilename = 'assertrole.txt'
WriteFile('',sqlfilename,'w')

for i=beginuid,enduid do
	sql = "insert into sys_userrole (userid,roleid) values("..i..",9062);\n"
	WriteFile(sql,sqlfilename,'a')
end