/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Device : OLED(Built in Device)
 *  Device Part : SH1106
 *  Libary : U8g2lib
 *  Example: OLED, Temp Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/


#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_SHTC3.h>

// OLED I2C 핀
#define OLED_SDA 12
#define OLED_SCL 11

// SHTC3 I2C 핀
#define SHTC3_SDA 10
#define SHTC3_SCL 9

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

Adafruit_SHTC3 shtc3;

void setup() {

  Wire.begin(OLED_SDA, OLED_SCL);
  Wire1.begin(SHTC3_SDA, SHTC3_SCL);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);

}

void loop() {
  sensors_event_t h, t;
  shtc3.getEvent(&h, &t);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, "SHTC3 Sensor");
  char buf[32];
  sprintf(buf, "Temp: %.1f C", t.temperature);
  u8g2.drawStr(0, 32, buf);
  sprintf(buf, "Humi: %.1f %%", h.relative_humidity);
  u8g2.drawStr(0, 48, buf);
  u8g2.sendBuffer();
  delay(2000);
}