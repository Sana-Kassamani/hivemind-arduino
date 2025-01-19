// temp code
#include <Arduino.h>
#include "wifi/wifi.h"
#include "temp_humidity/temp_humidity.h"
#include "load_cell/load_cell.h"


// only runs on boot
void setup() {

  Serial.begin(115200);
  delay(100);
  connectToWifi();
  setupDHT();
  setupScale();
  // calibrateSetup();
}


// runs over and over again

void loop() {
  float humidity;
  float temperature;
  float mass;
  // calibrateLoop();
  loopDHT(temperature, humidity);
  loopScale(mass);
  sendRequest(temperature, humidity, mass);
  delay(5000);
}


