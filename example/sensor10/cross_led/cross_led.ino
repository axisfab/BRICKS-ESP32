/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : CROSS-LED
 *  Example: Basic Blink Test\
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define LED_PIN 35  //D0 Pin

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
