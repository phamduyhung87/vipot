uart.on("data", "\r",
  function(data)
    --print ("uart receiverd: ", data)
    _, _, vars, buff = string.find(data, "(.+) (.+)\r");
     --print("cmd =",cmd)
     --
    if vars == "msg" then
        while (alarm_msg[j] ~= nil) do
        --for j = 0, i/5 - 1 , 1 do
            if buff == (alarm_code[j] .. alarm_level[j]) then
                print(buff)
                assert(loadfile("action.lua"))(alarm_msg[j],nil,nil)
            end
        end        
    end
    if data=="quit\r" then
      uart.on("data") -- unregister callback function
    end
    vars, buff = nil
end, 0)