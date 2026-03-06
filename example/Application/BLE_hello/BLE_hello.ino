#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// [주소 설정] 학생들과 약속한 방 번호와 바구니 번호
#define SERVICE_UUID        "300f1432-4265-41e7-bfb2-8891d365a865"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define ANALOG_PIN 13       // 아날로그 센서가 연결된 핀

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// 연결 상태 확인을 위한 콜백 설정
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) { deviceConnected = true; };
    void onDisconnect(BLEServer* pServer) { 
      deviceConnected = false;
      pServer->getAdvertising()->start(); // 끊기면 다시 찾을 수 있게 광고
    }
};

void setup() {
  Serial.begin(115200);
  
  // 1. 블루투스 초기화
  BLEDevice::init("S3_ANALOG_SENSOR");

  // 2. 서버 및 서비스 생성
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 3. 데이터 전송 통로(특성) 생성
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | 
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pService->start();
  
  // 4. 광고 시작
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();

  Serial.println("센서 데이터를 보낼 준비가 되었습니다!");
}

void loop() {
  if (deviceConnected) {
    // 5. 아날로그 값 읽기 (0 ~ 4095)
    int sensorValue = analogRead(ANALOG_PIN);
    
    // 6. 전송을 위해 문자열로 변환
    String data = "Val: " + String(sensorValue);
    
    // 7. 블루투스로 전송
    pCharacteristic->setValue(data.c_str());
    pCharacteristic->notify(); 
    
    Serial.println("전송된 값: " + data);
  }
  
  delay(1000); // 1초 대기
}