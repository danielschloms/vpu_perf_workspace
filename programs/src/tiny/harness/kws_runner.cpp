/*
 * MLPerf Tiny Keyword Spotting (KWS) inference runner for the Vicuna2/Verilator
 * model.  Runs the pretrained int8 DS-CNN model through tflite-micro once, on a
 * fixed 10x49x1 input, and reports the 12-class softmax output.
 *
 * This is a self-contained, host-command-free runner (no EEMBC/mbed serial
 * protocol): it loads the bundled input, invokes the interpreter, and returns
 * 0 when the top-1 class matches the expected label (used by the harness to
 * drive the Vicuna2 0x408 MMIO pass/fail signal).
 */

#include "kws/kws_model_data.h"
#include "kws/kws_model_settings.h"

#include <cstdint>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/schema/schema_generated.h"

// The runner prints diagnostics; the sink differs per simulator.
//   * Verilator (Vicuna2): the runtime's limited uart_printf (no %zu, no floats)
//   * ETISS:               hosted stdio (printf) via semihosting
#if defined(KWS_UART)
#include "uart.hpp"                          // Vicuna2 runtime uart_printf
#define KWS_PRINTF uart_printf
#else
#include <cstdio>                            // ETISS: hosted stdout
#define KWS_PRINTF printf
#endif

namespace {

constexpr int kTensorArenaSize = 200 * 1024;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

// Pretrained int8 KWS input (10x49x1 = kKwsInputSize).  Taken from the
// reference submission's kws/kws_input_data.cc, re-hosted here so this harness
// does not depend on mbed.h.
constexpr int8_t kInput[kKwsInputSize] = {
  76, 77, 85, 83, 88, 83, 82, 87, 87, 84, 64, 81, 83, 87, 87, 83,  //
  84, 86, 87, 85, 55, 85, 85, 86, 86, 85, 85, 84, 84, 84, 55, 85,  //
  85, 86, 84, 84, 85, 84, 84, 86, 51, 84, 85, 86, 85, 85, 85, 84,  //
  86, 84, 80, 87, 80, 79, 86, 88, 83, 85, 83, 86, 88, 88, 84, 79,  //
  87, 88, 81, 84, 83, 85, 111, 88, 85, 78, 86, 87, 84, 84, 82, 85,  //
  109, 89, 86, 77, 86, 87, 83, 84, 83, 85, 107, 90, 85, 78, 87, 87,  //
  83, 83, 83, 85, 106, 93, 85, 76, 87, 86, 84, 84, 82, 86, 109, 93,  //
  82, 77, 87, 87, 83, 84, 82, 86, 109, 93, 83, 77, 86, 89, 83, 83,  //
  83, 86, 111, 92, 83, 78, 86, 88, 83, 84, 83, 86, 112, 90, 83, 79,  //
  86, 88, 82, 84, 83, 86, 110, 92, 82, 80, 87, 87, 81, 84, 83, 85,  //
  110, 91, 82, 81, 87, 86, 81, 86, 84, 85, 107, 93, 80, 84, 86, 85,  //
  83, 86, 84, 83, 104, 91, 85, 84, 85, 83, 84, 86, 84, 83, 103, 90,  //
  86, 86, 84, 82, 85, 85, 84, 83, 96, 88, 89, 89, 83, 83, 84, 84,  //
  85, 82, 90, 89, 90, 91, 83, 83, 83, 84, 85, 82, 89, 89, 90, 90,  //
  81, 86, 84, 83, 84, 83, 89, 90, 89, 89, 82, 85, 85, 84, 84, 83,  //
  86, 90, 90, 90, 82, 85, 85, 84, 83, 84, 72, 92, 90, 92, 82, 85,  //
  85, 83, 83, 84, 67, 89, 90, 89, 84, 86, 84, 85, 84, 84, 60, 88,  //
  87, 89, 84, 85, 85, 86, 83, 84, -128, 84, 85, 85, 85, 84, 85, 85,  //
  85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85,  //
  85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85,  //
  -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84,  //
  85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84,  //
  85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85,  //
  85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85,  //
  85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85,  //
  -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84,  //
  85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84,  //
  85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85,  //
  85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85, -128, 84, 85, 85,  //
  85, 84, 85, 85, 85, 85, -128, 84, 85, 85, 85, 84, 85, 85, 85, 85,  //
  -128, 84, 85, 85, 85, 84, 85, 85, 85, 85,
};

// Expected top-1 class for the kInput sample.  Filled in from an identical host
// run of the same model + tflite-micro (int8 inference is exact integer
// arithmetic, so the result is deterministic across platforms).  Here the KWS
// sample is unambiguously classified as "on" (class 5).
constexpr int kExpectedLabel = 5;

}  // namespace

