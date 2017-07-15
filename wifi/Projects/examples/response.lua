local vars, client = ...          
            file.close()
            local buff = ''
            if (vars ~= nil)then
                if ((vars=='/') or (vars=='/Home')) then
                   file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("webpage.lua", "r")
                   client:send(buff);
                end
                if ((vars=='/setting') or (vars=='/settinglight')) then
                   file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("setting.lua", "r")
                   client:send(buff);
                end
                if (vars=='/settingscene') then
                   file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("scenepage.lua", "r")
                   client:send(buff);
                end
                 if (vars=='/settingalarm') then
                 file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("alarmpage.lua", "r")
                   client:send(buff);
                end
                if (vars=='/settingremote') then
                   file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("remotepage.lua", "r")
                   client:send(buff);
                end
                if (vars=='/settingwifi') then
                   file.open("webdata.lua", "r")
                   buff = file.read()
                   file.close()
                   ofile = file.open("wifipage.lua", "r")
                   client:send(buff);
                end
                if (vars=='/data') then
                   file.open("data.lua", "r")
                   buff = file.read(1000)
                   client:send(data);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/room') then                    
                   file.open("room.lua", "r")
                   buff = file.read(200)
                   --file.close()
                   client:send(buff);
                   client:close()
                end
                if (vars=='/scene') then
                   file.open("scene.lua", "r")
                   buff = file.read(1000)
                   client:send(buff);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/bscene') then                    
                   file.open("bscene.lua", "r")
                   buff = file.read(200)
                   client:send(buff);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/alarm') then                    
                   file.open("alarm.lua", "r")
                   buff = file.read(1000)
                   client:send(buff);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/ir') then
                   file.open("ir.lua", "r")
                   buff = file.read(1000)
                   client:send(buff);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/wifi') then
                   file.open("wifi.lua", "r")
                   buff = file.read(500)
                   client:send(buff);
                   --file.close()
                   client:close()
                   file.close()
                end
                if (vars=='/ip') then
                   file.open("ip.lua", "r")
                   local dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')                   
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   buff = dt
                   dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   buff = buff .. dt
                   dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   dt = dt .. ';'
                   buff = buff .. dt
                   client:send(buff);
                   buff = nil
                   dt = nil
                   --file.close()
                   client:close()
                   file.close()
                end   
            end
            buff = nil
vars, client = nil
