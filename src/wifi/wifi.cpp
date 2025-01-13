#include <Arduino.h>
#include "wifi.h"

#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "Tenda_DE7A90";
const char* password = "170180190200";

const char* serverName = "http://192.168.0.100:8080/hive-details/iot";

// storing times
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

WiFiServer server(80);

void connectToWifi(){
   
  //Connecting to WiFi network 
  Serial.println('\n');
  WiFi.begin(ssid,password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(" ");
  }
  Serial.println("\n");
  Serial.println("Connection established");

  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

