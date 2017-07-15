#include <ESP8266WiFi.h>
#include "FS.h"

const char* ssid = "Pham Tuan Hung";
const char* password = "phamtuanhung";

int ledPin = 2; // GPIO2
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  //byte ip[4] = {192,168,1,30}; 
  byte dns[4] = {8,8,8,8};
  byte gateway[4] = {192,168,1,1};
  byte subnet[4] = {255,255,255,0};
  byte ip[4] = {192,168,1,30}; 
  //for (int i = 0; i < 4; i++){
  //  ip[i] = pgm_read_word_near(ip_mem + i);
  //}
  WiFi.config(ip,dns,gateway,subnet);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  SPIFFS.begin();
  File f = SPIFFS.open("/f.txt", "a");
  if (!f) {
      Serial.println("file open failed");
  }
  Serial.println("====== Writing to SPIFFS file =========");
  // write 10 strings to file
  for (int i=1; i<=2; i++){
    f.print("Millis() : ");
    f.println(millis());
    Serial.println(millis());
  }
  f = SPIFFS.open("/f.txt", "r");
  if (!f) {
      Serial.println("file open failed");
  }
  else
  {
    Serial.println("file open successfully");
    for (int i=1; i<=10; i++){
    String s=f.readStringUntil(';');
    Serial.print(i);
    Serial.print(":");
    Serial.println(s);
    }
  }
}

void loop() {
  

}
