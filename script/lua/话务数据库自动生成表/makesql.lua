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

function GetReplaced(txt,keyword,replacedword)
	return string.gsub(txt,keyword,replacedword)
end

--sql模板
modelfile = 'model.sql'
--替换的关键字
replacekeywords = '10_2013'
--生成年份
makeyears = '2015'
--话务数据库机构对应编号
orginfo = {10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28}


all = GetFileData(modelfile)
for orgid in ipairs(orginfo) do
	content = GetReplaced(all,replacekeywords,orginfo[orgid]..'_'..makeyears)
	WriteFile(content..'\n',makeyears..'allsql.sql','a')
end

