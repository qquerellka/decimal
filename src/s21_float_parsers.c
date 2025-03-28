#include "s21_float_parsers.h"

#include <stdio.h>

#include "s21_utils.h"

static void s21_initialize_decimal_as_zero(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
}

static void s21_set_float_mantisa_in_decimal(s21_decimal *dst,
                                             uint32_t uint_value) {
  dst->bits[0] = uint_value;
}

int from_f_to_d(float src, s21_decimal *dst) {
  int result_to_decimal = 0;
  int is_nan = 0;
  int is_zero = 0;
  s21_FloatUint32_t float_box = {0};
  s21_FloatDescriptor_t float_descriptor = {0};

  s21_initialize_decimal_as_zero(dst);

  float_box = s21_pack_float_in_int_box(src);

  is_nan = s21_is_float_nan(float_box);
  //
  printf("is_nan = %d\n", is_nan);
  //
  if (is_nan) {
    result_to_decimal = 1;
  } else {
    is_zero = s21_is_float_zero(float_box);
    //
    printf("is zero = %d\n", is_zero);
    //
    if (!is_zero) {
      float_descriptor = s21_get_float_data(float_box.uint_value);

      s21_set_sign(dst, (int)float_descriptor.is_minus_sign);
      //
      printf("scale is = %d\n", float_descriptor.scale);
      //
      s21_set_scale(dst, (int)float_descriptor.scale);

      s21_set_float_mantisa_in_decimal(dst, float_descriptor.mantisa);
    }
  }

  return result_to_decimal;
}

int from_d_to_f(s21_decimal src, float *dst) {
  int result_to_float = 0;
  s21_FloatDescriptor_t float_descriptor = {0};
  s21_FloatUint32_t float_box = {0};

  float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);

  float_descriptor.scale = (unsigned char)s21_get_scale(&src);

  float_descriptor.mantisa = src.bits[0];

  s21_convert_float_descriptor_to_float(&float_descriptor, &float_box);

  *dst = float_box.float_value;

  return result_to_float;
}