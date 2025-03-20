#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return S21_ERROR_CONVERT;
  }
  int scale = s21_get_scale(&src);
  long long mantissa = (long long)src.bits[0] | ((long long)src.bits[1] << 32);

  float result = (float)mantissa / powf(10, scale);
  if (s21_get_sign(&src)) {
    result = -result;
  }
  *dst = result;
  return S21_OK;
}
