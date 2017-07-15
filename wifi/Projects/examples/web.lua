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
led1 = 3
gpio.mode(led1, gpio.OUTPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        print(request)
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
            print(vars)
        else
            client:send("<!DOCTYPE html>");
        end
        
--         local _on,_off = "",""
--        if(_GET.pin == "ON1")then
--              gpio.write(led1, gpio.HIGH);
--        end
       
        --print(buf);
        collectgarbage();
    end)
    local i = 0;
    
    
    conn:on("sent",function(client)       
        file.open("webpage.lua", "r")
        print(i)
        local j = 0;
        local b = 0;
        local line = "";
        local buf = "";
        while (j <= i) do
            buf = ""
            --for b=0,20,1 do 
               line = file.read(1300)
               if (line == nil) then 
                break end
                --buf = buf .. line              
                
            --end            
            j = j + 1;    
        end
       if (line == nil) then
            --client:send(buf);
           conn:close()
           i = 0;
       else 
           --print(buf);
           client:send(line);
           i = i + 1;
          file.close();
       end
    end)
end)

