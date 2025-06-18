// #include "Wheelchair.h"
#include "Microphone.h"
#include "streaming_model.h"
#include "wake_word_model.cc"


#define MICRO_BAUDS 115200
#define SAMPLE_RATE 16000
#define AUDIO_BUFFER 1024
#define MIC_AMPLIFY 10

#define MEL_WINDOW_SIZE_MS 30
#define NUM_MEL_BINS 40
#define UPPER_BAND_LIMIT 7500
#define LOWER_BAND_LIMIT 125
#define FFT_SIZE 512


// Wheelchair controller;
Microphone mic(MIC_AMPLIFY);
StreamingModel wakeWord(wake_word_model, 26080, 0.97, 5);

TaskHandle_t microphoneHandlerTask,
  speechHandlerTask;

void microphoneTask(void* pvParams) {
  (void) pvParams;
  mic.configureMicrophone();

  while (true) {
    mic.readAudio();
    delay(10);
  }
}

void speechTask(void *pvParams) {
  (void) pvParams;
  if (!wakeWord.load_model()) {
    Serial.println("Failed to load wake word model");
    return;
  }

  while (true) {
    if (mic.getReadResult() != ESP_OK) continue;

    int16_t* audio_buffer = mic.getStreamBuffer();
    size_t samples_available = mic.getBytesRead() / 2;
    size_t num_features = wakeWord.generate_features(audio_buffer, samples_available);
    int8_t* features = wakeWord.getFeatures();

    Serial.println(num_features);
    // for (size_t i = 0; i < num_features; i++) {
    //   Serial.print(" ");
    //   Serial.print(features[i]);
    //   Serial.print(" ");
    // }
    // Serial.println("]");
    
    // testHwm("Speech task");
  }
}


void setup() {
  Serial.begin(MICRO_BAUDS);
  // controller.begin(MICRO_BAUDS);

  xTaskCreatePinnedToCore(
    microphoneTask,
    "Microphone task",
    2048,
    NULL,
    10,
    &microphoneHandlerTask,
    1
  );

  xTaskCreatePinnedToCore(
    speechTask,
    "Speech task",
    8192,
    NULL,
    20,
    &speechHandlerTask,
    1
  );

  vTaskStartScheduler();
}

void loop() {
  // controller.loop();
}
