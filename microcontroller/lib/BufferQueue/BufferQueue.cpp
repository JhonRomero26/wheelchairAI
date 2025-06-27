#include "BufferQueue.h"


BufferQueue::BufferQueue(size_t bufferSize, size_t queueLength, TickType_t timemout) {
  buffer_size_ = bufferSize;
  queue_length_ = queueLength;
  timeout = timemout;
  queue = xQueueCreate(queueLength, sizeof(audio_buffer_t*));
}

size_t BufferQueue::getBufferSize() const {
  return buffer_size_;
}

size_t BufferQueue::getQueueLength() const {
  return queue_length_;
}

bool BufferQueue::push(void* buffer) {
  return xQueueSend(queue, &buffer, NULL) == pdTRUE;
}

bool BufferQueue::pop(void* out) {
  return xQueueReceive(queue, out, NULL) == pdTRUE;
}
