local str , vars, edit = ...
if str then
    --print(str)
    local s = tostring(str)
    for i = 0, 4, 1 do
        if tcpconn[i] then
            tcpconn[i]:send(s)
        end
    end
else
                
                
                edit = string.gsub(edit,"%%20"," ")
               if (vars == 'R') then
                    ofile = file.open("room.lua", "w")
                    file.write(edit)
                end
                if (vars == 'D') then
                    ofile = file.open("data.lua", "w")
                    file.write(edit)
                end
                if (vars == 'A') then
                    ofile = file.open("data.lua", "a+")
                    file.write(edit)
                end
                if (vars == 'B') then
                    ofile = file.open("bscene.lua", "w")
                    file.write(edit)
                end
                if (vars == 'S') then
                    ofile = file.open("scene.lua", "w")
                    file.write(edit)
                end
                if (vars == 's') then
                    ofile = file.open("scene.lua", "a+")
                    file.write(edit)
                end
                if (vars == 'd') then
                    ofile = file.open("alarm.lua", "w")
                    file.write(edit)
                end
                if (vars == 'a') then
                    ofile = file.open("alarm.lua", "a+")
                    file.write(edit)
                end
                if (vars == 'i') then
                    ofile = file.open("ip.lua", "w")
                    file.write(edit)
                end
                if (vars == 'w') then
                    ofile = file.open("wifi.lua", "w")
                    file.write(edit)
                end
                 if (vars == 'I') then
                    ofile = file.open("ir.lua", "w")
                    file.write(edit)
                end
                ofile = file.close();
end
