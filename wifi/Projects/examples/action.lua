local str , vars, buff = ...

function foo(ip,port,text,i)
  if clientconn[i] then
      clientconn[i] = nil
      client_dis[i] = client_dis[i] + 1;
  end
      clientconn[i] = net.createConnection(net.TCP, 0)
      clientconn[i]:connect(port,ip)
      clientconn[i]:on("connection", function() 
        clientconn[i]:send(text)
        clientconn[i]:close()
        clientconn[i] = nil
        client_dis[i] = 0;
      end)
end

if str then
    --print(str)
    buff = tostring(str)
    for i = 0, 4, 1 do
        if ip[i] then
            --print(ip[i],port[i])
            foo(ip[i],port[i],buff,i)
        end
    end
else
                buff = string.gsub(buff,"%%20"," ")
               if (vars == 'R') then
                    ofile = file.open("room.lua", "w")
                    file.write(buff)
                end
                if (vars == 'D') then
                    ofile = file.open("data.lua", "w")
                    file.write(buff)
                end
                if (vars == 'A') then
                    ofile = file.open("data.lua", "a+")
                    file.write(buff)
                end
                if (vars == 'B') then
                    ofile = file.open("bscene.lua", "w")
                    file.write(buff)
                end
                if (vars == 'S') then
                    ofile = file.open("scene.lua", "w")
                    file.write(buff)
                end
                if (vars == 's') then
                    ofile = file.open("scene.lua", "a+")
                    file.write(buff)
                end
                if (vars == 'd') then
                    ofile = file.open("alarm.lua", "w")
                    file.write(buff)
                end
                if (vars == 'a') then
                    ofile = file.open("alarm.lua", "a+")
                    file.write(buff)
                end
                if (vars == 'i') then
                    ofile = file.open("ip.lua", "w")
                    file.write(buff)
                end
                if (vars == 'w') then
                    ofile = file.open("wifi.lua", "w")
                    file.write(buff)
                end
                 if (vars == 'I') then
                    ofile = file.open("ir.lua", "w")
                    file.write(buff)
                end
                ofile = file.close();
                dofile('makedata.lua')
end
str , vars, buff = nil
