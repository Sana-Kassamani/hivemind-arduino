#include <Arduino.h>
#include "HX711.h"
#include "load_cell.h"

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

void setupScale(){

  Serial.println("Initializing the scale");

  // begin the scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());

  // this value is obtained by calibrating the scale with known weights
  scale.set_scale(388.63);  
  
  // reset the scale to 0
  scale.tare();

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());

}
void loopScale(){

    // get raw reading of scale
    Serial.print("on reading:\t");
    Serial.print(scale.get_units(), 1);

    // put the ADC in sleep mode
    scale.power_down();
    delay(2000);
    scale.power_up();
}

