#include "/home/yatharthdedhia/tensorflow/tensorflow/lite/micro/all_ops_resolver.h"
#include "/home/yatharthdedhia/tensorflow/tensorflow/lite/micro/micro_error_reporter.h"
#include "/home/yatharthdedhia/tensorflow/tensorflow/lite/micro/micro_interpreter.h"
#include "/home/yatharthdedhia/tensorflow/tensorflow/lite/schema/schema_generated.h"
#include "/home/yatharthdedhia/tensorflow/tensorflow/lite/version.h"

#include "model_effnet.h"

TF_LITE_MICRO_TESTS_BEGIN

TF_LITE_MICRO_TEST(LoadModelAndPerformInference) 
{
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

const tflite::Model* model = ::tflite::GetModel(g_model);
if (model->version() != TFLITE_SCHEMA_VERSION) {
  TF_LITE_REPORT_ERROR(error_reporter,
      "Model provided is schema version %d not equal "
      "to supported version %d.\n",
      model->version(), TFLITE_SCHEMA_VERSION);
}

tflite::AllOpsResolver resolver;

const int tensor_arena_size = 100 * 1024;
uint8_t tensor_arena[tensor_arena_size];

tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,tensor_arena_size, error_reporter);

interpreter.AllocateTensors();



TF_LITE_MICRO_TESTS_END