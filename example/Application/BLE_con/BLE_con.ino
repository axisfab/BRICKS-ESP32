#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// [주소 설정] 방 번호(Service)와 바구니 번호(Characteristic)
#define SERVICE_UUID        "300f1432-4265-41e7-bfb2-8891d365a865"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // 1. 장치 초기화
  BLEDevice::init("ESP32S3_HELLO");

  // 2. 서버 및 서비스(방) 생성
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 3. 특성(데이터 바구니) 생성 - 읽기(READ)와 알림(NOTIFY) 권한 부여
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | 
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // 4. 바구니에 초기 데이터 담기
  pCharacteristic->setValue("Hello World!");

  // 5. 서비스 시작 및 광고 시작 
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  
  BLEDevice::startAdvertising();
  Serial.println("이제 스마트폰에서 'Hello' 메시지를 확인할 수 있습니다!");
}

void loop() {
  // 2초마다 "Hello!"와 함께 숫자를 붙여서 업데이트
  static int count = 0;
  String data = "Hello! [" + String(count++) + "]";
  
  pCharacteristic->setValue(data.c_str());
  pCharacteristic->notify(); // 연결된 스마트폰에 데이터가 바뀌었다고 알림
  
  Serial.println("보낸 데이터: " + data);
  delay(2000);
}