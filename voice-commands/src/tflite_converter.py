import tensorflow as tf

# Ruta al directorio del modelo SavedModel
saved_model_dir = './trained/non_stream/'

# Cargar el convertidor de TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_saved_model(saved_model_dir)

# Opciones adicionales (opcional)
converter.optimizations = [tf.lite.Optimize.DEFAULT]  # Optimización básica
converter.target_spec.supported_ops = [
    tf.lite.OpsSet.TFLITE_BUILTINS,  # Operaciones integradas de TFLite
    tf.lite.OpsSet.SELECT_TF_OPS     # Operaciones personalizadas de TensorFlow (si es necesario)
]

# Realizar la conversión
tflite_model = converter.convert()

# Guardar el modelo TFLite en un archivo
output_tflite_model_path = './modelo_convertido.tflite'
with open(output_tflite_model_path, 'wb') as f:
    f.write(tflite_model)

print(f"Modelo TFLite guardado en: {output_tflite_model_path}")