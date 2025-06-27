// #include "Wheelchair.h"
#include "Microphone.h"
#include "streaming_model.h"
#include "wake_word_model.cc"
#include "arduinoFFT.h"
#include "BufferQueue.h"
#include "tasks.h"

#define MICRO_BAUDS 115200
#define MIC_SAMPLE_RATE 16000
#define MIC_QUEUE_SIZE 10
#define MIC_BUFFER_SIZE 1024

// Wheelchair controller;
BufferQueue micQueue(MIC_BUFFER_SIZE, MIC_QUEUE_SIZE, portMAX_DELAY);
Microphone mic(MIC_SAMPLE_RATE, MIC_BUFFER_SIZE);
StreamingModel wakeWord(wake_word_model, 26080, 0.97, 5);

TaskHandle_t microphoneHandlerTask,
  speechHandlerTask;


void initializeTasks() {
  if (!mic.configureMicrophone()) {
    Serial.println("Error al configurar el microfono");
    return;
  }
  xTaskCreatePinnedToCore(
    microphoneTask,
    "Microphone task",
    2048,
    NULL,
    10,
    &microphoneHandlerTask,
    1
  );

  if (!wakeWord.load_model()) {
    Serial.println("Failed to load wake word model");
    return;
  }
  xTaskCreatePinnedToCore(
    speechTask,
    "Speech task",
    4096,
    NULL,
    20,
    &speechHandlerTask,
    1
  );

  vTaskStartScheduler();
}

void setup() {
  Serial.begin(MICRO_BAUDS);
  // controller.begin(MICRO_BAUDS);

  initializeTasks();
}

void loop() {
  // controller.loop();
}