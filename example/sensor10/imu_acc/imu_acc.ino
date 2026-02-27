/*******************************************************
 * AXISFAB BRICKS-ESP Sensor Example Code
 * Sensor Module : IMU(ICM-20948) Sensor
 * Example: Accelerometer Only Output
 * Version : Bricks_sensor v1.0
 *******************************************************/

#include "ICM_20948.h"

#define IMU_SDA 40
#define IMU_SCL 39
ICM_20948_I2C myICM;

void setup() {
  Serial.begin(115200);
  while (!Serial); 
  Wire.begin(IMU_SDA, IMU_SCL);
  myICM.begin(Wire, 0); // 0x68 주소 사용
}

void loop() {
  if (myICM.dataReady()) {
    myICM.getAGMT(); // 데이터 읽기

    // 가속도(Accelerometer) 데이터만 출력 (단위: mg)
    Serial.print("Acc_X: "); Serial.print(myICM.accX());
    Serial.print("\tAcc_Y: "); Serial.print(myICM.accY());
    Serial.print("\tAcc_Z: "); Serial.println(myICM.accZ());

  } 
  delay(200); // 출력 속도 조절 (20Hz)
}