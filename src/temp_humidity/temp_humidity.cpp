#include "temp_humidity.h"
#include <Arduino.h>
#include "DHT.h"
#define DHTTYPE DHT22 

const int DHTPin = 4;
DHT dht(DHTPin,DHTTYPE);

static char celsiusTemp[7];
static char humidityTemp[7];

void setupDHT(){
 dht.begin();
}

void loopDHT(){
    float h = dht.readHumidity();
        // read tempeerature in Celcius
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) ) {
        Serial.println("Failed to read from DHT sensor!");
        strcpy(celsiusTemp,"Failed");
        strcpy(humidityTemp, "Failed");         
    }
    else{
        // Computes temperature values in Celsius and Humidity
        float hic = dht.computeHeatIndex(t, h, false);       
        dtostrf(hic, 6, 2, celsiusTemp);                     
        dtostrf(h, 6, 2, humidityTemp);
        
        // You can delete the following Serial.print's, it's just for debugging purposes
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t Temperature: ");
        Serial.print(t);
        Serial.print("\n");
    }

}