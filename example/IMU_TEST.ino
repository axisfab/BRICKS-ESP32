/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Sensor Module : IMU(ICM-20948) Sensor
 *  Example: IMU sensor Example
 *  Library : U8g2 by oliver 2.3x 
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <math.h>

// [핀 정의]
#define OLED_SDA 12   
#define OLED_SCL 11   
#define IMU_SDA 40
#define IMU_SCL 39
#define ICM20948_ADDR 0x68
#define AK09916_ADDR  0x0C // 내부 지자기 센서 주소

U8G2_SH1106_128X64_WINSTAR_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);

/* --- 레지스터 제어 함수 --- */
void writeReg(uint8_t bank, uint8_t reg, uint8_t val) {
  Wire1.beginTransmission(ICM20948_ADDR);
  Wire1.write(0x7F); Wire1.write(bank << 4);
  Wire1.endTransmission();
  Wire1.beginTransmission(ICM20948_ADDR);
  Wire1.write(reg); Wire1.write(val); 
  Wire1.endTransmission();
}

uint8_t readReg(uint8_t bank, uint8_t reg) {
  Wire1.beginTransmission(ICM20948_ADDR);
  Wire1.write(0x7F); Wire1.write(bank << 4);
  Wire1.endTransmission();
  Wire1.beginTransmission(ICM20948_ADDR);
  Wire1.write(reg);
  Wire1.endTransmission(false);
  Wire1.requestFrom(ICM20948_ADDR, 1);
  return Wire1.read();
}

/* --- 지자기(AK09916) 직접 읽기 함수 --- */
void readMag(int16_t *m) {
  // Bypass 모드 활성화하여 AK09916에 직접 접근
  writeReg(0, 0x0F, 0x02); // INT_PIN_CFG: Bypass En
  
  Wire1.beginTransmission(AK09916_ADDR);
  Wire1.write(0x11); // ST1 레지스터
  Wire1.endTransmission(false);
  Wire1.requestFrom(AK09916_ADDR, 9); // Status + Data(6) + Status2
  
  if(Wire1.available() >= 9) {
    Wire1.read(); // ST1 Skip
    m[0] = (Wire1.read() | Wire1.read() << 8); // X
    m[1] = (Wire1.read() | Wire1.read() << 8); // Y
    m[2] = (Wire1.read() | Wire1.read() << 8); // Z
    Wire1.read(); // ST2 Skip
  }
}

bool initSensors() {
  writeReg(0, 0x06, 0x80); delay(100); // Reset
  writeReg(0, 0x06, 0x01); delay(100); // Wake
  
  if (readReg(0, 0x00) != 0xEA) return false;

  // 지자기 센서(AK09916) 초기화 (Bypass 모드 후 설정)
  writeReg(0, 0x0F, 0x02); 
  delay(10);
  Wire1.beginTransmission(AK09916_ADDR);
  Wire1.write(0x31); // CNTL2
  Wire1.write(0x08); // Continuous measurement mode 4 (100Hz)
  Wire1.endTransmission();
  
  return true;
}

void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  u8g2.begin();
  Wire1.begin(IMU_SDA, IMU_SCL, 400000); 
  
  if(!initSensors()) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 35, "9-Axis Init Fail!");
    u8g2.sendBuffer();
    while(1);
  }
}

void loop() {
  // 1. 가속도 & 자이로 읽기
  writeReg(0, 0x7F, 0x00); // Bank 0
  Wire1.beginTransmission(ICM20948_ADDR);
  Wire1.write(0x2D);
  Wire1.endTransmission(false);
  Wire1.requestFrom(ICM20948_ADDR, 12);

  int16_t ax, ay, az, gx, gy, gz;
  if(Wire1.available() == 12) {
    ax = (Wire1.read() << 8) | Wire1.read();
    ay = (Wire1.read() << 8) | Wire1.read();
    az = (Wire1.read() << 8) | Wire1.read();
    gx = (Wire1.read() << 8) | Wire1.read();
    gy = (Wire1.read() << 8) | Wire1.read();
    gz = (Wire1.read() << 8) | Wire1.read();
  }

  // 2. 지자기 읽기
  int16_t m[3];
  readMag(m);

  // 3. 합성값 계산
  float accMag  = sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2)) / 16384.0;
  float gyroMag = sqrt(pow(gx, 2) + pow(gy, 2) + pow(gz, 2)) / 131.0;
  float magMag  = sqrt(pow(m[0], 2) + pow(m[1], 2) + pow(m[2], 2)) * 0.15; // uT 단위 변환

  // 4. OLED 출력
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(0, 8, "9-AXIS VECTOR MONITOR");
  u8g2.drawHLine(0, 10, 128);

  u8g2.setFont(u8g2_font_6x12_tr);
  // 가속도 (G)
  u8g2.setCursor(0, 25); u8g2.print("ACC: "); u8g2.print(accMag, 2); u8g2.print(" G");
  // 자이로 (deg/s)
  u8g2.setCursor(0, 42); u8g2.print("GYR: "); u8g2.print(gyroMag, 1); u8g2.print(" dps");
  // 지자기 (uT)
  u8g2.setCursor(0, 59); u8g2.print("MAG: "); u8g2.print(magMag, 1); u8g2.print(" uT");

  u8g2.sendBuffer();
  delay(50);
}