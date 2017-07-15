wifi.setmode(wifi.STATION)
wifi.sta.config("Pham Tuan Hung","phamtuanhung")
cfg =
{
  ip="192.168.1.30",
  netmask="255.255.255.0",
  gateway="192.168.1.1"
}
wifi.sta.setip(cfg)
print(wifi.sta.getip())
buff_led1="load"
buff_led2="load"
buff_led1_on="Dang Bat"
buff_led1_of="Dang Tat"
buff_led2_on="Dang Bat"
buff_led2_of="Dang Tat"
led1 = 3
led2 = 4
gpio.mode(led1, gpio.OUTPUT)
gpio.mode(led2, gpio.OUTPUT)
gpio.write(led1, gpio.LOW);
gpio.write(led2, gpio.LOW);
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
         local _on,_off = "",""
        if(_GET.pin == "ON1")then
              gpio.write(led1, gpio.HIGH);
        elseif(_GET.pin == "OFF1")then
              gpio.write(led1, gpio.LOW);
        elseif(_GET.pin == "ON2")then
              gpio.write(led2, gpio.HIGH);
        elseif(_GET.pin == "OFF2")then
              gpio.write(led2, gpio.LOW);
        end
        if(gpio.read(3)==1)then
            buff_led1=buff_led1_on
        elseif(gpio.read(3)==0)then
            buff_led1=buff_led1_of
        end
        if(gpio.read(4)==1)then
            buff_led2=buff_led2_on
        elseif(gpio.read(4)==0)then
            buff_led2=buff_led2_of
        end
        buf = buf.."<head><title>Linhkien69</title></head>";
        buf = buf.."<h1 align=\"center\"><p><font face=\"Times new roman\" size=\"7\" color=\"0099FF\">Linh Kien 69</font></p></h1>";
        buf = buf.."<h1 align=\"center\"><font face=\"Times new roman\" size=\"7\" color=\"red\">ESP8266 Web Server</font></h1>";
        buf = buf.."<p align=\"center\"><font size=\"7\" color=\"00AA00\"> Thiet Bi 1 </font>";--//
        buf = buf.."<a href=\"?pin=ON1\"><button><font size=\"7\" color=\"00AA00\">ON</font></button></a>";--//
        buf = buf.."&nbsp;<a href=\"?pin=OFF1\"><button><font size=\"7\">OFF</font></button></a>";
        buf = buf.."<font size=\"7\"> ";
        buf = buf..(buff_led1);
        buf = buf.."</font></p>";---thiet bi 1
        buf = buf.."<p align=\"center\"><font size=\"7\" color=\"FF0000\"> Thiet Bi 2 </font>";
        buf = buf.."<a href=\"?pin=ON2\"><button disabled=\"disabled\" color=\"00AA00\"><font size=\"7\" color=\"FF0000\">ON</font></button></a>";
        buf = buf.."&nbsp;<a href=\"?pin=OFF2\"><button><font size=\"7\">OFF</font></button></a>";
        buf = buf.."<font size=\"7\"> ";
        buf = buf..(buff_led2);
        buf = buf.."</font></p>";---thiet bi 2
        buf = buf.."<h1 align=\"center\"><p><marquee behavior=\"alternate\"><font face=\"Times new roman\" size=\"7\"";
        buf = buf.."color=\"FF0000\">Linh Kien 69 Kinh chao Quy Khach <BR>http://linhkien69.vn</BR></font></marquee></p></h1>";
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)
