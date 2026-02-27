/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : Relay Module
 *  Example: Relay Control Test\
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define RELAY_PIN 35  //D0 Pin

void relay_con(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);
    delay(1000);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
  relay_con(5);
}


void loop() {
}
