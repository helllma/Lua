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

--解析文件
function GetCustomerData(content)
	list = {}
	for lines in string.gfind(content,'(.-)\n') do
		info = {}
		for line in string.gfind(lines, '(%d-)%D') do
			table.insert(info, line)
		end
		table.insert(list,info)
	end
	return list
end

--解析数据
function split(str,sign)
	list = {}
	--print( string.find(str,sign) )
	for line in string.gfind(str, sign) do
		table.insert(list, line)
		print(line)
	end
	print('=========='..#list..'==========')
	return list
end

content = GetFileData('D:\\Hellma\\mycode\\script\\lua\\客户信息导入\\mline.txt')
lastlist = GetCustomerData(content)
writepath = 'D:\\Hellma\\mycode\\script\\lua\\客户信息导入\\mod.sql'

for i=1,#lastlist do	
	print(#lastlist,lastlist[i][2],lastlist[i])
	sql = "update TB_FLOWCUSTOMER t set t.phone = '6"..lastlist[i][2].."'".." where t.ID='"..lastlist[i][1].."';\n"	
	sql1 = "insert into Tb_Flowcustomer_Bind values(SEQ_TB_FLOWCUSTOMER_BIND.Nextval, '6"..lastlist[i][3].."', '"..lastlist[i][1].."', to_char(SYSDATE,'YYYY-MM-DD HH24:MI:SS') );\n"
	sql2 = ''
	WriteFile(sql,writepath,"a")
	WriteFile(sql1,writepath,"a")
	if #lastlist[i] == 4 then
		sql2 = "insert into Tb_Flowcustomer_Bind values(SEQ_TB_FLOWCUSTOMER_BIND.Nextval, '6"..lastlist[i][4].."', '"..lastlist[i][1].."', to_char(SYSDATE,'YYYY-MM-DD HH24:MI:SS') );\n"
		WriteFile(sql2,writepath,"a")
	end
	WriteFile('\n',writepath,"a")
end




