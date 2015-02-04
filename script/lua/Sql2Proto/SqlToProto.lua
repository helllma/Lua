--数据类型映射
typemap = {["NUMBER"]="int32", ["VARCHAR2"]="string"}
--proto的固定头格式
protohead = '// 必须指定包名\
option java_package = "com.ydtf.ipcc.itsm";\
// 不要修改下面这一行\
option optimize_for = CODE_SIZE;'
-------------------------------------------------------------------------------------------------------------------------------------
--读取sql文件内容；参数 sqlpath：文件路径 返回值：文件全内容
function ReadSql(sqlpath)
	getfile = io.open(sqlpath)
	if getfile == nil then
		print('file '..sqlpath..' open fail!')
		return nil 
	end
	all = string.upper(getfile:read('*all'))
	io.close(getfile)
	return all
end
--获取表名；参数 content：传入需处理字符buf 返回值：表名
function FindTableName(content)
	_,_,tablename = string.find(content, '%c+CREATE%s-TABLE%s-(%S-)%c')
	return tablename
end
--解析每一行数据；参数 content：传入需处理字符buf 返回值：columnname（名称）, columntype（类型）, columntypelen（类型长度）
function ParserData(content)
	_,_,columnname=string.find(content, '(%S-)%s-%S-%)')
	_,_,columntype=string.find(content, '%S-%s-(%S-)%(')
	_,_,columntypelen=string.find(content, '%S-%s-%S-%((.-)%)')
	return columnname, columntype, columntypelen
end
--获取注释映射:参数 content：传入需处理字符buf，notesmap获取映射table
function GetNotes(content,notesmap)
	for line in string.gfind(content, "COMMENT%s-ON%s-COLUMN.-%..-%c.-'.-';") do
		_,_,key = string.find(line,"%.(.-)%c.-")
		_,_,value = string.find(line,"'(.+)';")
		notesmap[key]=value
	end
end
--获取表数据；参数 content：传入需处理字符buf，datatable：是解析字符串后获取的表。 返回值：datatable
function GetTableData(content, datatable)
	_,_,tabledata = string.find(content, 'CREATE%s-TABLE%s-%S-%c%(%c(.-)%)%c')		
	notesmap={}
	GetNotes(content,notesmap)
	for data in string.gfind(tabledata,'(.-)%c') do
		datastrcut = {}
		datastrcut.name, datastrcut.type, datastrcut.typelen = ParserData(data)
		--_,_,datastrcut.notes=string.find(content, 'COMMENT%s-ON%s-COLUMN.-'..datastrcut.name..".-'(.-)'")
		datastrcut.notes = notesmap[datastrcut.name]
		if datastrcut.notes == nil then
			datastrcut.notes = ''
		end
		--print(datastrcut.name, datastrcut.type, datastrcut.typelen,datastrcut.notes)
		table.insert(datatable,datastrcut)
	end
	return datatable
end
--对数据长度进行处理；参数 columntype：类型， typelen 类型长度。 返回值：处理后的类型，处理完数据长度格式后可以直接拼接的字段
function TypeLengthConvert(columntype, typelen)
	--对类似PRICE NUMBER(14,2),这样的数据进行特殊处理
	if string.find(typelen,',') and columntype =='NUMBER' then
		_,_,len = string.find(typelen,'(.-),.+')
		_,_,declen = string.find(typelen,'.-,(.+)')
		return 'double','[len='..len..',declen='..declen..']'
	end
	return typemap[columntype], '[len='..typelen..']'
end
--生成最后proto文件的数据；参数 tablename：表名，datatable 是解析字符串后获取的表。 返回值：最后生成proto文件buf
function MakeProto(tablename, datatable)
	lastbuf = protohead
	lastbuf = lastbuf..'\nmessage '..tablename..'{\n'
	for index,datastruct in pairs(datatable) do
		columntype, columntypelen = TypeLengthConvert(datastruct.type, datastruct.typelen)
		lastbuf = lastbuf..'\toptional\t'..columntype..'\t_'
		..datastruct.name..'='..index..'\t'..columntypelen..';//'..datastruct.notes..'\n'
		--print(datastruct.name,datastruct.type,datastruct.typelen)
	end
	lastbuf = lastbuf..'}'
	return lastbuf
end
--写proto文件；参数 content：proto文件内容，protopath proto文件保存路径
function WriteProto(content,protopath)
	writefile = io.open(protopath,'w')
	if writefile == nil then
		print('file '..protopath..' open fail!')
		return nil 
	end
	writefile:write(content)
	io.close(writefile)
end
-------------------------------------------------------------------------------------------------------------------
if #arg ~= 2 then
	print('输入参数错误，请输入sql文件名和保存proto文件名')
	os.exit(-1)
end
sqlpath = arg[1]
protopath = arg[2]
content = ReadSql(sqlpath)
tablename = FindTableName(content)
datatable = {}
WriteProto(MakeProto(tablename, GetTableData(content, datatable)),protopath)
print('文件："'..sqlpath..'" 转换proto格式："'..protopath..'" 成功！')