#ifndef MICROPHONE_H
#include "Arduino.h"
#include "esp_adc_cal.h"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "utils.h"

#define DEFAULT_VREF 1100
#define ADC_SAMPLE_COUNT 1024


class Microphone {
  private:
    int vref = DEFAULT_VREF;
    int adc_sample_count = ADC_SAMPLE_COUNT;
    int bauds = 115200;
    esp_adc_cal_characteristics_t adc_chars;
    xTaskHandle microphoneHandlerTask;
  public:
    void configureMicrophone();
    void microphoneTask(void* pvParameters);
};

#endif