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
name = {'һ�߽���ʣ�&gt;80%��', 'һ�߽���ʷ���', 'һ�߽���ʷ�ĸ',
        '�����ʣ�&lt;10%��','�����ʼ������','�����ʼ����ĸ',
		'�¼���Ӧ��ʱ�ʣ�&lt;10%��','�¼���Ӧ��ʱ�ʷ���','�¼���Ӧ��ʱ�ʷ�ĸ',
		'�¼���ʱ����ʣ�&gt;90%��','�¼���ʱ����ʷ���','�¼���ʱ����ʷ�ĸ',
		'�ͻ�����ȣ�85�֣�','�ͻ�Ͷ�ߣ���','�����ʱ������'
		}
orgname = {'ͬ��','��Ѷ','Զ��','����','���'}

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
	WriteFile(items,'D:\\Hellma\\mycode\\script\\lua\\��ά�±��ܱ�flex��������\\export.log','a')
	print(items)
	--os.execute('pause')
end
