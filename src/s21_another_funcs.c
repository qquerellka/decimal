#include "s21_decimal.h"

int s21_get_scale(const s21_decimal *decimal) {
  return (decimal->bits[3] >> 16) & 0xFF;
}

void s21_set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= ~(0xFF << 16);
  decimal->bits[3] |= (scale & 0xFF) << 16;
}

int s21_get_sign(s21_decimal *decimal) {
  return ((unsigned int)decimal->bits[3] >> 31) & 1;
}

void s21_set_sign(s21_decimal *decimal, int sign) {
  if (sign) {
    decimal->bits[3] |= (1U << 31);
  } else {
    decimal->bits[3] &= ~(1U << 31);
  }
}

int s21_is_zero(s21_decimal *value) {
  return (value->bits[0] == 0 && value->bits[1] == 0 && value->bits[2] == 0);
}

int s21_mul_by_10(s21_decimal *value) {
  uint64_t temp = 0;
  uint64_t carry = 0;

  for (int i = 0; i < 3; i++) {
    temp = (uint64_t)value->bits[i] * 10 + carry;
    value->bits[i] = (uint32_t)(temp & 0xFFFFFFFF);
    carry = temp >> 32;
  }

  if (carry) {
    return 0;
  }

  int scale = (value->bits[3] >> 16) & 0xFF;
  if (scale < 28) {
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= (scale + 1) << 16;
  } else {
    return 0;
  }

  return 1;
}

int s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);

  while (scale1 < scale2) {
    if (!s21_mul_by_10(value_1)) return 0;
    scale1++;
  }
  while (scale2 < scale1) {
    if (!s21_mul_by_10(value_2)) return 0;
    scale2++;
  }
  return 1;
}

int s21_div_by_ten(s21_decimal *value) {
  uint64_t temp = 0;
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; i--) {
    temp = (uint64_t)(value->bits[i]) + (remainder << 32);
    value->bits[i] = (uint32_t)(temp / 10);
    remainder = temp % 10;
  }
  return (uint32_t)remainder;
}

void s21_set_bit(s21_decimal *value, unsigned bit, int set) {
  int word = bit / 32;
  int position = bit % 32;
  if (set) {
    value->bits[word] |= (1u << position);
  } else {
    value->bits[word] &= ~(1u << position);
  }
}

void s21_left_shift(s21_decimal *value) {
  int carry_prev = 0;
  for (int i = 0; i < 3; i++) {
    int carry = (value->bits[i] >> 31) & 1;
    value->bits[i] <<= 1;
    value->bits[i] |= carry_prev;
    carry_prev = carry;
  }
}

int s21_get_bit(s21_decimal value, unsigned bit) {
  int word = bit / 32;
  int position = bit % 32;
  return (value.bits[word] >> position) & 1;
}

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

  result = (double_value > S21_MAX);

  return result;
}

int s21_is_float_too_small(double double_value) {
  int result = 0;

  if (double_value < 0) {
    double_value = -double_value;
  }

  result = (int)(double_value < FLOAT_TOO_SMALL);

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
  char sprintf_buffer[16] = {0};
  double temp_value = 0;

  result_descriptor.is_minus_sign = s21_get_float_sign(float_box.uint_value);
  if (result_descriptor.is_minus_sign) {
    float_box.float_value = -float_box.float_value;
  }

  sprintf(sprintf_buffer, "%.6E", (double)float_box.float_value);

  sscanf(sprintf_buffer, "%lf", &temp_value);

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