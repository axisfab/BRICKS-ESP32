/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : Tact Switch
 *  Example: Tact Switch Digital Input Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define SWITCH_PIN 35    
#define LED_PIN    2    

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN);
  if (switchState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Switch Pressed");
  } 
  else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Switch Released");
  }
  delay(50); 
}