/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : NeoPixel LED(Built-in Device)
 *  Example: RGB LED Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#include <Adafruit_NeoPixel.h>

#define PIN        1   // 회로도 상의 IO1 연결
#define NUMPIXELS  1   // 보드에 내장된 LED 개수

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // NeoPixel 라이브러리 초기화
}

void loop() {
  // 점점 밝아지기
  for(int i=0; i<150; i++) {
    pixels.setPixelColor(0, pixels.Color(i, 0, i)); // 보라색 톤
    pixels.show();
    delay(10);
  }

  // 점점 어두워지기
  for(int i=150; i>=0; i--) {
    pixels.setPixelColor(0, pixels.Color(i, 0, i));
    pixels.show();
    delay(10);
  }
}
