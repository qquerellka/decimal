#include "s21_utils.h"

#include <math.h>
#include <stdio.h>

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

  result = (double_value > FLOAT_MAX_VALUE);

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

s21_FloatUint32_t s21_pack_float_in_int_box(float float_value) {
  s21_FloatUint32_t result_box = {0};

  result_box.float_value = float_value;

  return result_box;
}

unsigned char s21_get_float_sign(uint32_t float_box) {
  unsigned char result_sign = 0;
  unsigned char current_mask = 1;

  if (((float_box >> FLOAT_SIGN_BIT) & current_mask) == current_mask) {
    result_sign = 1;
  }

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

s21_FloatDescriptor_t s21_get_float_data(s21_FloatUint32_t float_box) {
  s21_FloatDescriptor_t result_descriptor = {0};

  result_descriptor.is_minus_sign = s21_get_float_sign(float_box.uint_value);
  if (result_descriptor.is_minus_sign) {
    float_box.float_value = -float_box.float_value;
  }

  printf("float value = %f\n", float_box.float_value);

  char sprintf_buffer[16] = {0};
  double temp_value = 0;
  sprintf(sprintf_buffer, "%.6E", (double)float_box.float_value);

  sscanf(sprintf_buffer, "%lf", &temp_value);

  printf("value in growth up = %lf\n", temp_value);

  int scale = 0;
  uint32_t int_value = 0;

  while (temp_value != 0 && temp_value < 1.0) {
    temp_value *= 10.0;

    scale--;
  }

  while (temp_value >= 10.0) {
    temp_value /= 10.0;

    scale++;
  }

  int_value = (uint32_t)(temp_value * 1e6);
  scale -= 6;

  result_descriptor.scale = scale;
  result_descriptor.mantisa = int_value;

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

double s21_get_multiplied_result(double decimal_mantissa_value) {
  return (double)decimal_mantissa_value * 10;
}

double s21_get_frac_result(double decimal_mantissa_value) {
  return (double)decimal_mantissa_value / 10;
}

void s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, s21_FloatUint32_t *float_box) {
  // int is_scale_negative = 0;
  int scale = 0;
  double result_value = 0;
  double (*operation)(double) = NULL;

  result_value = (double)float_descriptor->mantisa;

  scale = float_descriptor->scale;

  if (scale < 0) {
    // is_scale_negative = 1;
    scale = -scale;
    operation = s21_get_frac_result;
  } else {
    operation = s21_get_multiplied_result;
  }

  for (int i = 0; i < scale; i++) {
    result_value = operation(result_value);
  }

  printf("result %lf\n", result_value);

  if (float_descriptor->is_minus_sign) {
    result_value = -result_value;
  }

  float_box->float_value = (float)result_value;
  // s21_set_float_sign(float_descriptor, &dst->uint_value);

  // s21_set_float_scale(float_descriptor, &dst->uint_value);

  // s21_set_float_mantisa(float_descriptor, &dst->uint_value);
}