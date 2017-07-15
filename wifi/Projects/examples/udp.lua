s=net.createServer(net.UDP)
s:listen(12345)
s:on("receive",function(s,c)
    _, _, path, vars, buff = string.find(c, "(.+)678(.+) (.+)");
    if vars == 'rf' then
        c = string.gsub(c,"123456789012345678","")
        assert(loadfile("action.lua"))(c,20,30)
        print(c)
    end
    if vars == 'scene' then
       for k = 0, 1, 1 do
           j = 0
           while (scene_number[j] ~= nil) do
           --for j = 0, (scene_i/5 - 1) , 1 do
               if buff == scene_number[j] then
                   print("rf " .. scene_code[j] .. "-" .. scene_comd[j])
                   tmr.delay(300000)
               end
               j = j + 1
            end
        end
    end
    path, vars, buff = nil
end)
