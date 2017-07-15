local str , vars, client = ...          
            
            if (vars ~= nil)then
                if (vars=='/') then
                   ofile = file.open("webpage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/Home') then
                   ofile = file.open("webpage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/setting') then
                   ofile = file.open("setting.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/settinglight') then
                   ofile = file.open("setting.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/settingscene') then
                   ofile = file.open("scenepage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                 if (vars=='/settingalarm') then
                   ofile = file.open("alarmpage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/settingremote') then
                   ofile = file.open("remotepage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/settingwifi') then
                   ofile = file.open("wifipage.lua", "r")
                   client:send("<!DOCTYPE html>");
                end
                if (vars=='/data') then
                   file.open("data.lua", "r")
                   local data = file.read(1000)
                   client:send(data);
                   --file.close()
                   client:close()
                end
                if (vars=='/room') then                    
                   file.open("room.lua", "r")
                   edit = file.read(200)
                   --file.close()
                   client:send(edit);
                   client:close()
                end
                if (vars=='/scene') then
                   file.open("scene.lua", "r")
                   edit = file.read(1000)
                   client:send(edit);
                   --file.close()
                   client:close()
                end
                if (vars=='/bscene') then                    
                   file.open("bscene.lua", "r")
                   edit = file.read(200)
                   client:send(edit);
                   --file.close()
                   client:close()
                end
                if (vars=='/alarm') then                    
                   file.open("alarm.lua", "r")
                   edit = file.read(1000)
                   client:send(edit);
                   --file.close()
                   client:close()
                end
                if (vars=='/ir') then
                   file.open("ir.lua", "r")
                   edit = file.read(1000)
                   client:send(edit);
                   --file.close()
                   client:close()
                end
                if (vars=='/wifi') then
                   file.open("wifi.lua", "r")
                   edit = file.read(500)
                   client:send(edit);
                   --file.close()
                   client:close()
                end
                if (vars=='/ip') then
                   file.open("ip.lua", "r")
                   local dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')                   
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   edit = dt
                   dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   edit = edit .. dt
                   dt = file.read(';')
                   dt = dt .. file.read(';')
                   dt = dt .. file.read(';')
                   dt = string.gsub(dt,";",".")
                   dt = dt .. file.read(';')
                   dt = dt .. ';'
                   edit = edit .. dt
                   client:send(edit);
                   --file.close()
                   client:close()
                end   
            end