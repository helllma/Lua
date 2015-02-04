function GetResult(express)
	express = 'result = '..express
	getresult = loadstring(express)
	getresult()
	return result
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

function GetMD5(text)
	cmd = io.popen('md5 -d'..text,'r')
	result = cmd:read('*all')
	cmd:close()
	return result
end

function GetInfo(md5)
	info = {}
	for i=0,7 do
		table.insert(info,string.sub(md5,1+i*4,4+i*4))
	end
	return info
end

function GetNum(text)
	result=''
	for i=0,#text-1 do
		--print(text,string.sub(text,1+i,1+i))
		result = result..dic[string.sub(text,1+i,1+i)]
	end
	return result
end

function CalNum(info)
	cinfo = {}
	for i in pairs(info) do
		--print(GetNum(info[i]),GetNum(info[#info]))
		num = GetNum(info[i])%GetNum(info[#info])
		if num == 0 then
			num = GetNum(info[i])
		end
		table.insert(cinfo,num)
	end
	return cinfo
end

function GetLastNums(info)
	linfo={}
	local f = frontzone
	local b = backzone
	for i=1,#info do
		if i < 6 then
			num = info[i]%#f
			if num==0 then
				num = #f
			end
			table.insert(linfo,f[num])
			table.remove(f,num)
		else
			num = info[i]%#b
			if num==0 then
				num = #b
			end
			table.insert(linfo,b[num])
			table.remove(b,num)
		end
	end
	return linfo
end

function GetLastNumsEX()
	linfo={}
	local f = frontzone
	local b = backzone
	for i=1,5 do
		num = math.random(0,999999999)%#f
		if num==0 then
			num = #f
		end		
		table.insert(linfo,f[num])
		table.remove(f,num)
	end
	for i=1,2 do
		num = math.random(0,999999999)%#b
		if num==0 then
			num = #b
		end
		table.insert(linfo,b[num])
		table.remove(b,num)
	end
	return linfo
end

function mainprocessEX()
	linfo = GetLastNumsEX()
	--print('linfo:'..#linfo,'frontzone:'..#frontzone,'backzone:'..#backzone)
	return linfo[1]..','..linfo[2]..','..linfo[3]..','..linfo[4]..','..linfo[5]..' '..linfo[6]..','..linfo[7],linfo
end

function mainprocess(text)
	md5 = GetMD5(text)
	--print(md5)
	info = GetInfo(md5)
	cinfo = CalNum(info)
	linfo = GetLastNums(cinfo)
	--print('linfo:'..#linfo,'frontzone:'..#frontzone,'backzone:'..#backzone)
	return linfo[1]..','..linfo[2]..','..linfo[3]..','..linfo[4]..','..linfo[5]..' '..linfo[6]..','..linfo[7],linfo
end

function getscore(info)
	if (score[info[1]]==1 and score[info[2]]==1 and score[info[3]]==1 and score[info[4]]==1 and score[info[5]]==1 and scoreex[info[6]]==1 and scoreex[info[7]]==1) then
		return true
	else
		return false
	end
end

function getRandomNum()
	return os.time()..math.random(0,999999999)
end

function test(num)
	a,b=mainprocess(os.time()..math.random(0,999999999)..'')
	frontzone = initzone(35)
	backzone = initzone(12)
	if(num==10000) then
		print(num,a,os.time()-timecheckpoint)
	end	
	if(getscore(b)==false) then
		test(num+1)
	else
		print(num..' 次后 '..a..' OK')
	end
end

function test1()
	total=0
	while 1==1 do
		total=total+1
		a,b=mainprocessEX()
		frontzone = initzone(35)
		backzone = initzone(12)
		if(total%100000==0) then
			print(total,a,os.time()-timecheckpoint)
		end	
		if(getscore(b)) then
			print(total..'次后'..a..'OK')
			WriteFile(total..'\t'..a..'\t'..os.time()-timecheckpoint..'\n','logs.log','a')
			break
		end
	end
end

function initzone(total)
	list={}
	for i=1,total do
		table.insert(list,i)
	end 
	return list
end

dic = {["0"]=0,["1"]=1,["2"]=2,["3"]=3,["4"]=4,["5"]=5,["6"]=6,["7"]=7,["8"]=8,["9"]=9,["A"]=10,["B"]=11,["C"]=12,["D"]=13,["E"]=14,["F"]=15}

score = {[19]=1,[24]=1,[3]=1,[14]=1,[34]=1}
scoreex = {[8]=1,[7]=1}

timecheckpoint=0

frontzone = initzone(35)
backzone = initzone(12)
ag2 = arg[2]
if ag2 == nil then
	ag2 = os.time()	
end
math.randomseed(ag2)
math.random(0,999999999)

ag = arg[1]
print(ag)
if ag ~= nil then
	os.execute('title='..ag)
end
timecheckpoint = os.time()
--test(1)
test1()


