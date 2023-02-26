#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define RelayD5 D5

const char* ssid = "Pak Nasrul";
const char* password = "pakalfan123";

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    daftar();
  }else{
    Serial.println("WiFi Disconnected");
  }
}

void daftar(){
  WiFiClient client;
  HTTPClient http;

  // URL Request (Wajib HTTP bukan HTTPS)
  String serverPath = "http://192.168.19.105:8000/daftar";
      
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverPath.c_str());

  // If you need Node-RED/server authentication, insert user and password below
  // http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
  // Send HTTP GET request
  int httpResponseCode = http.GET();
      
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  delay(10000);
}
