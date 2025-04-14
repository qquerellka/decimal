#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_to_float = 0;
  int is_decimal_not_zero = 0;
  s21_FloatDescriptor_t float_descriptor = {0};
  double float_buffer = 0;

  if (dst) {
    *dst = 0;
    is_decimal_not_zero = s21_is_decimal_not_zero(&src);

    if (is_decimal_not_zero) {
      float_buffer = s21_convert_decimal_mantisa_to_double(src);

      float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);

      float_descriptor.scale = (unsigned char)s21_get_scale(&src);

      *dst = s21_convert_float_descriptor_to_float(&float_descriptor,
                                                   float_buffer);
    }

  } else {
    result_to_float = 1;
  }

  return result_to_float;
}