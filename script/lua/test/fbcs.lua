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

math.randomseed(os.time())
math.random(1)
print(math.random(1,10))

total={}
for i=1,100000 do
	num = math.random(1,10)
	if total[num] == nil then
		total[num] = 1;
	else
		total[num] = total[num]+1
	end
end

for index in pairs(total) do
	print(index,total[index])
end