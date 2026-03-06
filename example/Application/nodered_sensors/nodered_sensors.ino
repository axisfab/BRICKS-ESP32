/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : temp (Built in Device)
 *  Sensor : SHTC3(MEMS)
 *  Libary : adafruit SHTC3
 *  Example: Temperature&Humidity Sensor Example(Node-red Serial Node Used)
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#include <Wire.h>
#include <Adafruit_SHTC3.h>

Adafruit_SHTC3 shtc3;

void setup() {
  Serial.begin(115200);
  Wire.begin(10, 9);   // SDA, SCL
  shtc3.begin();
}

void loop() {
  sensors_event_t h, t;
  shtc3.getEvent(&h, &t);

  Serial.print(t.temperature);
  Serial.print(",");
  Serial.println(h.relative_humidity);

  delay(2000);
}