#include <stdint.h>

#include "s21_decimal.h"

#define FLOAT_SIGN_BIT 31
#define FLOAT_GET_SIGN_MASK 0xff
#define FLOAT_SCALE_EXIST_MASK 0x80000000
#define FLOAT_MANTISA_MASK 0xffffffff
#define FLOAT_MANTISA_BITS 22
#define FLOAT_MANTISA_SHIFT 9
#define FLOAT_SCALE_STEP 127
#define FLOAT_MAX_SCALE 255
#define FLOAT_MIN_SCALE 0

typedef union float_uint32_t {
  float float_value;
  uint32_t uint_value;
} FloatUint32_t;

typedef struct float_descriptor {
  uint32_t mantissa;
  unsigned char is_minus_sign;
  unsigned char scale;
} FloatDescriptor_t;

int from_f_to_d(float src, s21_decimal *dst);

int from_d_to_f(s21_decimal src, float *dst);