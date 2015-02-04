--userids={81939,96486,81627,100091,101851,101852,101853,101854,101855,101856,101857,101858,101859,101860,101861,101862,101863,101864,106084,2664}
--userids={581,1002,184,565,1003,524,649,634,1026,1045,2522,2562,2283,952}
--userids={81939,96486,81627,100091,101851,101852,101853,101854,101855,101856,101857,101858,101859,101860,101861,101862,101863,101864}
userids={49,464,476,477,478,479,494,495,505,506,510,511,521,526,528,529,530,533,539,601,604,605,606,607,608,609,610,611,612,625,626,627,
		633,634,649,1714,1715,1716,1717,1718,1720,1724,1902,1962,2082,2582,2583,2584,2585,2586,2587,2588,2589,2590,2591,2592,2593,2602,3122,3130}

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

--roleid = 9022
--roleid = 9142
--roleid = 202
roleid = 9162

content =''
for i=1,#userids do
	content = content.."insert into sys_userrole values("..userids[i]..","..roleid..");\n"	
end
content = content..'\ncommit;';
print(content)