--function makedata()
    --Make webdata

--end
--makedata()
--Get Scene

file.open("scene.lua", "r")
local buff = file.read(';')
i = 0;
scene_number = {}
scene_code = {}
scene_comd = {}
while buff do
    if (i%5) == 0 then
        scene_number[i/5] = string.gsub(buff,";","")
    end
    if (i%5) == 2 then
        scene_code[i/5] = string.gsub(buff,";","")
    end
    if (i%5) == 3 then
        scene_comd[i/5] = string.gsub(buff,";","")
    end
    i = i + 1;
    buff = file.read(';')
end
scene_number[i/5] = nil
buff = nil
file.close()

--get alarm
alarm_msg = {}
alarm_code = {}
alarm_level = {}
i = 0
file.open("alarm.lua", "r")
buff = file.read(';')
while buff do
    if (i%5) == 1 then
        alarm_msg[i/5] = string.gsub(buff,";","")
    end
    if (i%5) == 2 then
        alarm_code[i/5] = string.gsub(buff,";","")
    end
    if (i%5) == 3 then
        alarm_level[i/5] = string.gsub(buff,";","")
    end
    i = i + 1;
    buff = file.read(';')
end
alarm_msg[i/5] = nil
buff = nil
file.close()

--timer
for i = 0, 5, 1 do
    client_dis[i] = 0
end
tmr.register(0,5000, tmr.ALARM_AUTO, function (t) 
    assert(loadfile("action.lua"))("keepalive",nil,nil)
        for i = 0, 5, 1 do
           if client_dis[i] > 0 then
                print("client ", i, " disconnect ", client_dis[i], "times")
            end
            if client_dis[i] > 3 then
                print("delete client ", i)
                ip[i] = nil
                port[i] = nil
                clientconn[i] = nil
                client_dis[i] = 0
           end
        end
end)
tmr.start(0)

