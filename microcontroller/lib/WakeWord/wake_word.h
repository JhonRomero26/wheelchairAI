#ifndef wake_word_h
#define wake_word_h

#include "wake_word_model.cc"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

void setup_model();
bool register_streaming_op(tflite::MicroMutableOpResolver<20> &op_resolver);
int8_t *getInputBuffer();
int predict();


class WakeWord {
  private:
    static constexpr int kArenaSize = 26080;
    tflite::MicroMutableOpResolver<20> *resolver;
    tflite::ErrorReporter *error_reporter;
    const tflite::Model *model;
    tflite::MicroInterpreter *interpreter;
    
    TfLiteTensor *input, *output;
    uint8_t tensor_arena[kArenaSize];
  
  public:
    void setup();
    int predict();
    int8_t* getInputBuffer();
    TfLiteTensor* getInputTensor();
    bool register_streaming_op(tflite::MicroMutableOpResolver<20> &op_resolver);
};

#endif