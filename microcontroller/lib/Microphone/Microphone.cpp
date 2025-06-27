#include "Microphone.h"

Microphone::Microphone(uint16_t sample_rate, size_t buffer_size, size_t buffer_count, uint8_t i2s_port, uint8_t i2s_ws, uint8_t i2s_sd, uint8_t i2s_sck) {
  sample_rate_ = sample_rate;
  buffer_size_ = buffer_size;
  buffer_count_ = buffer_count;
  i2s_port = i2s_port;
  i2s_ws_ = i2s_ws;
  i2s_sd_ = i2s_sd;
  i2s_sck_ = i2s_sck;
}

bool Microphone::configureMicrophone() {
  if (i2s_install() != ESP_OK) return false;
  if (i2s_setpin() != ESP_OK) return false;
  if (i2s_start(MIC_I2S_PORT) != ESP_OK) return false;

  return true;
}

esp_err_t Microphone::i2s_install() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = MIC_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .dma_buf_count = MIC_BUFF_COUNT,
    .dma_buf_len = MIC_BUFF_LEN,
    .use_apll = false
  };

  return i2s_driver_install(MIC_I2S_PORT, &i2s_config, 0, NULL);
}

esp_err_t Microphone::i2s_setpin() {
  i2s_pin_config_t pin_config = {
    .bck_io_num = MIC_I2S_SCK,
    .ws_io_num = MIC_I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = MIC_I2S_SD
  };

  return i2s_set_pin(MIC_I2S_PORT, &pin_config);
}

bool IRAM_ATTR Microphone::readAudio(void* buffer, size_t samples) {
  if (!buffer || samples == 0) return false;

  size_t bytesRead = 0;
  esp_err_t result = i2s_read(
    MIC_I2S_PORT, 
    buffer,
    samples,
    &bytesRead, 
    MIC_PORT_DELAY
  );
  bytesRead_ = bytesRead;

  return result == ESP_OK && bytesRead > 0;
}

size_t Microphone::getBytesRead() {
  return bytesRead_;
}
