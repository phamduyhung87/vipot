void init_data(){
  File f;
  String str;
  int i = 0; 
  
  f.close();
  f = SPIFFS.open("/ip.txt","r");  
  for (i = 0; i < 3; i++){
    str = f.readStringUntil('.');
    str.replace(".","");
    ip[i] = str.toInt(); 
  }
    str = f.readStringUntil(';');
    str.replace(".","");
    ip[i] = str.toInt();
  //byte ip[4] = {192,168,1,150}; 
  //byte subnet[4] = {255,255,255,0};
  
  i = 0;
  for (i = 0; i < 3; i++){
    str = f.readStringUntil('.');
    str.replace(".","");
    subnet[i] = str.toInt(); 
  }
    str = f.readStringUntil(';');
    str.replace(".","");
    subnet[i] = str.toInt();
  //byte gateway[4] = {192,168,1,1};
 
  i = 0;
  for (i = 0; i < 3; i++){
    str = f.readStringUntil('.');
    str.replace(".","");
    gateway[i] = str.toInt(); 
  }
    str = f.readStringUntil(';');
    str.replace(".","");
    gateway[i] = str.toInt();
    f = SPIFFS.open("/wifi.txt","r");
    str = f.readStringUntil(';');
    str.replace(";","");
    str.toCharArray(wifi.stSsid,70);
    str = f.readStringUntil(';');
    str.replace(";","");
    str.toCharArray(wifi.stPassword,70);
    str = f.readStringUntil(';');
    str.replace(";","");
    str.toCharArray(wifi.apSsid,70);
    str = f.readStringUntil(';');
    str.replace(";","");
    str.toCharArray(wifi.apPassword,70);
    f.close();    
}
void refresh(){
  File f = SPIFFS.open("/scene.txt","r");
  int count = 0;
  String str = "";
  while ((str = f.readStringUntil(';')) != ""){
    str.replace(";","");
    if ((count%4) == 0)
      scene[count/4].group = str;
    if ((count%4) == 2)
      scene[count/4].code = str;
    if ((count%4) == 3)
      scene[count/4].comand = str;
    //scene[count/4][count%4] = str;
    count++;
  }
  f = SPIFFS.open("/alarm.txt","r");
  count = 0;
  str = "";
  while ((str = f.readStringUntil(';')) != ""){
    str.replace(";","");
    if ((count%5) == 1)
      alarm[count/5].message = str;
    if ((count%5) == 2)
      alarm[count/5].code = str;
    if ((count%5) == 3)
      alarm[count/5].level = str;
    count++;
  }
  f = SPIFFS.open("/room.txt","r");
  data.room = f.readString();
  f = SPIFFS.open("/light.txt","r");
  data.light = f.readString();
  f = SPIFFS.open("/bscene.txt","r");
  data.scene = f.readString();
  f = SPIFFS.open("/ir.txt","r");
  data.remote = f.readString();
  f.close();
}

void wifi_setup(){
  // Connect to WiFi network
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  if (digitalRead(2) == 0){
    WiFi.mode(WIFI_STA);
    WiFi.config(ip,gateway,subnet);
    Serial.print("Connecting to ");  
    Serial.print(wifi.stSsid);
    Serial.print(" : ");  
    Serial.println(wifi.stPassword);
    WiFi.begin(wifi.stSsid, wifi.stPassword);    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
  }
  else{
    WiFi.mode(WIFI_AP);
    WiFi.config(ipDefault,gateway,subnetDefault);
    Serial.print("Setting soft-AP ... ");
    boolean result = WiFi.softAP(wifi.apSsid, wifi.apPassword);
    if(result == true)
    {
      Serial.println("Ready");
      Serial.print("SSID: ");
      Serial.println(wifi.apSsid);
      Serial.print("Password: ");
      Serial.println(wifi.apPassword);
    }
    else
    {
      Serial.println("Failed!");
    }
  }  
}

