/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Device : OLED(Built in Device)
 *  Device Part : SH1106
 *  Libary : U8g2lib
 *  Example: OLED Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/


#include <Wire.h>
#include <U8g2lib.h>
#define I2C_SCL 11
#define I2C_SDA 12

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,       // 회전 (0도)
  U8X8_PIN_NONE  // Reset 핀 사용 안함
);

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 20, "OLED TEST");
  u8g2.drawStr(0, 40, "SH1106 OLED");
  u8g2.sendBuffer();
}

void loop() {
}