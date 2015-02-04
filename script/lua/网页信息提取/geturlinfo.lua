 --ִ��������
function GetCmdResult(cmd)
	getdata = io.popen(cmd,'r')
	all = getdata:read('*all')
	io.close(getdata)
	return all
end
--��ȡ�ļ�
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
--д�ļ������� content���ļ����ݣ�filepath �ļ�����·��,type д�뷽ʽ��wд�룬a׷��д��
function WriteFile(content,filepath,type)
	if type == nil then
		type = 'w'
	end
	writefile = io.open(filepath,type)
	if writefile == nil then
		print('�ļ�д��ʧ�ܣ�file '..filepath..' open fail!')
		return false 
	end
	writefile:write(content)
	io.close(writefile)
	return true
end
--ִ������
function Download(downurl)
	os.execute('if exist '..filename..' del status.txt')
	timestart = os.time()
	os.execute('curl --silent -o status.txt "'..downurl..'"')
end
--�����ļ�
function GetCustomerData(content)
	result = {}
	for lines in string.gfind(content,'<li id=".-">.-</li>') do
		--print(lines)
		item = {}
		for line in string.gfind(lines,'<span class="td td%-1st">(.-)</span>') do
			item.index = line
			--print(line)
		end		
		for line in string.gfind(lines,'<span class="td td%-2nd">.-target="_blank">(.-)</a></span>') do
			item.name =line
			--print(line)
		end	
		for line in string.gfind(lines,'<span class="td td%-3rd">(.-)</span>') do
			item.score =line
			--print(line)
		end
		table.insert(result,item)
	end
	return result
end
------------------------------------------------------------

url = 'http://tianqi.2345.com/air-rank.htm'
filename = 'status.txt'

Download(url)
all = GetFileData(filename)
r = GetCustomerData(all)

for i in ipairs(r) do
	WriteFile(r[i].index..'\t'..r[i].name..'\t'..r[i].score..'\n','last.txt','a')
end
