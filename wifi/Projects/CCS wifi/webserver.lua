add = 1
ofile = nil
ip = {}
port = {}
srv=net.createServer(net.TCP)
print("webserver")
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        ipp, ppp = client:getpeer()
        --print(ipp,ppp)
        --print(request)
        local _, _, method, path, vars, edit = string.find(request, "([A-Z]+) (.+)-(.+) HTTP");
        if (vars ~= nil)then
            if path == '/sendrf' then
                print("rf " .. vars)
                client:send("OK");
                
                client:close()
            end
            if path == '/sendScene' then
                for k = 0, 1, 1 do
                    for j = 0, bs/4 - 1 , 1 do
                        if vars == bscene[j*4] then
                        print("rf " .. bscene[j*4 + 2] .. "-" .. bscene[j*4 + 3])
                        tmr.delay(300000)
                    end
                end
            end
                client:send("OK");
                client:close()
            end
            collectgarbage();
            return
        else
            _, _, method, path, vars, edit = string.find(request, "([A-Z]+) (.+)?(.+):(.+)/ HTTP");
            if (path == '/edit') then
               assert(loadfile("action.lua"))(nil,vars,edit)
                client:send("OK");
                client:close()
                return
            end
                   
            _, _, method, vars = string.find(request, "([A-Z]+) (.+) HTTP");
            if (vars ~= nil)then
                print("response")
                assert(loadfile("response.lua"))(0,vars,client)
                return
            end
    if request == "client"  then
        --dofile('action.lua')
    end
    print(request)
    if request == "connection\n" then
        print("connected")
        add = 1;
        for i = 0, 4, 1 do
            if tcpconn[i] then
                -- tcpconn[i]:send("<h2> Hello, NodeMCU!!! </h2>")
            else
               if add == 1 then
                  ip[i], port[i] = client:getpeer()
                   print("tcpwait",i,"= 1", ip[i], port[i])
                  add = 0;
                  client:send("Conneted to NodeMCU ...")
                  client:close();
               end
            end
        end
    else
        if request == "keepalive" then
        else
            client:send("<h1> Hello, NodeMCU!!! </h1>")
            client:close()
        end
    end
        end
    
        collectgarbage();
    end)
    conn:on("disconnection",function(conn) 
    for i = 0, 4, 1 do
        if tcpconn[i] then
            if tcpconn[i] == conn then
                --tcpconn[i] = nil
            end
        end
    end
  end)
    conn:on("sent",function(client)  
           if ofile then
               local line = file.read(1500)
               if (line == nil) then
                   ofile = file.close()
                   print(ofile)
                   client:close()                   
               else 
                   client:send(line);
               end
           end
    end)
end)
