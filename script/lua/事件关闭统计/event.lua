typemap={[100001]=10000002,[100002]=10000002,[100003]=10000003,[100004]=10000003,[100005]=10000004,[100006]=10000004}
typename={
			[10000002]='一线解决',[10000003]='二线解决',[10000004]='三线解决',[100001]='一线根本解决',[100002]='一线替代方法',
			[100003]='二线根本解决',[100004]='二线替代方法',[100005]='三线根本解决',[100006]='三线替代方法',[100007]='厂商解决',
			[100008]='未解决',[100009]='自动消失',[100010]='可忽略（作废工单）'
		 }
orgcount={[12]=0,[202]=0,[203]=0,[209]=0}
--print(typemap[100001])

--inname = 'D:\\Hellma\\mycode\\script\\lua\\事件关闭统计\\事件关闭码统计.csv'
--outname = 'D:\\Hellma\\mycode\\script\\lua\\事件关闭统计\\归档异常.csv'
inname = 'D:\\Hellma\\mycode\\script\\lua\\事件关闭统计\\远信0312-0502分析.csv'
outname = 'D:\\Hellma\\mycode\\script\\lua\\事件关闭统计\\远信归档异常0312-0502分析.csv'
info = {}

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
function IsInOrgRange(orgid)
	for index in pairs(orgcount) do	
		if index == orgid then
			return true
		end
	end
	return false
end
--解析文件
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
				lines = lines..',"程序判定：'..typename[nodeid]..' 实际判定:'..typename[closeid]..'"\n'
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

all = GetFileData(inname)
GetCustomerData(all)
print(#info,orgcount[12],orgcount[202],orgcount[203],orgcount[209])
--print(all)

WriteFile('',outname,'w')
for _,data in pairs(info) do
	--print(data)
	WriteFile(data,outname,'a')
end
