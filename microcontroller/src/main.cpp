#include "Wheelchair.h"
#include "utils.h"
#include "Microphone.h"



#define MICRO_BAUDS 115200


Wheelchair controller;
// Microphone &mic;


void setup() {
  Serial.begin(MICRO_BAUDS);
  controller.begin(MICRO_BAUDS);

  // mic.configureMicrophone();
  // xTaskCreatePinnedToCore(
  //   mic->microphoneTask,
  //   "Microphone task",
  //   2048,
  //   NULL,
  //   1,
  //   mic->microphoneHandlerTask,
  //   1
  // );
}

void loop() {
  controller.loop();
}
