--Make webdata
local buff = '<!DOCTYPE html>\n<html>\n<script>\nvar data = \''
--file.open("data.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar room = \''
--file.open("room.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar scene = \''
--file.open("scene.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar bscene = \''
--file.open("bscene.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar alarm_data = \''
--file.open("alarm.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar ir_data = \''
--file.open("ir.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar ip_data = \''
--file.open("ip.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\nvar wifi_data = \''
--file.open("wifi.lua", "r")
--buff = buff .. string.gsub(file.read(),"\n","")
buff = buff .. '\';\n</script>'
file.open("webdata.lua", "w")
file.write(buff)
buff = nil
file.close()