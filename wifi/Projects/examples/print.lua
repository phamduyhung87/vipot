file.open("ip.lua", "r")
file.open("ip.lua", "r")
local data = "192;168;1;31;255;255;255;0;192;168;1;1"
local i = string.find(data,';')
data = string.strsub(data, i)
print(data)
local _, _, ip1, ip2, ip3, ip4 = string.find(data, "([A-Z].+);(.+);(.+);(.+);"); 
print(ip1)
print(ip2)
print(ip3)
print(ip4)
file.close()
