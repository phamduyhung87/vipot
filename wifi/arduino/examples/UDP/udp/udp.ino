#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

unsigned int UDPPort = 12345;      // local port to listen on
const char* ssid = "Pham Tuan Hung";
const char* password = "phamtuanhung";

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
WiFiUDP Udp;
void setup() {
  Serial.begin(9600);
  delay(10);
  
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
  
  Udp.begin(UDPPort);
  Serial.println();
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    char * data = packetBuffer + 18;
    Serial.println("Contents:");
    Serial.println(data);
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}
