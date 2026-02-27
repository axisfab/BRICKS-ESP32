#include <Adafruit_NeoPixel.h>

#define PIN 1 // 회로도 상의 IO1 연결
#define NUMPIXELS 1 // 보드에 내장된 LED 개수

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();  // NeoPixel 라이브러리 초기화
}

void loop() {
    for (int i = 0; i < 150; i++) {
    pixels.setPixelColor(0, pixels.Color(i, 0, i));  // 보라색 톤
    pixels.show();
    delay(10);
  }
    for (int i = 150; i >= 0; i--) {
    pixels.setPixelColor(0, pixels.Color(i, 0, i));
    pixels.show();
    delay(10);
  }
}
