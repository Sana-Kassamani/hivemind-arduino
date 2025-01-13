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

void sendRequest(){

  //Send an HTTP POST request every 10 seconds
  if ((millis() - lastTime) > timerDelay) {

    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with path
      http.begin(client, serverName);
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");

      // Data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // receive http status code
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
