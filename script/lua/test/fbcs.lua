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