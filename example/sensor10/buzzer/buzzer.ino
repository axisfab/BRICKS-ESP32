/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : Active-Buzzer
 *  Example: Basic Beep Test\
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define BUZZER_PIN 35  //D0 Pin

void beep(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);
  beep(5);
}


void loop() {
}
