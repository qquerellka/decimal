#include "s21_float_parsers.h"

#include "s21_utils.h"

static void s21_initialize_decimal_as_zero(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

static int s21_is_decimal_overflow_float(s21_decimal *decimal) {
  int result = 0;

  if (decimal->bits[0] > FLOAT_MANTISA_MAXIMUM_MASK) {
    result++;
  }

  for (int i = 1; i < 3; i++) {
    if (decimal->bits[i] != 0) {
      result++;
    }
  }

  return result;
}

static void s21_set_float_mantisa_in_decimal(s21_decimal *dst,
                                             uint32_t uint_value) {
  dst->bits[0] = uint_value;
}

static int s21_is_decimal_not_zero(s21_decimal *decimal) {
  int result = 0;

  for (int i = 0; i < 3; i++) {
    if (decimal->bits[i]) {
      result++;
    }
  }

  return result;
}

int from_f_to_d(float src, s21_decimal *dst) {
  int result_to_decimal = 0;
  int is_nan = 0;
  int is_zero = 0;
  int is_float_overflow_decimal = 0;
  int is_float_is_too_small = 0;
  s21_FloatUint32_t float_box = {0};
  s21_FloatDescriptor_t float_descriptor = {0};

  s21_initialize_decimal_as_zero(dst);

  float_box = s21_pack_float_in_int_box(src);

  is_nan = s21_is_float_nan(float_box);

  if (is_nan) {
    result_to_decimal = 1;
  } else {
    is_zero = s21_is_float_zero(float_box);
    is_float_overflow_decimal = s21_is_float_overflow((double)src);
    is_float_is_too_small = s21_is_float_too_small((double)src);

    if (!is_zero && !is_float_overflow_decimal && !is_float_is_too_small) {
      float_box.float_value = s21_round_float_to_7(src);

      float_descriptor = s21_get_float_data(float_box.uint_value);

      s21_set_sign(dst, (int)float_descriptor.is_minus_sign);

      s21_set_scale(dst, (int)float_descriptor.scale);

      s21_set_float_mantisa_in_decimal(dst, float_descriptor.mantisa);
    } else if (is_float_overflow_decimal) {
      result_to_decimal = 1;
      // src=0;??//оставшийся вопрос
    } else if (is_float_is_too_small) {
      result_to_decimal = 1;
    }
  }

  return result_to_decimal;
}

int from_d_to_f(s21_decimal src, float *dst) {
  int result_to_float = 0;
  int is_decimal_not_zero = 0;
  int is_decimal_overflow_float_mantisa = 0;  //
  s21_FloatDescriptor_t float_descriptor = {0};
  s21_FloatUint32_t float_box = {0};
  *dst = 0;

  if (dst) {
    is_decimal_not_zero = s21_is_decimal_not_zero(&src);
    is_decimal_overflow_float_mantisa = s21_is_decimal_overflow_float(&src);

    if (is_decimal_not_zero) {
      if (!is_decimal_overflow_float_mantisa) {
        float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);

        float_descriptor.scale = (unsigned char)s21_get_scale(&src);

        float_descriptor.mantisa = src.bits[0];

        s21_convert_float_descriptor_to_float(&float_descriptor, &float_box);

        *dst = float_box.float_value;
      } else {
        result_to_float = 1;
      }
    }
  } else {
    result_to_float = 1;
  }

  return result_to_float;
}