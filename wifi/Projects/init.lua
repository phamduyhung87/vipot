a = true
-- setup I2c and connect display
function init_i2c_display()
     i2c.setup(0, 4, 3, i2c.SLOW)
     disp = u8g.ssd1306_128x64_i2c(0x3c)
end
-- the draw() routine
function draw()
   disp:setFont(u8g.font_6x10)
   disp:drawStr( 30, 10, "Hello IoT!")
   disp:drawLine(0, 25, 128, 25);
   disp:setFont(u8g.font_chikita)
   disp:drawStr( 5, 40, "More cool stuff coming soon") 
   disp:drawStr( 30, 50, "on ashishware.com")
end
  
function display()
  disp:firstPage()
  repeat
       draw()
  until disp:nextPage() == false      
  display();
end
init_i2c_display()
display()
