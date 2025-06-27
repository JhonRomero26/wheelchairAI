// AudioBufferQueue.h
#ifndef AUDIO_BUFFER_QUEUE_H
#define AUDIO_BUFFER_QUEUE_H

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef int16_t audio_buffer_t;

class BufferQueue {
public:
    BufferQueue(size_t bufferSize = 480, size_t queueLength = 10, TickType_t timeout = portMAX_DELAY);
    size_t getBufferSize() const;
    size_t getQueueLength() const;
    bool push(void* buffer);
    bool pop(void* out);
      
private:
    size_t buffer_size_ = 480;
    size_t queue_length_ = 10;
    TickType_t timeout = portMAX_DELAY;
    QueueHandle_t queue;
};

#endif