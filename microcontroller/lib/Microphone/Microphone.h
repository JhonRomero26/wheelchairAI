#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "driver/i2s.h"
#include "utils.h"


#define MIC_SAMPLE_RATE 16000            // Frecuencia de muestreo en Hz
#define MIC_BUFF_COUNT 10
#define MIC_BUFF_LEN 1024
#define MIC_PORT_DELAY portMAX_DELAY
#define MIC_I2S_PORT I2S_NUM_0

#define MIC_I2S_WS 25
#define MIC_I2S_SD 33
#define MIC_I2S_SCK 32

class Microphone {
  private:
    size_t bytesRead_ = 0;
    TickType_t timeout_ = MIC_PORT_DELAY;
    uint16_t sample_rate_ = MIC_SAMPLE_RATE;
    size_t buffer_size_ = MIC_BUFF_LEN;
    size_t buffer_count_ = MIC_BUFF_COUNT;
    uint8_t i2s_port = MIC_I2S_PORT;
    uint8_t i2s_ws_ = MIC_I2S_WS;
    uint8_t i2s_sd_ = MIC_I2S_SD;
    uint8_t i2s_sck_ = MIC_I2S_SCK;

    esp_err_t i2s_install();
    esp_err_t i2s_setpin();
  
  public:
    Microphone(
      uint16_t sample_rate = MIC_SAMPLE_RATE,
      size_t buffer_size = MIC_BUFF_LEN,
      size_t buffer_count = MIC_BUFF_COUNT,
      uint8_t i2s_port = MIC_I2S_PORT,
      uint8_t i2s_ws = MIC_I2S_WS,
      uint8_t i2s_sd = MIC_I2S_SD,
      uint8_t i2s_sck = MIC_I2S_SCK);
    bool configureMicrophone();
    size_t getBytesRead();
    bool readAudio(void* buffer, size_t samples);
};

#endif