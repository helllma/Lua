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
writepath = 'D:\\Hellma\\mycode\\script\\lua\\客户信息导入\\info.txt'
content = GetFileData('D:\\Hellma\\mycode\\script\\lua\\客户信息导入\\sheet001.htm')
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



