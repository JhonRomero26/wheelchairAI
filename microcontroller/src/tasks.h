#ifndef TASKS_H
#define TASKS_H

#include "BufferQueue.h"
#include "Microphone.h"
#include "streaming_model.h"

void microphoneTask(void* pvParams);
void speechTask(void* pvParams);

#endif