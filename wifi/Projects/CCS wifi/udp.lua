file.open("scene.lua", "r")
bscene = {}
bs = 0
bscene[bs] = file.read(';')
while bscene[bs] do
    bscene[bs] = string.gsub(bscene[bs],";","")
    bs = bs + 1;
    bscene[bs] = file.read(';')
end
file.close()
tcpconn = {net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP)}-- {net.createServer(net.TCP), net.createServer(net.TCP)}
for i = 0, 4, 1 do
    tcpconn[i] = nil
end

s=net.createServer(net.UDP)
s:listen(12345)
s:on("receive",function(s,c)
    local _, _, head, cmd, msg = string.find(c, "(.+)678(.+) (.+)");
    if cmd == 'rf' then
        c = string.gsub(c,"123456789012345678","")
        assert(loadfile("action.lua"))(c,20,30)
        print(c)
    end
    if cmd == 'scene' then
        for k = 0, 1, 1 do
            for j = 0, bs/5 - 1 , 1 do
                if msg == bscene[j*5] then
                    local buf = "rf " .. bscene[j*5 + 2] .. bscene[j*5 + 3]
                    print(buf)
                    tmr.delay(200000)
                end
            end
        end
    end
    end)
alarm = {}
i = 0
file.open("alarm.lua", "r")
alarm[i] = file.read(';')
while alarm[i] do
    alarm[i] = string.gsub(alarm[i],";","")
    i = i + 1;
    alarm[i] = file.read(';')
end
file.close()

uart.on("data", "\r",
  function(data)
    local _, _, cmd, msg = string.find(data, "(.+) (.+)\r");
     --print("cmd =",cmd)
     --
    if cmd == "msg" then
        for j = 0, i/5 - 1 , 1 do
            if msg == (alarm[j*5+2]..alarm[j*5+3]) then
                print(msg)
                assert(loadfile("action.lua"))(alarm[j*5+1],20,30)
            end
        end        
    end
    if data=="quit\r" then
      uart.on("data") -- unregister callback function
    end
end, 0)
