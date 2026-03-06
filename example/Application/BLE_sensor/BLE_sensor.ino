#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE 서비스 및 특성 UUID (표준 Nordic UART UUID)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

static const int LED_PIN = 2; // ESP32-S3의 IO2번 핀
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;

// 연결 상태 콜백
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("기기가 연결되었습니다.");
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("연결이 해제되었습니다. 다시 광고를 시작합니다.");
      pServer->getAdvertising()->start();
    }
};

// 데이터 수신 콜백
// 데이터 수신 콜백 (수정 버전)
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      // std::string 대신 아두이노 String 객체로 받습니다.
      String rxValue = pCharacteristic->getValue(); 

      if (rxValue.length() > 0) {
        Serial.print("수신된 데이터: ");
        Serial.println(rxValue);

        // String 객체의 indexOf 메서드를 사용하여 문자 포함 여부 확인
        if (rxValue.indexOf("1") != -1) {
          digitalWrite(LED_PIN, HIGH);
          Serial.println("LED ON");
        } 
        else if (rxValue.indexOf("0") != -1) {
          digitalWrite(LED_PIN, LOW);
          Serial.println("LED OFF");
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // BLE 장치 초기화
  BLEDevice::init("ESP32S3_LED_CTRL"); // 스마트폰에서 보일 이름

  // 서버 생성 및 콜백 설정
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 서비스 생성
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // TX 특성 (ESP32 -> 스마트폰) 생성
  pTxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
  pTxCharacteristic->addDescriptor(new BLE2902());

  // RX 특성 (스마트폰 -> ESP32) 생성
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // 서비스 시작 및 광고(Advertising) 개시
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("BLE 대기 중... 스마트폰에서 연결하세요.");
}

void loop() {
  // 루프에서는 별도의 작업이 필요 없으며 콜백에서 처리됩니다.
  delay(10);
}