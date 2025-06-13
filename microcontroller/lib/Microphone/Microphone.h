#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "Arduino.h"
#include "driver/i2s.h"
#include "utils.h"


#ifndef MICRO_BAUDS
#define MICRO_BAUDS 115200
#endif

#ifndef MIC_SAMPLE_RATE
#define MIC_SAMPLE_RATE 16000            // Frecuencia de muestreo en Hz
#endif

#ifndef MIC_DMA_BUFF_COUNT
#define MIC_DMA_BUFF_COUNT 8
#endif

#ifndef MIC_DMA_BUFF_LEN
#define MIC_DMA_BUFF_LEN 1024
#endif

#ifndef MIC_DMA_BUFF_PORT
#define MIC_I2S_PORT I2S_NUM_0
#endif

#define I2S_SAMPLE_BIT_COUNT 16


#define MIC_I2S_WS 25
#define MIC_I2S_SD 33
#define MIC_I2S_SCK 32

class Microphone {
  private:
    int bauds = 115200;
    const int StreamBufferNumBytes = 512;
    const int StreamBufferLen = 256 /* StreamBufferNumBytes / 2 */;
    int16_t StreamBuffer[256];
    size_t bytesRead = 0;
    int8_t amplifyFactor = 1;
    esp_err_t readResult;
  
  private:
    void i2s_install();
    void i2s_setpin();
  
  public:
    Microphone(int8_t amplifyFactor);
    void configureMicrophone();
    esp_err_t readAudio();
    int16_t* getStreamBuffer();
    esp_err_t getReadResult();
    size_t getBytesRead();
};

#endif