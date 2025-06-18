#include "streaming_model.h"


StreamingModel::StreamingModel(const uint8_t* model_start, size_t tensor_arena_size, uint8_t probability_cutoff,
  size_t sliding_window_size)
    : model_start_(model_start),
      tensor_arena_size_(tensor_arena_size),
      probability_cutoff_(probability_cutoff),
      fft_(vReal_, vImag_, FFT_SIZE, 16000, true),
      sliding_window_size_(sliding_window_size) {
  recent_streaming_probabilities_.resize(sliding_window_size_, 0);
}
StreamingModel::~StreamingModel() {
  unload_model();
}

bool StreamingModel::load_model() {
  if (interpreter_ != nullptr) return true;  // Ya está cargado

  error_reporter_ = new tflite::MicroErrorReporter();
  tensor_arena_ = new uint8_t[tensor_arena_size_];
  
  tflite::MicroMutableOpResolver<20> op_resolver;
  if (!register_streaming_ops(op_resolver)) return false;

  ma_ = tflite::MicroAllocator::Create(tensor_arena_, tensor_arena_size_, error_reporter_);
  if (!ma_) {
    TF_LITE_REPORT_ERROR(
      error_reporter_, "MicroAllocator resource variables failed"
    );
    return false;
  }

  mrv_ = tflite::MicroResourceVariables::Create(ma_, 20);
  if (!mrv_) {
    TF_LITE_REPORT_ERROR(
      error_reporter_, "MicroResourceVariables resource variables failed"
    );
    return false;
  }

  if (!tensor_arena_) {
    TF_LITE_REPORT_ERROR(
      error_reporter_, "MicroAllocator resource variables failed"
    );
    return false;
  }

  model_ = tflite::GetModel(model_start_);
  if (model_->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(
      error_reporter_, "Model provided is schema version %d not equal to supported version %d.", model_->version(), TFLITE_SCHEMA_VERSION
    );
    return false;
  }

  interpreter_ = new tflite::MicroInterpreter(
     model_, op_resolver, ma_, error_reporter_, mrv_);

  if (interpreter_->AllocateTensors() != kTfLiteOk) {
    unload_model();
    TF_LITE_REPORT_ERROR(error_reporter_,
      "AllocateTensors() failed even after passing resource variables.");
    return false;
  }

  loaded_ = true;
  reset_probabilities();
  return true;
}

void StreamingModel::unload_model() {
  delete model_;
  model_ = nullptr;
  delete interpreter_;
  interpreter_ = nullptr;
  delete[] tensor_arena_;
  tensor_arena_ = nullptr;
  loaded_ = false;
}

bool StreamingModel::perform_streaming_inference(const int8_t features[]) {
  if (!loaded_) return false;

  TfLiteTensor* input = interpreter_->input(0);
  uint8_t stride = input->dims->data[1];

  std::memmove((int8_t*)(tflite::GetTensorData<int8_t>(input)) + 40 * (last_n_index_ % stride), features, 40);

  if (++last_n_index_ % stride == 0) {
    if (interpreter_->Invoke() != kTfLiteOk) return false;

    TfLiteTensor* output = interpreter_->output(0);
    recent_streaming_probabilities_[last_n_index_ % sliding_window_size_] = output->data.uint8[0];
  }

  return true;
}


size_t StreamingModel::generate_features(int16_t* audio_buffer, int samples_available) {
  if (samples_available < AUDIO_BUFFER_SIZE) return 0;

  for (size_t window = 0; window < NUM_WINDOWS; window++) {
    for (size_t i = 0; i < FFT_SIZE; i++) {
      vReal_[i] = audio_buffer[window * SAMPLES_PER_WINDOW + i];
    }

    fft_.compute(FFTDirection::Forward);
    fft_.complexToMagnitude(vReal_, vImag_, FFT_SIZE);

    for (size_t i = 0; i < FEATURE_SIZE; i++) {
      size_t start = (FFT_SIZE / 2) * i / FEATURE_SIZE;
      size_t end = (FFT_SIZE / 2) * (i + 1) / FEATURE_SIZE;
      double avg = 0;

      for (size_t j = start; j < end; j++) {
        avg += vReal_[j];
      }

      avg /= end - start;

      features_buffer[window * FEATURE_SIZE + i] = static_cast<int8_t>(
        clamp(avg / 256, INT8_MIN, INT8_MAX)
      );
    }
  }

  return NUM_WINDOWS * FEATURE_SIZE;  
}

void StreamingModel::reset_probabilities() {
  std::fill(recent_streaming_probabilities_.begin(), recent_streaming_probabilities_.end(), 0);
  last_n_index_ = 0;
  ignore_windows_ = -5;
}

StreamingModel::DetectionEvent StreamingModel::determine_detected() {
  DetectionEvent event;
  event.detected = false;
  event.max_probability = 0;
  event.average_probability = 0;

  if (ignore_windows_ >= 0 || !loaded_) return event;

  uint32_t sum = 0;
  for (auto prob : recent_streaming_probabilities_) {
    event.max_probability = std::max(event.max_probability, prob);
    sum += prob;
  }

  event.average_probability = sum / sliding_window_size_;
  event.detected = sum > probability_cutoff_ * sliding_window_size_;
  ignore_windows_ = 0;  // Reiniciar contador de ventanas ignoradas

  return event;
}

int8_t* StreamingModel::getFeatures() {
  return features_buffer;
}

bool StreamingModel::register_streaming_ops(tflite::MicroMutableOpResolver<20>& op_resolver) {
  if (op_resolver.AddCallOnce() != kTfLiteOk) return false;
  if (op_resolver.AddVarHandle() != kTfLiteOk) return false;
  if (op_resolver.AddReshape() != kTfLiteOk) return false;
  if (op_resolver.AddReadVariable() != kTfLiteOk) return false;
  if (op_resolver.AddStridedSlice() != kTfLiteOk) return false;
  if (op_resolver.AddConcatenation() != kTfLiteOk) return false;
  if (op_resolver.AddAssignVariable() != kTfLiteOk) return false;
  if (op_resolver.AddConv2D() != kTfLiteOk) return false;
  if (op_resolver.AddMul() != kTfLiteOk) return false;
  if (op_resolver.AddAdd() != kTfLiteOk) return false;
  if (op_resolver.AddMean() != kTfLiteOk) return false;
  if (op_resolver.AddFullyConnected() != kTfLiteOk) return false;
  if (op_resolver.AddLogistic() != kTfLiteOk) return false;
  if (op_resolver.AddQuantize() != kTfLiteOk) return false;
  if (op_resolver.AddDepthwiseConv2D() != kTfLiteOk) return false;
  if (op_resolver.AddAveragePool2D() != kTfLiteOk) return false;
  if (op_resolver.AddMaxPool2D() != kTfLiteOk) return false;
  if (op_resolver.AddPad() != kTfLiteOk) return false;
  if (op_resolver.AddPack() != kTfLiteOk) return false;
  if (op_resolver.AddSplitV() != kTfLiteOk) return false;

  return true;
}