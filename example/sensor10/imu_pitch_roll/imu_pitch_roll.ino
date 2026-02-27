/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : IMU(ICM-20948) Sensor
 *  Example: IMU sensor Example
 *  Library : U8g2 by oliver 2.3x 
 *  Version : Bricks_sensor v1.0
 *******************************************************/
#include "ICM_20948.h"
#include <math.h> // 삼각함수 사용

#define IMU_SDA 40
#define IMU_SCL 39
ICM_20948_I2C myICM;

void setup() {
  Serial.begin(115200);
  Wire.begin(IMU_SDA, IMU_SCL);
  myICM.begin(Wire, 0);
}

void loop() {
  if (myICM.dataReady()) {
    myICM.getAGMT();

    // 가속도 데이터를 이용한 Pitch와 Roll 계산 (라디안 -> 도 변환)
    // atan2를 사용하여 각도를 계산합니다.
    float pitch = atan2(myICM.accY(), myICM.accZ()) * 180 / M_PI;
    float roll = atan2(-myICM.accX(), sqrt(myICM.accY() * myICM.accY() + myICM.accZ() * myICM.accZ())) * 180 / M_PI;

    Serial.print("기울기 -> 앞뒤(Pitch): "); Serial.print(pitch);
    Serial.print("도 | 좌우(Roll): "); Serial.print(roll);
    Serial.println("도");
  }
  delay(200);
}