/*******************************************************
 *  AXISFAB BRICKS-ESP Sensor Example Code
 *  Device : MIC(Built in Device)
 *  Example: MIC Example
 *  Version : Bricks_sensor v1.0
 *******************************************************/


#include <Arduino.h>
#include <driver/i2s.h>

// 1. 하드웨어 핀 설정 (ESP32 핀 번호)
#define I2S_WS      6   // Word Select (좌/우 채널 구분)
#define I2S_SCK     7   // Serial Clock (데이터 전송 타이밍)
#define I2S_SD      8   // Serial Data (실제 음성 데이터)
#define I2S_PORT    I2S_NUM_0

// 소리 데이터 처리를 위한 변수
int32_t dc_offset = 0; 

void setup() {
  Serial.begin(115200);

  // 2. I2S 설정 (마이크와 대화하는 방식 정의)
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // ESP32가 주인, 데이터를 받기만 함
    .sample_rate = 16000,                               // 초당 16,000번 샘플링 (음성 인식 적정 수준)
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,       // 32비트 정밀도로 읽기
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,        // 한 채널만 사용 (L/R 핀이 GND일 때)
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,  // 표준 I2S 방식
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,           // 인터럽트 설정
    .dma_buf_count = 4,                                 // 데이터 임시 저장 창고 개수
    .dma_buf_len = 128                                  // 창고 하나당 크기
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,                  // 출력은 사용 안 함
    .data_in_num = I2S_SD
  };

  // 설정 적용 및 드라이버 설치
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
}

void loop() {
  int32_t sample = 0;
  size_t bytes_read;

  // 3. 데이터 읽기
  // DMA 창고에서 데이터를 꺼내 'sample' 변수에 담습니다.
  i2s_read(I2S_PORT, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);
  
  if (bytes_read > 0) {
    /** * [보정 단계 1: DC Offset 제거]
     * 디지털 마이크 데이터는 0을 기준으로 하지 않고 살짝 떠 있는 경우가 많습니다.
     * 이동 평균(Moving Average)을 이용해 중앙값(0)을 맞춰줍니다.
     */
    dc_offset = (dc_offset * 0.95) + (sample * 0.05);
    int32_t wave = sample - dc_offset;

    /** * [보정 단계 2: 값의 크기 조절 (Scaling)]
     * 32비트 데이터는 숫자가 너무 커서(수억 단위) 그래프에 그리기 어렵습니다.
     * 비트 시프트(>> 15)를 통해 숫자를 작고 다루기 쉽게 만듭니다.
     */
    wave >>= 15;

    // 4. 시리얼 플로터로 출력 (그래프 확인용)
    // 최솟값(-500)과 최댓값(500)을 고정해주면 그래프가 안정적으로 보입니다.
    Serial.print(-500); 
    Serial.print(" ");
    Serial.print(500);  
    Serial.print(" ");
    Serial.println(wave);
    
    // 데이터 처리 속도를 위해 아주 짧은 대기 (필요시 조정)
    delay(5); 
  }
}