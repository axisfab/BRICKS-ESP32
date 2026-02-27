/*******************************************************
 * AXISFAB BRICKS-ESP Sensor Example Code
 * Sensor Module : IMU(ICM-20948) 9-Axis Sensor
 * Example: Accel, Gyro, and Magnetometer Output
 * Version : Bricks_sensor v1.1
 *******************************************************/

#include "ICM_20948.h"

#define IMU_SDA 40
#define IMU_SCL 39
ICM_20948_I2C myICM;

void setup() {
  Serial.begin(115200);
  while (!Serial); 
  
  Wire.begin(IMU_SDA, IMU_SCL);
  bool initialized = false;
  while (!initialized) {
    myICM.begin(Wire, 0); // 0x68 주소 사용
    if (myICM.status != ICM_20948_Stat_Ok) {
      Serial.println("센서를 찾을 수 없습니다. 연결을 확인하세요...");
      delay(500);
    } else {
      initialized = true;
    }
  }
}

void loop() {
  if (myICM.dataReady()) {
    myICM.getAGMT(); // 가속도, 자이로, 지자기, 온도 데이터 통합 읽기

    // 1. 가속도 데이터 (mg)
    Serial.print("ACC [mg]: ");
    Serial.print(myICM.accX()); Serial.print(", ");
    Serial.print(myICM.accY()); Serial.print(", ");
    Serial.print(myICM.accZ());

    // 2. 자이로 데이터 (DPS: Degrees Per Second)
    Serial.print(" | GYR [dps]: ");
    Serial.print(myICM.gyrX()); Serial.print(", ");
    Serial.print(myICM.gyrY()); Serial.print(", ");
    Serial.print(myICM.gyrZ());

    // 3. 지자기 데이터 (uT: Micro Tesla)
    Serial.print(" | MAG [uT]: ");
    Serial.print(myICM.magX()); Serial.print(", ");
    Serial.print(myICM.magY()); Serial.print(", ");
    Serial.print(myICM.magZ());

    Serial.println(); // 줄바꿈

  } else {
    Serial.println("Waiting for data...");
  }
  
  delay(100); // 출력 속도 조절 (약 10Hz)
}