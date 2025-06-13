#include "Wheelchair.h"
#include "utils.h"
#include "Microphone.h"



#define MICRO_BAUDS 115200


Wheelchair controller;
Microphone mic;

TaskHandle_t microphoneHandlerTask;

void microphoneTask(void* pvParams) {
  (void) pvParams;
  mic.configureMicrophone();

  while (true) {
    mic.readAudio();
    delay(10);
  }
}


void setup() {
  Serial.begin(MICRO_BAUDS);
  controller.begin(MICRO_BAUDS);
  
  xTaskCreatePinnedToCore(
    microphoneTask,
    "Microphone task",
    2048,
    NULL,
    1,
    &microphoneHandlerTask,
    1
  );

  vTaskStartScheduler();
}

void loop() {
  controller.loop();
}
