--insert into smsinfo (datatype,dstype,dnumber,snumber,username,date,chatboxid,content) values('sms','deliver','15062200535','','范立志南京','2012.03.02 20:30','168','你别受张老师影响你不还要去北京泡妞呢吗');
function GetData(filepath)
	getdata = io.open(filepath,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
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