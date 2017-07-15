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
  for (int i = 0; i < 4; i++){
    str = f.readStringUntil(';');
    str.replace(";","");
    str.toCharArray(wifi[i],70);
  }
  
  
}

