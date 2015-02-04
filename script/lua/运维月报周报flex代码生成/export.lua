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
name = {'一线解决率（&gt;80%）', '一线解决率分子', '一线解决率分母',
        '呼损率（&lt;10%）','呼损率计算分子','呼损率计算分母',
		'事件响应超时率（&lt;10%）','事件响应超时率分子','事件响应超时率分母',
		'事件按时解决率（&gt;90%）','事件按时解决率分子','事件按时解决率分母',
		'客户满意度（85分）','客户投诉（起）','解决超时工单数'
		}
orgname = {'同方','能讯','远信','东电','监控'}

nindex = 1

for i=1,75 do
	items = ''
	head1 = '			tableHtml+="<tr>";\n'
	head2 =	'			tableHtml+="	<td>'..i..'</td>";\n'
	print(name[nindex],nindex,i)
	if(nindex>#name) then
		nindex=#name
	end
	head3 = '			tableHtml+="	<td rowspan=5>'..name[nindex]..'</td>";\n'
	oindex = 1
	if i%5==0 then
		oindex = 5
	else
		oindex = i%5
	end
	head4 = '			tableHtml+="	<td>'..orgname[oindex]..'</td>";\n'
	tail =  '			tableHtml+="</tr>";\n'
	items = items..head1..head2
	if i%5==1 then
		items = items..head3
		nindex = nindex + 1
	end
	items = items..head4
	
	
	item = ''
	for j=0,7 do
		item = item..'			tableHtml+="	<td>" + rptData['..(i-1)..']['..j..'] + "</td>";\n'
	end
	items = items..item
	items = items..tail
	WriteFile(items,'D:\\Hellma\\mycode\\script\\lua\\运维月报周报flex代码生成\\export.log','a')
	print(items)
	--os.execute('pause')
end
