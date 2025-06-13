#include "Microphone.h"


Microphone::Microphone(int8_t amplifyFactor) : amplifyFactor(amplifyFactor) {}

void Microphone::configureMicrophone() {
  i2s_install();
  i2s_setpin();
  i2s_start(MIC_I2S_PORT);
}

void Microphone::i2s_install() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = MIC_SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BIT_COUNT),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = MIC_DMA_BUFF_COUNT,
    .dma_buf_len = MIC_DMA_BUFF_LEN,
    .use_apll = false
  };

  i2s_driver_install(MIC_I2S_PORT, &i2s_config, 0, NULL);
}

void Microphone::i2s_setpin() {
  i2s_pin_config_t pin_config = {
    .bck_io_num = MIC_I2S_SCK,
    .ws_io_num = MIC_I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = MIC_I2S_SD
  };

  i2s_set_pin(MIC_I2S_PORT, &pin_config);
}

esp_err_t Microphone::readAudio() {
  readResult = i2s_read(
    MIC_I2S_PORT, 
    &StreamBuffer,
    StreamBufferNumBytes,
    &bytesRead, 
    portMAX_DELAY
  );
  
  return readResult;
}

int16_t* Microphone::getStreamBuffer() {
  if (amplifyFactor > 1) {
    int samplesRead = bytesRead / 2;
    if (samplesRead > 0) {
    for (int i = 0; i < samplesRead; i++) {
        int32_t sample = StreamBuffer[i] * amplifyFactor;
        
        if (sample > 32700) {
          sample = 32700;
        } else if (sample < -32700) {
          sample = -32700;
        }
        
        StreamBuffer[i] = sample;
      }
    }
  } 

  return StreamBuffer;
}

esp_err_t Microphone::getReadResult() {
  return readResult;
}

size_t Microphone::getBytesRead() {
  return bytesRead;
}
