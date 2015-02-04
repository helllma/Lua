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

for i=1,90 do
	for j=0,7 do
		ii=2
		if(i%5==1) then
			ii=3
		end
		WriteFile('			tableC_'..i..'_'..(j+ii)..'.text=rptData['..(i-1)..']['..j..'];\n','D:\\Hellma\\mycode\\script\\lua\\运维月报周报flex代码生成\\list.log','a')
		print('tableC_'..i..'_'..(j+ii)..'.text=rptData['..(i-1)..']['..j..']')
	end
	--os.execute('pause')
end