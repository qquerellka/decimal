#include "s21_decimal.h"

#include <stdint.h>

// Получение масштаба (биты 16-23 в bits[3])
int s21_get_scale(const s21_decimal *decimal) {
    return (decimal->bits[3] >> 16) & 0xFF;
  }
  
  // Установка масштаба (биты 16-23 в bits[3])
  void s21_set_scale(s21_decimal *decimal, int scale) {
    decimal->bits[3] &= ~(0xFF << 16);
    decimal->bits[3] |= (scale & 0xFF) << 16;
  }
  
  // Получение знака (бит 31 в bits[3])
  int s21_get_sign(s21_decimal *decimal) {
    return ((unsigned int)decimal->bits[3] >> 31) & 1;
  }
  
  // Установка знака (бит 31 в bits[3])
  void s21_set_sign(s21_decimal *decimal, int sign) {
    if (sign) {
      decimal->bits[3] |= (1U << 31);
    } else {
      decimal->bits[3] &= ~(1U << 31);
    }
  }
  
  int s21_is_overflow(s21_decimal value) {
    s21_decimal max_value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    return (value.bits[2] > max_value.bits[2] ||
            (value.bits[2] == max_value.bits[2] &&
             value.bits[1] > max_value.bits[1]) ||
            (value.bits[2] == max_value.bits[2] &&
             value.bits[1] == max_value.bits[1] &&
             value.bits[0] > max_value.bits[0]));
  }
  
  int s21_is_greater(s21_decimal a, s21_decimal b) {
    for (int i = 2; i >= 0; i--) {
      if (a.bits[i] > b.bits[i]) return 1;
      if (a.bits[i] < b.bits[i]) return 0;
    }
    return 0;
  }
  
  int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == NULL) {
      return S21_FALSE;
    }
    dst->bits[0] = abs(src);
    dst->bits[2] = dst->bits[1] = 0;
    s21_set_scale(dst, 0);
    s21_set_sign(dst, src < 0);
    return S21_OK;
  }
  
  int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst == NULL || isnan(src) || isinf(src) || src >= S21_MAX ||
        src <= S21_MIN) {
      return S21_FALSE;
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
  
  int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (dst == NULL) {
      return S21_FALSE;
    }
    int scale = s21_get_scale(&src);
    long long mantissa = (long long)src.bits[0] | ((long long)src.bits[1] << 32);
  
    for (int i = 0; i < scale; i++) {
      mantissa /= 10;
    }
    if (s21_get_sign(&src)) {
      mantissa = -mantissa;
    }
    if (mantissa > INT_MAX || mantissa < INT_MIN) {
      return S21_FALSE;
    }
    *dst = (int)mantissa;
    return S21_OK;
  }
  
  int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    if (dst == NULL) {
      return S21_FALSE;
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
  
  int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (!result) return S21_FALSE;
    *result = (s21_decimal){0};
  
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    int scale1 = s21_get_scale(&value_1);
    int scale2 = s21_get_scale(&value_2);
    int target_scale = (scale1 > scale2) ? scale1 : scale2;
  
    if (sign1 == sign2) {
      uint64_t temp_sum = 0;
      uint32_t carry = 0;
  
      for (int i = 0; i < 3; i++) {
        temp_sum = (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + carry;
        result->bits[i] = (uint32_t)(temp_sum & 0xFFFFFFFF);
        carry = (uint32_t)(temp_sum >> 32);
      }
  
      if (carry) return sign1 ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;
      s21_set_sign(result, sign1);
    } else {
      s21_set_sign(&value_2, sign1);
      return s21_sub(value_1, value_2, result);
    }
  
    s21_set_scale(result, target_scale);
    return S21_OK;
  }
  
  int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (!result) return S21_FALSE;
    *result = (s21_decimal){0};
  
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    int scale1 = s21_get_scale(&value_1);
    int scale2 = s21_get_scale(&value_2);
    int target_scale = (scale1 > scale2) ? scale1 : scale2;
  
    if (sign1 != sign2) {
      s21_set_sign(&value_2, sign1);
      return s21_add(value_1, value_2, result);
    }
  
    int greater =
        (value_1.bits[2] > value_2.bits[2]) ||
        (value_1.bits[2] == value_2.bits[2] &&
         value_1.bits[1] > value_2.bits[1]) ||
        (value_1.bits[2] == value_2.bits[2] &&
         value_1.bits[1] == value_2.bits[1] && value_1.bits[0] > value_2.bits[0]);
  
    s21_decimal max = greater ? value_1 : value_2;
    s21_decimal min = greater ? value_2 : value_1;
  
    uint64_t temp_sub = 0;
    int borrow = 0;
    for (int i = 0; i < 3; i++) {
      if (max.bits[i] >= min.bits[i] + borrow) {
        temp_sub = (uint64_t)max.bits[i] - min.bits[i] - borrow;
        borrow = 0;
      } else {
        temp_sub = (uint64_t)max.bits[i] + 0x100000000 - min.bits[i] - borrow;
        borrow = 1;
      }
      result->bits[i] = (uint32_t)temp_sub;
    }
  
    if (s21_is_overflow(*result)) return S21_NUMBER_MIN_INF;
  
    s21_set_sign(result, greater ? sign1 : !sign1);
    s21_set_scale(result, target_scale);
    return S21_OK;
  }