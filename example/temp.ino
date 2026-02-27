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
  Serial.print(" C, ");
  Serial.print(h.relative_humidity);
  Serial.println(" %");

  delay(2000);
}