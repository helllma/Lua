data = {}           -- create the matrix
for i=1,9 do
    data[i] = {}    -- create a new row
    for j=1,9 do
       data[i][j] = 0
    end
end
data[1][1] = 8
data[3][2] = 3
data[4][2] = 6
data[2][3] = 7
data[5][3] = 9
data[7][3] = 2
data[2][4] = 5
data[6][4] = 7
data[5][5] = 4
data[6][5] = 5
data[7][5] = 7
data[4][6] = 1
data[8][6] = 3
data[3][7] = 1
data[8][7] = 6
data[9][7] = 8
data[3][8] = 8
data[4][8] = 5
data[8][8] = 1
data[2][9] = 9
data[7][9] = 4

rowinfo = {1,2,3,4,5,6,7,8,9}
column = {1,2,3,4,5,6,7,8,9}
rowmap = {}
columnmap = {}

function getExistmap()
	for i=1,9 do
		row = ''
		for j=1,9 do
			if data[j][i] > 0 then
				makemap(i,data[j][i],rowmap)
				makemap(j,data[j][i],columnmap)
			end
			row = row..data[j][i]
		end
			print(row)
	end
end

function makemap(index,data,map)
	temp={}
	if map[index] == nil then
		table.insert(temp,data)
		map[index] = temp
	else
		temp = map[index]
		table.insert(temp,data)
		map[index] = temp
	end
end

getExistmap()

for i=1,9 do
	print(rowmap[i])
	echo = ''
	for k=1,#rowmap[i] do
		echo = echo..rowmap[i][k]
	end
	print(echo)
end

for i=1,9 do
	print(columnmap[i])
	echo = ''
	for k=1,#columnmap[i] do
		echo = echo..columnmap[i][k]
	end
	print(echo)
end
