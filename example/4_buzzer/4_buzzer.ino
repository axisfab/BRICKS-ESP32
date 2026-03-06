/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : buzzer (Built in Device)
 *  Example: buzzer Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#define BUZZER_PWR   3    // 전원 제어 (IO3)
#define BUZZER_SIG   4    // 신호 제어 (IO4)

const int freq = 2000;    // 주파수 (Hz)
const int resolution = 8; // 해상도 (8비트: 0~255)

void setup() {
  // 1. 부저 전원 공급 설정 (회로도 IO3)
  pinMode(BUZZER_PWR, OUTPUT);
  digitalWrite(BUZZER_PWR, HIGH); // 부저 회로 활성화

  // 2. 신호 핀 설정 (새로운 API: ledcAttach)
  // ledcAttach(핀번호, 주파수, 해상도);
  ledcAttach(BUZZER_SIG, freq, resolution);
}

void loop() {
  // 도(262Hz) 재생
  ledcWriteTone(BUZZER_SIG, 262);
  ledcWrite(BUZZER_SIG, 3); //0~255
  delay(500);

  // 소리 끄기
  ledcWriteTone(BUZZER_SIG, 0);
  delay(500);
}