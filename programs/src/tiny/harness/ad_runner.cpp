/*
 * MLPerf Tiny Anomaly Detection (int8 autoencoder) inference runner for the
 * Vicuna2/Verilator + ETISS harness.
 *
 * Runs the pretrained int8 model once on the reference submission's fixed
 * input (the first 640 float of the dcase01 normal clip, pre-quantized to the
 * model's int8 input/zero-point), then computes the reference reconstruction
 * error: mean((dequantized_output - original_float_input)^2).  Returns 0 when
 * that score matches the expected value within tolerance.
 *
 * Self-contained, host-command-free (no EEMBC/mbed serial protocol).
 */

#include "micro_model_settings.h"   // kFeatureElementCount
#include "model.h"                  // g_model[]
#include "ad_input_data.h"          // kAdInputQ8[], kAdInputF[]

#include <cstdint>
#include <cmath>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/schema/schema_generated.h"

#if defined(TINY_UART)
#include "uart.hpp"
#define AD_PRINTF uart_printf
#else
#include <cstdio>
#define AD_PRINTF printf
#endif

namespace {

constexpr int kTensorArenaSize = 200 * 1024;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

// g_model[] (model.h) is declared as an incomplete array, so we hard-code its
// byte length (from anomaly_detection/model.cc).
constexpr unsigned kAdModelLen = 276976;

// Expected reconstruction error (mean squared) for the fixed input, measured
// from an identical ETISS run.  The int8 autoencoder is exact integer
// arithmetic, so the dequantized output is deterministic across platforms; the
// remaining float work (dequant + MSE) is IEEE 754, so the score reproduces to
// within float accumulation rounding everywhere.
constexpr float kExpectedAdScore = 11.676168f;
// Relative tolerance for the float reconstruction error across simulators.
constexpr float kAdScoreTol = 0.03f;

}  // namespace

extern "C" int run_ad(void) {
  AD_PRINTF("AD: tflite-micro %d, model bytes=%u\n", TFLITE_SCHEMA_VERSION,
            (unsigned)kAdModelLen);

  const tflite::Model* model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    AD_PRINTF("AD: model schema %d != tflm %d\n",
              static_cast<int>(model->version()), TFLITE_SCHEMA_VERSION);
    return 1;
  }

  // Graph: 10x FULLY_CONNECTED (int8 autoencoder).  Register the FC op plus the
  // QUANTIZE/DEQUANTIZE ops as the reference submission does, so we are robust
  // to any helper nodes in the graph.
  tflite::MicroMutableOpResolver<3> resolver;
  TfLiteStatus status;
  status = resolver.AddFullyConnected();
  if (status != kTfLiteOk) { AD_PRINTF("AD: AddFullyConnected failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddQuantize();
  if (status != kTfLiteOk) { AD_PRINTF("AD: AddQuantize failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddDequantize();
  if (status != kTfLiteOk) { AD_PRINTF("AD: AddDequantize failed (%d)\n", static_cast<int>(status)); return 1; }

  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,
                                       kTensorArenaSize);

  status = interpreter.AllocateTensors();
  if (status != kTfLiteOk) {
    AD_PRINTF("AD: AllocateTensors failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* input = interpreter.input(0);
  if (input->bytes != static_cast<size_t>(kFeatureElementCount * sizeof(int8_t))) {
    AD_PRINTF("AD: input bytes %u != expected %d\n", (unsigned)input->bytes,
              kFeatureElementCount);
    return 1;
  }
  int8_t* input_buf = tflite::GetTensorData<int8_t>(input);
  for (int i = 0; i < kFeatureElementCount; i++) {
    input_buf[i] = kAdInputQ8[i];
  }

  AD_PRINTF("AD: invoking...\n");
  status = interpreter.Invoke();
  if (status != kTfLiteOk) {
    AD_PRINTF("AD: Invoke failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* output = interpreter.output(0);
  const int8_t* out_buf = tflite::GetTensorData<int8_t>(output);
  const float out_scale = output->params.scale;
  const int32_t out_zp = output->params.zero_point;

  // Reference reconstruction error: mean((dequant_out - float_input)^2).
  // Float accumulation to match the reference submission's calculate_result().
  float diffsum = 0.0f;
  for (int i = 0; i < kFeatureElementCount; i++) {
    const float converted = static_cast<float>(out_buf[i] - out_zp) * out_scale;
    const float diff = converted - kAdInputF[i];
    diffsum += diff * diff;
  }
  const float score = diffsum / static_cast<float>(kFeatureElementCount);

  const float diff =
      static_cast<float>(std::fabs(static_cast<double>(score - kExpectedAdScore)));
  const bool pass = diff <= kAdScoreTol * (1.0f + std::fabs(kExpectedAdScore));

  // Neither the Vicuna2 uart_printf nor the tflm eyalroz printf pulled into the
  // ETISS build supports floats safely (the latter has a riscv pcrel linker
  // overflow in its float path), so scale to an integer.  Use 1e3 on the
  // limited uart and 1e6 on ETISS (hosted stdio) for golden-value precision.
#if defined(TINY_UART)
  AD_PRINTF("AD: score=%d (mse*1000), expected=%d, tol=%d\n",
            static_cast<int>(score * 1000.0f),
            static_cast<int>(kExpectedAdScore * 1000.0f),
            static_cast<int>(kAdScoreTol * 1000.0f));
#else
  AD_PRINTF("AD: score=%d (mse*1e6), expected=%d (mse*1e6), tol=%d (mse*1e3)\n",
            static_cast<int>(score * 1000000.0f),
            static_cast<int>(kExpectedAdScore * 1000000.0f),
            static_cast<int>(kAdScoreTol * 1000.0f));
#endif
  AD_PRINTF("AD: %s\n", pass ? "PASS" : "FAIL");
  return pass ? 0 : 1;
}
