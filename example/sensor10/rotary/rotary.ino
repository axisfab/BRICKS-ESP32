/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : ROTARY SWITCH Sensor
 *  Example: Rotray switch sensor Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define ROTARY_PIN 13   

void setup() {
  Serial.begin(115200);
  Serial.println("CDS Sensor Test Start");
}

void loop() {

  int adcValue = analogRead(ROTARY_PIN);

  Serial.print("ADC Value: ");
  Serial.println(adcValue);

  delay(100);
}