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
  local str = ""
  str = file.read(';')  
  str = str .. file.read(';')
  str = str .. file.read(';')
  str = string.gsub(str,";",".")
  str = str .. file.read(';')
  str = string.gsub(str,";","")
  local ipAdd = str
  str = file.read(';')  
  str = str .. file.read(';')
  str = str .. file.read(';')
  str = string.gsub(str,";",".")
  str = str .. file.read(';')
  str = string.gsub(str,";","")
  local ipNet = str
  str = file.read(';')  
  str = str .. file.read(';')
  str = str .. file.read(';')
  str = string.gsub(str,";",".")
  str = str .. file.read(';')
  str = string.gsub(str,";","")
  local ipGate = str
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

print(wifi.sta.getip())
dofile('udp.lua')
dofile('webserver.lua')
