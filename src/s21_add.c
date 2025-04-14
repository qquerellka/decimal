#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_ERROR_CONVERT;
  *result = (s21_decimal){0};

  int sign1 = s21_get_sign(&value_1);

  if (!s21_normalize(&value_1, &value_2)) {
    return S21_ERROR_CONVERT;
  }
  int target_scale = s21_get_scale(&value_1);

  uint64_t temp_sum = 0;
  uint32_t carry = 0;

  for (int i = 0; i < 3; i++) {
    temp_sum = (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + carry;
    result->bits[i] = (uint32_t)(temp_sum & 0xFFFFFFFF);
    carry = (uint32_t)(temp_sum >> 32);
  }
  s21_set_sign(result, sign1);
  s21_set_scale(result, target_scale);

  if (carry) return sign1 ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;

  return S21_OK;
}
