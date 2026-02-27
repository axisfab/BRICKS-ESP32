/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : PIR(Passive Infrared) Motion sensor
 *  Example: Motion Detection Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define PIR_PIN 35    
#define LED_PIN 2    

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  delay(3000);
  Serial.println("PIR Motio Sensor Ready");
}

void loop() {

  int motionState = digitalRead(PIR_PIN);

  if (motionState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motion Detected!");
  }
  else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("No Motion");
  }

  delay(500);
}