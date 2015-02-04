url = "http://10.111.0.77:9088/"

info = io.popen('curl -I '..url)
all = info:read('*all')
io.close(info)
--print(all)
print(string.find(all,'200'))
if string.find(all,'HTTP/1.1 200 OK') == nil then
	print("**************************************")
end