/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : CDS(Light) Sensor
 *  Example: CDS Sensor Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define CDS_PIN 13   

void setup() {
  Serial.begin(115200);
  Serial.println("CDS Sensor Test Start");
}

void loop() {

  int adcValue = analogRead(CDS_PIN);

  Serial.print("ADC Value: ");
  Serial.println(adcValue);

  delay(100);
}