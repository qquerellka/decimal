#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst == NULL || isnan(src) || isinf(src) || src >= S21_MAX ||
        src <= S21_MIN) {
      return S21_ERROR_CONVERT;
    }
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  
    if (src < 0) {
      s21_set_sign(dst, 1);
      src = -src;
    }
  
    int scale = 0;
    while (scale < 28 && src - (long long)src != 0.0) {
      src *= 10;
      scale++;
    }
    unsigned long long mantissa = (unsigned long long)src;
  
    dst->bits[0] = (unsigned int)(mantissa & 0xFFFFFFFF);
    dst->bits[1] = (unsigned int)((mantissa >> 32) & 0xFFFFFFFF);
    dst->bits[2] = 0;
  
    s21_set_scale(dst, scale);
  
    return S21_OK;
  }
  
