#include "s21_utils.h"

int s21_is_float_nan(s21_FloatUint32_t float_box) {
  int is_nan_result = 0;

  if ((float_box.uint_value & FLOAT_POSITIVE_NAN_MASK) ==
      FLOAT_POSITIVE_NAN_MASK) {
    is_nan_result = 1;
  }
  return is_nan_result;
}

//разбить на 2
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

  result = (double_value > S21_MAX);

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

void s21_initialize_decimal_as_zero(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

void s21_set_float_mantisa_in_decimal(s21_decimal *dst, uint32_t uint_value) {
  dst->bits[0] = uint_value;
}

int s21_is_decimal_not_zero(s21_decimal *decimal) {
  int result = 0;

  for (int i = 0; i < 3; i++) {
    if (decimal->bits[i]) {
      result++;
    }
  }

  return result;
}

double s21_convert_decimal_mantisa_to_double(s21_decimal dec) {
  uint32_t current_bits = 0;
  int current_bits_index = 0;
  double converted_value_buffer_result = 0;

  current_bits = dec.bits[0];
  for (int i = 0; i < 95; i++) {
    if (i == 32) {
      current_bits = dec.bits[1];
      current_bits_index = i - 32;
    }
    if (i == 64) {
      current_bits = dec.bits[2];
      current_bits_index = i - 64;
    }

    if ((current_bits >> current_bits_index) & 1) {
      converted_value_buffer_result += pow(2, i);
    }

    current_bits_index++;
  }

  return converted_value_buffer_result;
}

s21_FloatDescriptor_t s21_get_float_data(s21_FloatUint32_t float_box) {
  s21_FloatDescriptor_t result_descriptor = {0};
  int scale = 0;
  uint32_t int_value = 0;
  double temp_value = 0;

  result_descriptor.is_minus_sign = s21_get_float_sign(float_box.uint_value);
  if (result_descriptor.is_minus_sign) {
    float_box.float_value = -float_box.float_value;
  }

  temp_value = (double)float_box.float_value;

  while (temp_value != 0 && temp_value < 1e6) {
    temp_value *= 10.0;
    //
    //printf("grow up value is %lf\n", temp_value);
    //
    scale--;
  }

  while (temp_value >= 1e7) {
    temp_value /= 10.0;
    //
    //printf("grow down value is %lf\n", temp_value);
    //
    scale++;
  }

  int_value = (uint32_t)round(temp_value);

  while (!(int_value % 10)) {
    int_value /= 10;
    scale++;
  }

  printf("double value = %lf & result value = %u & scale = %d\n", temp_value,
         int_value, scale);

  result_descriptor.scale = scale;
  result_descriptor.mantisa = int_value;

  return result_descriptor;
}

double s21_get_multiplied_result(double decimal_mantissa_value) {
  return (double)decimal_mantissa_value * 10;
}

double s21_get_frac_result(double decimal_mantissa_value) {
  return (double)decimal_mantissa_value / 10;
}

float s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, double double_float_box) {
  int scale = 0;
  double result_value = 0;
  double (*operation)(double) = NULL;

  result_value = double_float_box;

  scale = float_descriptor->scale;

  if (scale < 0) {
    scale = -scale;
    operation = s21_get_frac_result;
  } else {
    operation = s21_get_multiplied_result;
  }

  for (int i = 0; i < scale; i++) {
    result_value = operation(result_value);
  }

  if (float_descriptor->is_minus_sign) {
    result_value = -result_value;
  }

  return (float)result_value;
}