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

void calibrateSetup(){
    scale.begin(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN);
}

void calibrateLoop(){
if(scale.is_ready()){

    // Call set_scale() with no parameter
    scale.set_scale();

    Serial.println("Tare... remove any weights from scale.");
    delay(5000);

    // Call tare() with no parameter.
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);

    //Place a known weight on the scale and call get_units(10)
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);

    //Divide the result in step 3 to your known weight. You should get about the parameter you need to pass to set_scale()
  }

  else{
    Serial.println("HX711 not found.");
  }
  delay(1000);
}