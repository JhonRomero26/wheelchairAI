#include "Wheelchair.h"
#include "utils.h"

#include "esp_adc_cal.h"
#include "driver/i2s.h"
#include "driver/adc.h"



#define MICRO_BAUDS 115200
#define DEFAULT_VREF 1100
#define ADC_SAMPLE_COUNT 1024


Wheelchair controller;

esp_adc_cal_characteristics_t adc_chars;
xTaskHandle microphoneHandlerTask;

void configureMicrophone() {
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_11db);
  esp_adc_cal_characterize(
    ADC_UNIT_1,
    ADC_ATTEN_11db,
    ADC_WIDTH_12Bit,
    DEFAULT_VREF,
    &adc_chars
  );
  // i2s_config_t i2s_config = {
  //   .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
  //   .sample_rate = 40000,
  //   .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
  //   .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
  //   .communication_format = I2S_COMM_FORMAT_I2S_LSB,
  //   .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  //   .dma_buf_count = 2,
  //   .dma_buf_len = 1024,
  //   .use_apll = false,
  //   .tx_desc_auto_clear = false,
  //   .fixed_mclk = 0};

  // // Install and start I2S driver
  // i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  // // Init ADC pad
  // i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_7);
  // // Enable the ADC
  // i2s_adc_enable(I2S_NUM_0);
}

void microphoneTask(void* pvParameters) {
  (void) pvParameters;
  
  while (true) {
    int sample = adc1_get_raw(ADC1_CHANNEL_7);
    int miliVolts = esp_adc_cal_raw_to_voltage(sample, &adc_chars);
    // Serial.printf(">sample:%d\n>miliVolts: %d\n", sample, miliVolts);
    testHwm("Microphone task");
  }
}

void setup() {
  Serial.begin(MICRO_BAUDS);
  controller.begin(MICRO_BAUDS);

  configureMicrophone();
  xTaskCreatePinnedToCore(
    microphoneTask,
    "Microphone task",
    2048,
    NULL,
    1,
    &microphoneHandlerTask,
    1
  );
}

void loop() {
  controller.loop();
}
