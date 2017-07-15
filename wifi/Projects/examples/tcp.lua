tcpsrv=net.createServer(net.TCP)
tcpconn = {net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP), net.createServer(net.TCP)}-- {net.createServer(net.TCP), net.createServer(net.TCP)}
for i = 0, 4, 1 do
    tcpconn[i] = nil
end
add = 1
tcpsrv:listen(80,function(conn)
  conn:on("receive",function(client,payload)
    local _, _, method, path, vars, edit = string.find(payload, "([A-Z]+) (.+)-(.+) HTTP");
        if (vars ~= nil)then
            if path == '/sendrf' then
                print("rf " .. vars)
                client:send("OK");
                
                client:close()
            end
            if path == '/sendScene' then
                for k = 0, 1, 1 do
                    for j = 0, bs/5 - 1 , 1 do
                        if vars == bscene[j*5] then
                        print("rf " .. bscene[j*5 + 2] .. bscene[j*5 + 3])
                        tmr.delay(200000)
                    end
                end
            end
                client:send("OK");
                client:close()
            end
            collectgarbage();
            return
        end
    if payload == "client"  then
        --dofile('action.lua')
    end
    if payload == "connection" then
        add = 1;
        for i = 0, 4, 1 do
            if tcpconn[i] then
                -- tcpconn[i]:send("<h2> Hello, NodeMCU!!! </h2>")
            else
               if add == 1 then
                  tcpconn[i] = client
                  add = 0;
                  client:send("Conneted to NodeMCU ...")
               end
            end
        end
    else
        if payload == "keepalive" then
        else
            client:send("<h1> Hello, NodeMCU!!! </h1>")
            client:close()
        end
    end
  end)
  conn:on("sent",function(conn)
  end)
  conn:on("disconnection",function(conn) 
    print("tcp disconnection")    
    for i = 0, 4, 1 do
        if tcpconn[i] then
            if tcpconn[i] == conn then
                print("tcpwait",i,"= 0")
                tcpconn[i] = nil
            end
        end
    end
  end)
end)
