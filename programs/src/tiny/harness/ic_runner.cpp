/*
 * MLPerf Tiny Image Classification (ResNet-8, int8) inference runner for the
 * Vicuna2/Verilator + ETISS harness.  Runs the pretrained int8 model once on
 * the reference submission's fixed input image (reinterpreted per the
 * reference: uint8 - 128 -> int8), and reports the 10-class softmax output.
 *
 * Self-contained, host-command-free (no EEMBC/mbed serial protocol): loads the
 * bundled input, invokes the interpreter, and returns 0 when the top-1 class
 * matches the expected label (used to drive the Vicuna2 0x408 MMIO pass/fail
 * signal and the ETISS exit code).
 */

#include <cstdint>

#include "ic/ic_model_quant_data.h"
#include "ic/ic_model_settings.h"
#include "ic/ic_inputs.h"

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/schema/schema_generated.h"

// Diagnostic sink differs per simulator:
//   * Verilator (Vicuna2): the runtime's limited uart_printf (no %zu, no floats)
//   * ETISS:               hosted stdio (printf)
#if defined(TINY_UART)
#include "uart.hpp"
#define IC_PRINTF uart_printf
#else
#include <cstdio>
#define IC_PRINTF printf
#endif

namespace {

constexpr int kTensorArenaSize = 200 * 1024;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

// Expected top-1 class for the fixed input sample (kNumIcTestInputs==1, an
// all-zeros uint8 image that the reference re-centres to int8 -128).  Measured
// from an identical ETISS/Vicuna2 run of the same model + tflite-micro; int8
// inference is exact integer arithmetic so the result is deterministic across
// platforms.  The all-zeros image is classified as class 0 ("airplane").
constexpr int kExpectedIcLabel = 0;

}  // namespace

extern "C" int run_ic(void) {
  IC_PRINTF("IC: tflite-micro %d, model bytes=%u\n", TFLITE_SCHEMA_VERSION,
            pretrainedResnet_quant_tflite_len);

  if (pretrainedResnet_quant_tflite_len == 0) {
    IC_PRINTF("IC: bad model data\n");
    return 1;
  }

  const tflite::Model* model = tflite::GetModel(pretrainedResnet_quant_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    IC_PRINTF("IC: model schema %d != tflm %d\n",
              static_cast<int>(model->version()), TFLITE_SCHEMA_VERSION);
    return 1;
  }

  // Ops: CONV_2D x7, ADD x3, AVERAGE_POOL_2D, RESHAPE, FULLY_CONNECTED,
  // SOFTMAX (from the reference ResNet-8 int8 graph).
  tflite::MicroMutableOpResolver<6> resolver;
  TfLiteStatus status;
  status = resolver.AddConv2D();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddConv2D failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddAdd();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddAdd failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddAveragePool2D();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddAveragePool2D failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddReshape();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddReshape failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddFullyConnected();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddFullyConnected failed (%d)\n", static_cast<int>(status)); return 1; }
  status = resolver.AddSoftmax();
  if (status != kTfLiteOk) { IC_PRINTF("IC: AddSoftmax failed (%d)\n", static_cast<int>(status)); return 1; }

  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,
                                       kTensorArenaSize);

  status = interpreter.AllocateTensors();
  if (status != kTfLiteOk) {
    IC_PRINTF("IC: AllocateTensors failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* input = interpreter.input(0);
  if (input->bytes != static_cast<size_t>(kIcInputSize * sizeof(int8_t))) {
    IC_PRINTF("IC: input bytes %u != expected %d\n", (unsigned)input->bytes,
              kIcInputSize);
    return 1;
  }
  // Reference recentres the uint8 test image: int8 = (int)uint8 - 128.
  int8_t* input_buf = tflite::GetTensorData<int8_t>(input);
  for (int i = 0; i < kIcInputSize; i++) {
    input_buf[i] = static_cast<int8_t>(static_cast<int>(g_ic_inputs[0][i]) - 128);
  }

  IC_PRINTF("IC: invoking...\n");
  status = interpreter.Invoke();
  if (status != kTfLiteOk) {
    IC_PRINTF("IC: Invoke failed (%d)\n", static_cast<int>(status));
    return 1;
  }

  TfLiteTensor* output = interpreter.output(0);
  const int8_t* out_buf = tflite::GetTensorData<int8_t>(output);
  const int num_out = static_cast<int>(output->bytes);
  // Softmax output is the argmax of the int8 logits (softmax is monotonic).
  IC_PRINTF("IC: outputs (%d): [", num_out);
  int best = 0;
  int best_permille = -1;
  for (int i = 0; i < num_out; ++i) {
    // prob = (q - zp) * scale with zp==-128, scale==1/256 for the softmax op.
    const int permille = static_cast<int>((out_buf[i] + 128) * 1000 / 256);
    if (permille > best_permille) {
      best_permille = permille;
      best = i;
    }
    IC_PRINTF("0.%03d", permille);
    if (i < num_out - 1) IC_PRINTF(",");
  }
  IC_PRINTF("]\n");

  IC_PRINTF("IC: top-1 = %d, p~0.%03d, expected=%d\n", best, best_permille,
            kExpectedIcLabel);

  return best == kExpectedIcLabel ? 0 : 1;
}
