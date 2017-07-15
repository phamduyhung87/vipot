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
struct Device {
  IPAddress ip;
  unsigned int port = 0;
  unsigned int count = 0;
};
struct Alarm {
  String message;
  String code;
  String level;
};
struct Scene {
  String group;
  String code;
  String comand;
};
struct Wifi {
  char apSsid[70];
  char apPassword[70];
  char stSsid[70];
  char stPassword[70];
};
struct Data {
  String room;
  String light;
  String scene;
  String remote;
};
struct Device device[5];
struct Alarm alarm[15];
struct Scene scene[20];
struct Wifi wifi;
struct Data data;
WiFiServer server(80);
//WiFiClient client[10];
WiFiClient client[10];
unsigned int UDPPort = 12345;
WiFiUDP Udp;
char packetBuffer[255];
byte ipDefault[4] = {192,168,1,30};
byte ip[4];
byte subnet[4];
byte subnetDefault[4] = {255,255,255,0};
byte gateway[4];
byte dns[4] = {8,8,8,8};
//char wifi[4][70];
//String scene[20][4];
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  delay(10);    
  
  Serial.println();
  Serial.println();  
  SPIFFS.begin();
  init_data();
  wifi_setup();
  // Start the server
  Udp.begin(UDPPort);
  server.begin();  
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  refresh();
}

void loop() {
  serial_event();
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
  for (int i = 0; i < 10; i++){
    if (!client[i])
      client[i] = server.available();
    if (client[i]){
      if (client[i].connected()){
        tcp_service(client[i], i);
      }        
      else
      {
        Serial.print("disconnected ");
        Serial.println(i);
        client[i].stop();
      }
    }    
  }
}

void tcp_service(WiFiClient sclient, int i){
  //Serial.println("Connecting from Client");
  //client.print(client.remotePort());
  // Wait until the client sends some data
  int wait = 0;
  while(!sclient.available()){
  delay(1);
   if (wait++ >= 50)
    return;
  }
  if(sclient.available()){
    // Read the first line of the request
    String request = sclient.readStringUntil('\n');
    //Serial.print(request);
    //client.flush();
    // Match the request
    if (request.indexOf("/sendrf-") != -1) {
      Serial.print("rf ");
      String s = request.substring( sizeof("POST /sendrf-") - 1);
      s.replace(" HTTP/1.1","");
      //s = s.substring(0, idx);
      Serial.print(s);
      Serial.print('\n');
      updateLights(s);
      sclient.print("OK");
      sclient.flush();
      client[i].stop();
    }
    else
    if (request.indexOf("/sendScene-") != -1){
      String s = request.substring( sizeof("POST /sendScene-") - 1);
      s.replace(" HTTP/1.1","");
      for(int i = 0; i < 20; i++){
        if (s.toInt() == scene[i].group.toInt()){
          Serial.println("rf " + scene[i].code + "-" + scene[i].comand);
          delay(300);
        }
      }
      sclient.print("OK");
      sclient.flush();
      client[i].stop();
    }
    else
    if (request.indexOf("/edit?") != -1){
      String s = request.substring( sizeof("POST /edit?") - 1);
      s.replace("/ HTTP/1.1","");
      edit(s);
      sclient.print("OK");
      refresh();
      sclient.flush();
      client[i].stop();
    }
    else
    if ((request.indexOf("POST /") != -1)||(request.indexOf("GET /") != -1)) {
      //Serial.println(request);
      http_response(request, sclient);
      sclient.flush();
      client[i].stop();
    }
    else
    if (request.indexOf("connection") == 0){
      for (int i = 0; i < 5; i++){
        if (!device[i].port){
          device[i].ip = sclient.remoteIP();
          device[i].port = sclient.remotePort();
          Serial.print("device ");
          Serial.print(i);
          Serial.print(" : ");
          Serial.print(device[i].ip);
          Serial.print(":");
          Serial.println(device[i].port);
          sclient.print("Conneted to MCU\n");
          break;
        }
        else{
          if (i == 4)
            Serial.println("Full devices");
        }
      }    
    }
    else{
      tcp_response(request, sclient);
    }
  }  
}

