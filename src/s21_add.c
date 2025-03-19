#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (!result) return S21_ERROR_CONVERT;
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