gpio.mode(4,gpio.INPUT)
gpio.write(4,gpio.LOW)
file.open("wifi.lua", "r")
ssid = file.read(';')
ssid = string.gsub(ssid,";","")
pwd = file.read(';')
pwd = string.gsub(pwd,";","")
cfg = {}
cfg.ssid = file.read(';')
cfg.ssid = string.gsub(cfg.ssid,";","")
cfg.pwd = file.read(';')
cfg.pwd = string.gsub(cfg.pwd,";","")
file.close()
file.open("ip.lua", "r")
  buff = ""
  buff = file.read(';')  
  buff = buff .. file.read(';')
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";",".")
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";","")
  local ipAdd = buff
  buff = file.read(';')  
  buff = buff .. file.read(';')
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";",".")
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";","")
  local ipNet = buff
  buff = file.read(';')  
  buff = buff .. file.read(';')
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";",".")
  buff = buff .. file.read(';')
  buff = string.gsub(buff,";","")
  local ipGate = buff
  buff = nil
file.close()
if gpio.read(4) == 0 then
    wifi.setmode(wifi.STATION)
    wifi.sta.config(ssid,pwd)
    cfg =
    {  
        ip=ipAdd,
        netmask=ipNet,
        gateway=ipGate
    }
    wifi.sta.setip(cfg)
    print("Wifi Station")
else
    wifi.setmode(wifi.SOFTAP)
    wifi.ap.config(cfg)
    cfg =
    {  
        ip=ipAdd,
        netmask=ipNet,
        gateway=ipGate
    }
    wifi.ap.setip(cfg)
    print("Wifi Access Point")
end
bscene = {}
bs = 0
add = 1
ofile = nil
ip = {}
port = {}
client_dis = {1,1,1,1}
clientconn = {}
print(wifi.sta.getip())
--dofile('makedata.lua')

dofile('timer.lua')
dofile('uart.lua')
dofile('webserver.lua')
dofile('udp.lua')
