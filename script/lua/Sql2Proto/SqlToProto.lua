--��������ӳ��
typemap = {["NUMBER"]="int32", ["VARCHAR2"]="string"}
--proto�Ĺ̶�ͷ��ʽ
protohead = '// ����ָ������\
option java_package = "com.ydtf.ipcc.itsm";\
// ��Ҫ�޸�������һ��\
option optimize_for = CODE_SIZE;'
-------------------------------------------------------------------------------------------------------------------------------------
--��ȡsql�ļ����ݣ����� sqlpath���ļ�·�� ����ֵ���ļ�ȫ����
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
--��ȡ���������� content�������账���ַ�buf ����ֵ������
function FindTableName(content)
	_,_,tablename = string.find(content, '%c+CREATE%s-TABLE%s-(%S-)%c')
	return tablename
end
--����ÿһ�����ݣ����� content�������账���ַ�buf ����ֵ��columnname�����ƣ�, columntype�����ͣ�, columntypelen�����ͳ��ȣ�
function ParserData(content)
	_,_,columnname=string.find(content, '(%S-)%s-%S-%)')
	_,_,columntype=string.find(content, '%S-%s-(%S-)%(')
	_,_,columntypelen=string.find(content, '%S-%s-%S-%((.-)%)')
	return columnname, columntype, columntypelen
end
--��ȡע��ӳ��:���� content�������账���ַ�buf��notesmap��ȡӳ��table
function GetNotes(content,notesmap)
	for line in string.gfind(content, "COMMENT%s-ON%s-COLUMN.-%..-%c.-'.-';") do
		_,_,key = string.find(line,"%.(.-)%c.-")
		_,_,value = string.find(line,"'(.+)';")
		notesmap[key]=value
	end
end
--��ȡ�����ݣ����� content�������账���ַ�buf��datatable���ǽ����ַ������ȡ�ı� ����ֵ��datatable
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
--�����ݳ��Ƚ��д������� columntype�����ͣ� typelen ���ͳ��ȡ� ����ֵ�����������ͣ����������ݳ��ȸ�ʽ�����ֱ��ƴ�ӵ��ֶ�
function TypeLengthConvert(columntype, typelen)
	--������PRICE NUMBER(14,2),���������ݽ������⴦��
	if string.find(typelen,',') and columntype =='NUMBER' then
		_,_,len = string.find(typelen,'(.-),.+')
		_,_,declen = string.find(typelen,'.-,(.+)')
		return 'double','[len='..len..',declen='..declen..']'
	end
	return typemap[columntype], '[len='..typelen..']'
end
--�������proto�ļ������ݣ����� tablename��������datatable �ǽ����ַ������ȡ�ı� ����ֵ���������proto�ļ�buf
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
--дproto�ļ������� content��proto�ļ����ݣ�protopath proto�ļ�����·��
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
	print('�����������������sql�ļ����ͱ���proto�ļ���')
	os.exit(-1)
end
sqlpath = arg[1]
protopath = arg[2]
content = ReadSql(sqlpath)
tablename = FindTableName(content)
datatable = {}
WriteProto(MakeProto(tablename, GetTableData(content, datatable)),protopath)
print('�ļ���"'..sqlpath..'" ת��proto��ʽ��"'..protopath..'" �ɹ���')