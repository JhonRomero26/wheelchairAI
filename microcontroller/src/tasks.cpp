#include "BufferQueue.h"
#include "Microphone.h"
#include "streaming_model.h"


extern BufferQueue micQueue;
extern Microphone mic;
extern StreamingModel wakeWord;

void microphoneTask(void* pvParams) {
  while (true) {
    size_t num_samples = micQueue.getBufferSize();
    int16_t* pBuffer = (int16_t*)malloc(num_samples * sizeof(int16_t));

    if (!pBuffer) {
      Serial.println("Error: no se pudo asignar memoria");
      vTaskDelay(pdMS_TO_TICKS(1000)); // Espera antes de reintentar
      continue;
    }

    if (!mic.readAudio(pBuffer, num_samples)) {
      free(pBuffer);
    }

    if (!micQueue.push(pBuffer)) {
      free(pBuffer);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void speechTask(void* pvParams) {
  while (true) {
    int16_t* pBuffer;

    if (!micQueue.pop(&pBuffer)) {
      vTaskDelay(pdMS_TO_TICKS(50));
      continue;
    }

    size_t num_samples = micQueue.getBufferSize();
    // float* features = wakeWord.generate_features(pBuffer, num_samples);
    // size_t num_features = sizeof(features) / sizeof(features[0]);
    
    // Aquí puedes hacer lo que necesites con las características
    for (size_t i = 0; i < num_samples; i++) {
      Serial.print(">Audio: ");
      Serial.println(pBuffer[i]);
    }
    
    // Liberar el buffer después de procesarlo
    free(pBuffer);
  }
}
