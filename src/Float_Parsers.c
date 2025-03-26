#include "Float_Parsers.h"

#include <stdio.h>

#include "s21_decimal.h"

FloatUint32_t pack_float_in_int_box(float float_value) {
  FloatUint32_t result_box = {0};

  result_box.float_value = float_value;

  return result_box;
}

unsigned char get_float_sign(uint32_t float_box) {
  unsigned char result_sign = 0;
  unsigned char current_mask = 1;

  if (((float_box >> 31) & current_mask) == current_mask) result_sign = 1;

  return result_sign;
}

char get_float_scale(uint32_t float_box) {
  char result_scale = 0;

  float_box >>= FLOAT_MANTISA_BITS;

  result_scale = (float_box & FLOAT_GET_SIGN_MASK);
  result_scale -= FLOAT_SCALE_STEP;

  return result_scale;
}

unsigned get_float_mantissa(uint32_t float_box, unsigned char scale) {
  unsigned result_mantiss = 0;

  result_mantiss = float_box & FLOAT_MANTISA_MASK;

  if (scale) {
    result_mantiss |= FLOAT_SCALE_EXIST_MASK;
  }

  return result_mantiss;
}

FloatDescriptor_t get_float_data(uint32_t float_box) {
  FloatDescriptor_t result_descriptor = {0};

  result_descriptor.is_minus_sign = get_float_sign(float_box);
  result_descriptor.scale = get_float_scale(float_box);
  result_descriptor.mantissa =
      get_float_mantissa(float_box, result_descriptor.scale);

  return result_descriptor;
}

void convert_float_descriptor_to_decimal(FloatDescriptor_t *float_descriptor,
                                         s21_decimal *dst) {
  s21_set_sign(dst, (int)float_descriptor->is_minus_sign);

  s21_set_scale(dst, (int)float_descriptor->scale);

  dst->bits[0] = float_descriptor->mantissa;
}

int from_f_to_d(float src, s21_decimal *dst) {
  int result_to_decimal = 0;
  FloatUint32_t float_box = {0};
  FloatDescriptor_t float_descriptor = {0};

  float_box = pack_float_in_int_box(src);
  float_descriptor = get_float_data(float_box.uint_value);

  convert_float_descriptor_to_decimal(&float_descriptor, dst);

  return result_to_decimal;
}

void obtain_decimal_data_to_float_descriptor(
    FloatDescriptor_t *float_descriptor, s21_decimal *dst) {
  float_descriptor->is_minus_sign = (unsigned char)s21_get_sign(dst);

  float_descriptor->scale = (char)s21_get_scale(dst);

  float_descriptor->mantissa = dst->bits[0];
}

void set_float_sign(FloatDescriptor_t *float_descriptor, uint32_t *dst) {
  uint32_t tmp_int_map = 0;

  tmp_int_map = *dst;

  if (float_descriptor->is_minus_sign) {
    tmp_int_map = 1;
    tmp_int_map <<= FLOAT_SIGN_BIT;
  }

  *dst = tmp_int_map;
}

void set_float_scale(FloatDescriptor_t *float_descriptor, uint32_t *dst) {
  uint32_t scale_mask = 0;

  scale_mask = float_descriptor->scale;

  scale_mask += FLOAT_SCALE_STEP;

  scale_mask <<= FLOAT_MANTISA_BITS;

  *dst |= scale_mask;
}

void set_float_mantissa(FloatDescriptor_t *float_descriptor, uint32_t *dst) {
  uint32_t mantisa = 0;

  mantisa = float_descriptor->mantissa;

  if (float_descriptor->scale >= FLOAT_MAX_SCALE) {
    float_descriptor->scale = FLOAT_MAX_SCALE;
    float_descriptor->mantissa = 0;

  } else if (float_descriptor->scale <= FLOAT_MIN_SCALE) {
    float_descriptor->scale = FLOAT_MIN_SCALE;
    float_descriptor->mantissa = 0;
  } else {
    mantisa <<= FLOAT_MANTISA_SHIFT;
    mantisa >>= FLOAT_MANTISA_SHIFT;

    *dst |= mantisa;
  }
}

void convert_float_descriptor_to_float(FloatDescriptor_t *float_descriptor,
                                       FloatUint32_t *dst) {
  set_float_sign(float_descriptor, &dst->uint_value);

  set_float_scale(float_descriptor, &dst->uint_value);

  set_float_mantissa(float_descriptor, &dst->uint_value);
}

int from_d_to_f(s21_decimal src, float *dst) {
  int result_to_float = 0;
  FloatDescriptor_t float_descriptor = {0};
  FloatUint32_t float_box = {0};

  obtain_decimal_data_to_float_descriptor(&float_descriptor, &src);
  convert_float_descriptor_to_float(&float_descriptor, &float_box);

  *dst = float_box.float_value;

  return result_to_float;
}