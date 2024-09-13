#include "Wheelchair.h"


#define MICRO_BAUDS 115200


Wheelchair controller;

void setup() {
  Serial.begin(MICRO_BAUDS);
  controller.begin(MICRO_BAUDS);
}

void loop() {
  controller.loop();
}
