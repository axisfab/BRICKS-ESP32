/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : neopixel LED(Built-in Device)
 *  Example: neopixel LED Example
 *  Library Install : adafruit neopixel
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#include <Adafruit_NeoPixel.h>

#define PIN        1   
#define NUMPIXELS  1   

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin(); 
}

void loop() {

  if(Serial.available()){
    cmd = Serial.readStringUntil('\n');
    if(cmd == "on"){
      pixels.setPixelColor(0, pixels.Color(150,0,150));
      pixels.show();
    }

    if(cmd == "off"){
      pixels.clear();
      pixels.show();
    }
  }
}