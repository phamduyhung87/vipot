void response(String request, WiFiClient client){
  if (request.indexOf("/data") != -1) {
    File f = SPIFFS.open("/data.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/room") != -1) {
    File f = SPIFFS.open("/room.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/bscene") != -1) {
   File f = SPIFFS.open("/bscene.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/scene") != -1) {
    File f = SPIFFS.open("/scene.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/ir") != -1) {
   File f = SPIFFS.open("/ir.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/alarm") != -1) {
   File f = SPIFFS.open("/alarm.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/wifi") != -1) {
   File f = SPIFFS.open("/wifi.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/ip") != -1) {
   File f = SPIFFS.open("/ip.txt", "r");
    String s=f.readString();
    client.print(s);
    f.close();
  }
  else
  if (request.indexOf("/light") != -1) {
    client.print("room: " + data.room);
    client.print("light: " + data.light + '\n');
    client.print("scene: " + data.scene + '\n');
    client.print("remote: " + data.remote + '\n');
   /*File f = SPIFFS.open("/room.txt", "r");
    String s=f.readString();
    client.print("room: " + s);
    f.close();
    f = SPIFFS.open("/light.txt", "r");
    s=f.readString();
    client.print("light: " + s + '\n');
    f.close();
    f = SPIFFS.open("/bscene.txt", "r");
    s=f.readString();
    client.print("scene: " + s + '\n');
    f.close();
    f = SPIFFS.open("/ir.txt", "r");
    s=f.readString();
    client.print("remote: " + s);
    f.close();*/
  }
  else
  {
    char * page;    
    if (request.indexOf("/setting ") != -1)
      page = setting;
    else
    if (request.indexOf("/settingscene") != -1)
      page = scenepage;
    else
    if (request.indexOf("/settingalarm") != -1)
      page = alarmpage;
    else
    if (request.indexOf("/settingremote") != -1)
      page = remotepage;
    else
    if (request.indexOf("/settingwifi") != -1)
      page = wifipage;
    else
    if (request.indexOf("/settinglight") != -1)
      page = setting;
    else
      page = webpage;
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    char data[2000];
    int len = strlen_P(page);
    int i = 0;
      for (int k = 0; k < len; k++)
      {
        
        data[i++] =  pgm_read_byte_near(page + k);
        if(i>=1998){
          data[1998] = 0;
          client.print(data);
          i = 0;
        }
      }
      data[i] = 0;
      client.print(data);
  }
}

void edit(String str){
  String s = str.substring(0, 2);
  str = str.substring(2);
  str.replace("\%20"," ");
  Serial.println(s + '-' + str);
  if (s == "R:"){
    File f = SPIFFS.open("/room.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "D:"){
    File f = SPIFFS.open("/data.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "A:"){
    File f = SPIFFS.open("/data.txt", "r");
    String s = f.readString();
    s.replace("\r","");
    f = SPIFFS.open("/data.txt", "w");    
    f.print(s + str);
    //f.print(str);
    f.close();
  }
  if (s == "B:"){
    File f = SPIFFS.open("/bscene.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "S:"){
    File f = SPIFFS.open("/scene.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "s:"){
    File f = SPIFFS.open("/scene.txt", "r");
    String s = f.readString();
    s.replace("\r","");
    f = SPIFFS.open("/scene.txt", "w");    
    f.print(s + str);
    //f.print(str);
    f.close();
  }
  if (s == "d:"){
    File f = SPIFFS.open("/alarm.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "a:"){
    File f = SPIFFS.open("/alarm.txt", "r");
    String s = f.readString();
    s.replace("\r","");
    f = SPIFFS.open("/alarm.txt", "w");    
    f.print(s + str);
    //f.print(str);
    f.close();
  }
  if (s == "I:"){
    File f = SPIFFS.open("/ir.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "w:"){
    File f = SPIFFS.open("/wifi.txt", "w");
    f.print(str);
    f.close();
  }
  if (s == "i:"){
    File f = SPIFFS.open("/ip.txt", "w");
    int count,i = 0;
    while(str[i]!=0){
    //for (int i = 0; i < sizeof(str); i++){
      if (str[i] == ';'){
        if ((count%4)!=3)
          str[i] = '.';
        count++;
      }
      i++;
    }
    str[i] = ';';
    str.replace("\n","");
    Serial.print(str);
    f.print(str);
    f.close();
  }
}

//Serial event
void serial_event(){
  // print the string when a newline arrives:
  if (stringComplete) {
    if (inputString.indexOf("msg ") != -1){
      inputString.replace("msg ", "");
      //Serial.println("Sring is: " + inputString);
      for (int j = 0; j < 15; j++){
        if ((inputString.indexOf(alarm[j].code) != -1)&&(alarm[j].code != "")){
          //Serial.print(j);
          //Serial.println(alarm[j].code);
          for (int i = 0; i < 10; i++){
            if (client[i])
              //Serial.print(i);
              client[i].print(alarm[j].message + " " + alarm[j].level);
          }          
          break;
        }        
      }      
    }    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  if ( Serial.available() )      
  {  // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    //Serial.write(inChar);
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 13) {
      stringComplete = true;
    }
  }
}

