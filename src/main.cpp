// temp code
#include <Arduino.h>
#include "wifi/wifi.h"
#include "temp_humidity/temp_humidity.h"
#include "load_cell/load_cell.h"


// only runs on boot
void setup() {

  Serial.begin(115200);
  delay(100);
  setupWifi();
  setupDHT();
  setupScale();
  // calibrateSetup();
}


// runs over and over again

void loop() {

  // calibrateLoop();
  loopDHT();
  loopScale();
  delay(3000);
}


