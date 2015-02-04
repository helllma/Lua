diftime = os.difftime(os.time(),os.time({year=2014,month=8,day=11,hour=10,min=40,sec=0}))
y = math.floor(diftime/(3600*24*365))
m = math.floor(diftime/(3600*24*30))
d = math.floor(diftime/(3600*24))
dh = math.floor(diftime%(3600*24))/3600
print(diftime,y,m,d,dh)