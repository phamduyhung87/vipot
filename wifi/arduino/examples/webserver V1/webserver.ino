#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "webpage.h"
#include "setting.h"
#include "alarmpage.h"
#include "remotepage.h"
#include "scenepage.h"
#include "wifipage.h"
#include "FS.h"

const String ssid = "Pham Tuan Hung";
const String password = "phamtuanhung";

WiFiServer server(80);
unsigned int UDPPort = 12345;
WiFiUDP Udp;
char packetBuffer[255];
byte ipDefault[4] = {192,168,1,30};
byte ip[4];
byte subnet[4];
byte subnetDefault[4] = {255,255,255,0};
byte gateway[4];
byte dns[4] = {8,8,8,8};
char wifi[4][70];
String scene[20][4];

void setup() {
  Serial.begin(9600);
  delay(10);
    
  // Connect to WiFi network
  Serial.println();
  Serial.println();  
  SPIFFS.begin();
  init_data();
  
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  if (digitalRead(2) == 0){
    WiFi.mode(WIFI_STA);
    WiFi.config(ip,gateway,subnet);
    Serial.print("Connecting to ");  
    Serial.print(wifi[0]);
    Serial.print(" : ");  
    Serial.println(wifi[1]);
    WiFi.begin(wifi[0], wifi[1]);    
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
    boolean result = WiFi.softAP(wifi[2], wifi[3]);
    if(result == true)
    {
      Serial.println("Ready");
      Serial.print("SSID: ");
      Serial.println(wifi[2]);
      Serial.print("Password: ");
      Serial.println(wifi[3]);
    }
    else
    {
      Serial.println("Failed!");
    }
  }  
  // Start the server
  Udp.begin(UDPPort);
  server.begin();  
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  File f = SPIFFS.open("/scene.txt","r");
  int count = 0;
  String str;
  while ((str = f.readStringUntil(';')) != ""){
    str.replace(";","");
    scene[count/4][count%4] = str;
    count++;
  }
}

void loop() {
  //Check if have an UDP
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    char * data = packetBuffer + 18;
    Serial.println(data);
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
  return;
  }
  
  // Wait until the client sends some data
  int wait = 0;
  while(!client.available()){
  delay(1);
   if (wait++ >= 100)
    return;
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\n');
  
  client.flush();
  
  // Match the request
  if (request.indexOf("/sendrf-") != -1) {
    Serial.print("rf ");
    String s = request.substring( sizeof("POST /sendrf-") - 1);
    s.replace(" HTTP/1.1","");
    //s = s.substring(0, idx);
    Serial.print(s);
    Serial.print('\n');
  }
  else
  if (request.indexOf("/sendScene-") != -1){
    String s = request.substring( sizeof("POST /sendScene-") - 1);
    s.replace(" HTTP/1.1","");
    for(int i = 0; i < 20; i++){
      if (s.toInt() == scene[i][0].toInt()){
        Serial.println("rf " + scene[i][2] + "-" + scene[i][3]);
        delay(300);
      }
    }
    client.print("OK");
  }
  else
  if (request.indexOf("/edit?") != -1){
    String s = request.substring( sizeof("GET /edit?") - 1);
    s.replace("/ HTTP/1.1","");
    edit(s);
    client.print("OK");
  }
  else{    
    Serial.println(request);
    response(request, client);
  }
}


