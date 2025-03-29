#include "s21_utils.h"

#include <math.h>

int s21_is_float_nan(s21_FloatUint32_t float_box) {
  int is_nan_result = 0;

  if ((float_box.uint_value & FLOAT_POSITIVE_NAN_MASK) ==
      FLOAT_POSITIVE_NAN_MASK) {
    is_nan_result = 1;
  }
  return is_nan_result;
}

int s21_is_float_zero(s21_FloatUint32_t float_box) {
  int is_zero_result = 0;

  if (float_box.uint_value == FLOAT_POSITIVE_ZERO_MASK) {
    is_zero_result = 1;
  } else if (float_box.uint_value == FLOAT_NEGATIVE_ZERO_MASK) {
    is_zero_result = 1;
  }

  return is_zero_result;
}

int s21_is_float_overflow(double double_value) {
  int result = 0;

  if (double_value < 0) {
    double_value = -double_value;
  }

  result = (double_value >=
            pow(FLOAT_BASE_OF_THE_EXPONENT, FLOAT_OVERFLOW_EXPONENT_SCALE));

  return result;
}

int s21_is_float_too_small(double double_value) {
  int result = 0;

  if (double_value < 0) {
    double_value = -double_value;
  }

  result = (double_value <= FLOAT_TOO_SMALL);

  return result;
}

float s21_round_float_to_7(float float_value) {
  float result_float = 0;
  int is_negative = 0;
  int integer_numbers_count = 0;
  int fractional_numbers_count = 0;
  double power_factor = 0;
  double temp_result = 0;

  if (float_value < 0) {
    is_negative = 1;
    float_value *= -1;
  }

  integer_numbers_count = (int)ceil(log10(float_value));

  fractional_numbers_count = FLOAT_ROUND_SIGN - integer_numbers_count;

  power_factor = pow(10, (double)fractional_numbers_count);

  temp_result = round(float_value * power_factor);

  temp_result = temp_result / power_factor;

  if (is_negative) {
    temp_result *= -1;
  }

  result_float = temp_result;

  return result_float;
}

s21_FloatUint32_t s21_pack_float_in_int_box(float float_value) {
  s21_FloatUint32_t result_box = {0};

  result_box.float_value = float_value;

  return result_box;
}

unsigned char s21_get_float_sign(uint32_t float_box) {
  unsigned char result_sign = 0;
  unsigned char current_mask = 1;

  if (((float_box >> FLOAT_SIGN_BIT) & current_mask) == current_mask)
    result_sign = 1;

  return result_sign;
}

char s21_get_float_scale(uint32_t float_box) {
  char result_scale = 0;
  uint32_t temp_scale = 0;

  temp_scale = float_box & FLOAT_GET_SIGN_MASK;
  temp_scale >>= FLOAT_MANTISA_BITS;
  temp_scale -= 127;

  result_scale = (char)temp_scale;

  return result_scale;
}

uint32_t s21_get_float_mantisa(uint32_t float_box) {
  uint32_t result_mantiss = 0;

  result_mantiss = float_box & FLOAT_MANTISA_MASK;

  return result_mantiss;
}

s21_FloatDescriptor_t s21_get_float_data(uint32_t float_box) {
  s21_FloatDescriptor_t result_descriptor = {0};
  result_descriptor.is_minus_sign = s21_get_float_sign(float_box);
  result_descriptor.scale = s21_get_float_scale(float_box);
  result_descriptor.mantisa = s21_get_float_mantisa(float_box);

  return result_descriptor;
}

void s21_set_float_sign(s21_FloatDescriptor_t *float_descriptor,
                        uint32_t *dst) {
  uint32_t tmp_int_map = 0;

  tmp_int_map = *dst;

  if (float_descriptor->is_minus_sign) {
    tmp_int_map = 1;
    tmp_int_map <<= FLOAT_SIGN_BIT;
  }

  *dst = tmp_int_map;
}

void s21_set_float_scale(s21_FloatDescriptor_t *float_descriptor,
                         uint32_t *dst) {
  uint32_t scale_mask = 0;

  scale_mask = float_descriptor->scale;

  scale_mask += FLOAT_SCALE_STEP;

  scale_mask <<= FLOAT_MANTISA_BITS;

  *dst |= scale_mask;
}

void s21_set_float_mantisa(s21_FloatDescriptor_t *float_descriptor,
                           uint32_t *dst) {
  uint32_t mantisa = 0;

  mantisa = float_descriptor->mantisa;

  mantisa <<= FLOAT_MANTISA_SHIFT;
  mantisa >>= FLOAT_MANTISA_SHIFT;

  *dst |= mantisa;
}

void s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, s21_FloatUint32_t *dst) {
  s21_set_float_sign(float_descriptor, &dst->uint_value);

  s21_set_float_scale(float_descriptor, &dst->uint_value);

  s21_set_float_mantisa(float_descriptor, &dst->uint_value);
}