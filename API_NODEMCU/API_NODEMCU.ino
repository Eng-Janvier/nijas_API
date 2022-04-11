#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Ethernet.h>
#include <WiFiClient.h>
EthernetClient client; 
WiFiClient wifiClient;

const char* ssid = "IT_Department_Office";   
const char* password = "G.S@W_It5ecured"; 


#define DHTPIN D4
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);

//Connecting the board to WIFI network
void setup_wifi() {
   delay(100);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());}
  
void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
}

void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();

HTTPClient http;    // http object of clas HTTPClient
String url = "http://192.168.1.119:5000/insert/dht/data?Temperature="+String(t)+"&Humidity="+String(h);
http.begin(wifiClient,url);//sending request

Serial.print("[HTTP] GET...   ");
int httpCode = http.GET();//get server response
Serial.println(httpCode);

String payload = http.getString();
Serial.println(payload);
delay(200);
}
