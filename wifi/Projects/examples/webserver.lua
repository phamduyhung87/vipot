
srv=net.createServer(net.TCP)
print("webserver")
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        --ipp, ppp = client:getpeer()
        --print(ipp,ppp)
        --print(request)
        tmr.stop(0)
        _, _, method, path, buff = string.find(request, "([A-Z]+) (.+)-(.+) HTTP");
        if (buff ~= nil)then
            if path == '/sendrf' then
                print("rf " .. buff)
                client:send("OK");
                
                client:close()
            end
            if path == '/sendScene' then
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
                client:send("OK");
                client:close()
            end
            collectgarbage();
            tmr.start(0)
            method, path, buff = nil
            return
        else
            _, _, method, path, vars, buff = string.find(request, "([A-Z]+) (.+)?(.+):(.+)/ HTTP");
            if (path == '/edit') then
               assert(loadfile("action.lua"))(nil,vars,buff)
                client:send("OK");
                client:close()
                tmr.start(0)
                method, path, vars, buff = nil
                return
            end
                   
            _, _, method, vars = string.find(request, "([A-Z]+) (.+) HTTP");
            if (vars ~= nil) and (vars ~= '/favicon.ico') then
                print(vars)
                print("response")
                assert(loadfile("response.lua"))(vars,client)
                tmr.start(0)
                method, vars = nil
                return
            end
            if request == "client"  then
                --dofile('action.lua')
            end
            print(request)
            if request == "connection\n" then
                
                add = 1;
                for i = 0, 4, 1 do
                    if ip[i] then
                        -- tcpconn[i]:send("<h2> Hello, NodeMCU!!! </h2>")
                    else
                       if add == 1 then
                          ip[i], port[i] = client:getpeer()
                           print("ip ",i,"= ", ip[i], port[i])
                          add = 0;
                          client:send("Conneted to NodeMCU ...")
                          client:close();
                       end
                    end
                end
                if add == 1 then
                    print("Full clients")
                    client:send("Full clients ...")
                    client:close();
                end
           end
       end
       tmr.start(0)
   end)
   
   conn:on("sent",function(client)  
           if ofile then
               tmr.stop(0)
               local dt = file.read(1500)
               if (dt == nil) then
                   ofile = file.close()
                   print(ofile)
                   client:close()
                   tmr.start(0)                   
               else 
                   client:send(dt);
                   dt = nil;
               end
           end
    end)
end)