extern "C" int run_kws(void) {
  KWS_PRINTF("KWS: tflite-micro %d, model bytes=%u\n",
              TFLITE_SCHEMA_VERSION, g_kws_model_data_len);

  if (g_kws_model_data_len == 0) {
    KWS_PRINTF("KWS: bad model data\n");
    return 1;
  }

  const tflite::Model* model = tflite::GetModel(g_kws_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    KWS_PRINTF("KWS: model schema %d != tflm %d\n", model->version(),
                TFLITE_SCHEMA_VERSION);
    return 1;
  }

  tflite::MicroMutableOpResolver<6> resolver;
  TfLiteStatus status;
  status = resolver.AddFullyConnected();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddFullyConnected failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddConv2D();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddConv2D failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddDepthwiseConv2D();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddDepthwiseConv2D failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddReshape();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddReshape failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddSoftmax();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddSoftmax failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddAveragePool2D();
  if (status != kTfLiteOk) { KWS_PRINTF("KWS: AddAveragePool2D failed (%d)\n", static_cast<int>(status)); return 1; }

  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,
                                       kTensorArenaSize);

  status = interpreter.AllocateTensors();
  if (status != kTfLiteOk) {
    KWS_PRINTF("KWS: AllocateTensors failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* input = interpreter.input(0);
  if (input->bytes != static_cast<size_t>(kKwsInputSize * sizeof(int8_t))) {
    KWS_PRINTF("KWS: input bytes %u != expected %d\n", (unsigned)input->bytes,
                kKwsInputSize);
    return 1;
  }
  int8_t* input_buf = tflite::GetTensorData<int8_t>(input);
  for (int i = 0; i < kKwsInputSize; i++) {
    input_buf[i] = kInput[i];
  }

  KWS_PRINTF("KWS: invoking...\n");
  status = interpreter.Invoke();
  if (status != kTfLiteOk) {
    KWS_PRINTF("KWS: Invoke failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* output = interpreter.output(0);
  const int8_t* out_buf = tflite::GetTensorData<int8_t>(output);
  const int num_out = static_cast<int>(output->bytes);
  const float scale = output->params.scale;
  const int32_t zero_point = output->params.zero_point;

  KWS_PRINTF("KWS: outputs (%d): [", num_out);
  int best = 0;
  int best_permille = -1;
  for (int i = 0; i < num_out; ++i) {
    const float value = static_cast<float>(out_buf[i] - zero_point) * scale;
    const int permille = static_cast<int>(value * 1000.0f + 0.5f);
    if (permille > best_permille) {
      best_permille = permille;
      best = i;
    }
    // 0.xxx (uart_printf has no float support, so use integer permille)
    KWS_PRINTF("0.%03d", permille);
    if (i < num_out - 1) KWS_PRINTF(",");
  }
  KWS_PRINTF("]\n");

  KWS_PRINTF("KWS: top-1 = %d (%s), p~0.%03d, expected=%d (%s)\n", best,
              kCategoryLabels[best], best_permille, kExpectedLabel,
              (kExpectedLabel >= 0 && kExpectedLabel < kCategoryCount)
                  ? kCategoryLabels[kExpectedLabel]
                  : "?");

  return best == kExpectedLabel ? 0 : 1;
}
