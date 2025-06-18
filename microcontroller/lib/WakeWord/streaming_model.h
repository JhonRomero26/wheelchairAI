#ifndef STREAMING_MODEL_H
#define STREAMING_MODEL_H

#include <cstdint>
#include <vector>
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_allocator.h"
#include "tensorflow/lite/micro/micro_resource_variable.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "arduinoFFT.h"


#define FFT_SIZE 128                  // Tamaño de la FFT (debe ser potencia de 2)
#define FEATURE_SIZE 40              // Número de bandas de frecuencia
#define SAMPLES_PER_WINDOW 160      // Muestras por ventana de tiempo
#define NUM_WINDOWS 3               // Ventanas consecutivas para la entrada (1,3,40)
#define AUDIO_BUFFER_SIZE (SAMPLES_PER_WINDOW * NUM_WINDOWS)
#define PREPROCESSOR_FEATURE_SIZE (FEATURE_SIZE * NUM_WINDOWS)



class StreamingModel {
public:
  StreamingModel(const uint8_t* model_start, size_t tensor_arena_size, uint8_t probability_cutoff,
                 size_t sliding_window_size);
  ~StreamingModel();

  struct DetectionEvent {
    bool detected;
    uint8_t max_probability;
    uint8_t average_probability;
  };
  
  DetectionEvent determine_detected();
  
  size_t generate_features(int16_t* audio_buffer, int samples_available);
  int8_t* getFeatures(); 
  bool load_model();
  void unload_model();
  bool perform_streaming_inference(const int8_t features[]);
  void reset_probabilities();

  
  private:
  const uint8_t* model_start_;
  static constexpr int kArenaSize = 26080;
  size_t tensor_arena_size_;
  uint8_t probability_cutoff_;
  size_t sliding_window_size_;
  size_t audio_index_ = 0;
  
  ArduinoFFT<double> fft_;
  double vReal_[FFT_SIZE];
  double vImag_[FFT_SIZE];
  double windowing_factors_[FFT_SIZE / 2];
  int8_t features_buffer[PREPROCESSOR_FEATURE_SIZE];
  
  const tflite::Model* model_ = nullptr;
  tflite::MicroInterpreter* interpreter_ = nullptr;
  tflite::ErrorReporter* error_reporter_ = nullptr;
  uint8_t* tensor_arena_ = nullptr;
  tflite::MicroAllocator* ma_ = nullptr;
  tflite::MicroResourceVariables* mrv_ = nullptr;
  
  
  std::vector<uint8_t> recent_streaming_probabilities_;
  size_t last_n_index_ = 0;
  int ignore_windows_ = -5;  // Valor inicial para evitar detecciones duplicadas
  bool loaded_ = false;
  
  bool update_model_probabilities_(const int8_t audio_features[FEATURE_SIZE]);
  bool register_streaming_ops(tflite::MicroMutableOpResolver<20>& op_resolver);
  
  
  template <typename T, typename U>
  T clamp(T value, U min, U max) {
        return (value < static_cast<T>(min)) ? static_cast<T>(min) 
        : (value > static_cast<T>(max)) ? static_cast<T>(max) 
        : value;
      }
};

#endif