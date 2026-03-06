/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : buzzer melody (Built in Device)
 *  Example: buzzer Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define BUZZER_PWR   3    
#define BUZZER_SIG   4   

// 음계별 주파수 정의 (도, 레, 미, 파, 솔)
int melody[] = {262, 294, 330, 349, 392};

void setup() {
  pinMode(BUZZER_PWR, OUTPUT);
  digitalWrite(BUZZER_PWR, HIGH); 
  ledcAttach(BUZZER_SIG, 2000, 8); 
}

void loop() {
  for (int i = 0; i < 5; i++) {
    ledcWriteTone(BUZZER_SIG, melody[i]); 
    ledcWrite(BUZZER_SIG, 3);  
    delay(500);               
    ledcWriteTone(BUZZER_SIG, 0);
    delay(100);
  }
  delay(2000);
}