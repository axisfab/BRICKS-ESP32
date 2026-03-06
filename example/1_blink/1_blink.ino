/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : Blink LED(Built-in Device)
 *  Example: Blink LED Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/
 
#define LED_PIN 2  //Blink LED(D4)

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
