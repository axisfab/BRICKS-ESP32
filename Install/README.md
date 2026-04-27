# 📦 BRICKS-ESP 개발환경 (Arduino)

## 🔹 Overview
BRICKS-ESP는 ESP32-S3 기반 IoT Edge Device로,  
Arduino IDE를 활용하여 쉽고 빠르게 개발할 수 있습니다.

- MCU: ESP32-S3
- 개발환경: Arduino IDE
- 언어: C / C++
- 통신: USB (CDC 내장)

---

## 🔹 1. Arduino IDE 설치
- 다운로드: https://www.arduino.cc/en/software  
- 설치 후 실행

---

## 🔹 2. ESP32 보드 패키지 설치
1. Arduino IDE 실행  
2. **도구 → 보드 → 보드 매니저**  
3. `esp32` 검색  
4. **Espressif Systems → ESP32 설치**

---

## 🔹 3. 보드 설정
- 도구 → 보드 → **ESP32S3 Dev Module**

### 필수 설정
- USB CDC On Boot → Enabled

---

## 🔹 4. 포트 설정
- USB 연결 후  
- 도구 → 포트 → COMx 선택

---

## 🔹 5. 업로드
- 단축키: `Ctrl + U`

---

## 🔹 6. 테스트 (LED Blink)

```cpp
#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}




---

# 📦 2. BRICKS-ESP 개발환경 (PlatformIO)

```markdown
# 📦 BRICKS-ESP 개발환경 (PlatformIO)

## 🔹 Overview
BRICKS-ESP는 ESP32-S3 기반 IoT Edge Device로,  
VS Code + PlatformIO 환경에서 개발할 수 있습니다.

- MCU: ESP32-S3
- 개발환경: VS Code + PlatformIO
- 언어: C / C++
- 통신: USB (CDC 내장)

---

## 🔹 1. 개발환경 설치

### 1) VS Code
https://code.visualstudio.com/

### 2) PlatformIO 설치
- VS Code 실행 → Extensions → PlatformIO 설치

---

## 🔹 2. 프로젝트 생성
- PlatformIO → New Project

### 설정
- Name: bricks-esp
- Board: esp32-s3-devkitm-1
- Framework: Arduino

---

## 🔹 3. platformio.ini 설정

```ini
[env:esp32-s3-devkitm-1]
platform = espressif32
board = esp32-s3-devkitm-1
framework = arduino

monitor_speed = 115200
upload_speed = 921600

build_flags =
    -DARDUINO_USB_CDC_ON_BOOT=1


