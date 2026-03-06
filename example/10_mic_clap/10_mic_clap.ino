/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Device : MIC(Built in Device)
 *  Example: MIC_Clap Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/

#include <Arduino.h>
#include <driver/i2s.h>

// ===== I2S 마이크 핀 =====
#define I2S_WS 6
#define I2S_SCK 7
#define I2S_SD 8
#define I2S_PORT I2S_NUM_0

// ===== LED 핀 =====
#define LED_PIN 2

bool ledState = false;  // LED 현재 상태 저장
int32_t dc = 0;         // 중심값 보정용

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // I2S 기본 설정
  i2s_config_t config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 128
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
}

void loop() {

  int32_t sample;
  size_t bytes_read;

  // 마이크 데이터 읽기
  i2s_read(I2S_PORT, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);

  if (bytes_read > 0) {

    // 1️중심값 보정
    dc = dc * 0.95 + sample * 0.05;
    int32_t sound = sample - dc;

    // 2️ 값 줄이기
    sound >>= 15;

    // 3️ 소리 크기 계산
    int volume = abs(sound);

    // 4️ 박수 감지 (기준값 200)
    if (volume > 300) {
      ledState = !ledState;  // LED
      digitalWrite(LED_PIN, ledState);
      delay(300);
      Serial.print("Detection Volume : ");
      Serial.println(volume);
    }
  }
}