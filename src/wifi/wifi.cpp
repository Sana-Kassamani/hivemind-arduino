#include <Arduino.h>
#include "wifi.h"

#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "<Network-ssid>";
const char* password = "<Network-pass>";

const char* serverName = "http://<IP-Address-of-server>:<Port>/";
const char* iotPath ="hive-details/iot";
const char* alertPath = "hive-details/alert";
// storing times
unsigned long lastTime = 0;
unsigned long lastAlertTime =0;
// timer set for one day = 24 hrs
unsigned long timerDelay = 86400;
// alert set for every hour
unsigned long alertDelay = 36000;

// simulated min and max values for testing, to be replaced by actual temperature and humidity limits
float minTemp = 10.0;
float maxTemp = 30.0;
float minHumidity = 40.0;
float maxHumidity = 65.0;


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

bool inRange(float v,float v1, float v2){
    return (v >= v1 && v <= v2);   
}

void httpRequest(String path,String data){
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){

      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with path
      http.begin(client, serverName+path);
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");

      // Data to send with HTTP POST
      String httpRequestData = data;           
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
}

bool checkAbnormalValues(String &s, float t, float h){
    s="";
    if( inRange(t, minTemp, maxTemp) && inRange(h, minHumidity,maxHumidity))
    {
        return false;
    }
    if(t < minTemp){
        s+="Low Temperature!";
    }
    else if( t > maxTemp){
        s+="High Temperature!";
    }

    if(h < minHumidity){
        s+="Low Humidity!";
    }
    else if( h > maxHumidity){
        s+="High Humidity!";
    }
    return true;
}

void sendRequest(float t, float h, float m){
    String message;
    if(checkAbnormalValues(message, t, h)){
        if( lastAlertTime == 0 || (millis()-lastAlertTime > alertDelay ))
        {
            httpRequest(String(alertPath),"{\"message\":\""+String(message)+"\",\"temperature\":\""+String(t)+"\",\"humidity\":\""+String(h)+"\",\"mass\":\""+String(m)+"\"}" );
            lastAlertTime = millis();
            lastTime = millis();
        }
    }
    //Send an HTTP POST request every 10 seconds
     if ((millis() - lastTime) > timerDelay) {
    String data = "{\"temperature\":\""+String(t)+"\",\"humidity\":\""+String(h)+"\",\"mass\":\""+String(m)+"\"}";
    httpRequest(String(iotPath), data);
    lastTime = millis();
    }
}