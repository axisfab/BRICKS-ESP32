#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  
  // 1. BLE 장치 초기화 및 이름 설정
  BLEDevice::init("My_BLE_01");

  // 2. 서버 생성 (연결을 받아들일 준비)
  BLEServer *pServer = BLEDevice::createServer();

  // 3. 광고(Advertising) 설정
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b"); // 임의의 ID
  pAdvertising->setScanResponse(true); // 스캔 시 응답 허용

  // 4. 광고 시작
  BLEDevice::startAdvertising();
  Serial.println("Search for Bluetooth on your Smartphone");
}

void loop() {
}