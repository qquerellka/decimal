#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_ERROR_CONVERT;
  if (s21_is_zero(&value_2)) return S21_DEV_BY_ZERO;
  *result = (s21_decimal){0};
  int sign_1 = s21_get_sign(&value_1);
  int sign_2 = s21_get_sign(&value_2);
  int result_sign = sign_1 ^ sign_2;
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);
  if (s21_is_equal(value_1, value_2)) {
    result->bits[0] = 1;
    s21_set_sign(result, result_sign);
    return S21_OK;
  }
  s21_decimal remainder = {0};
  s21_decimal quotient = {0};
  int scale = 0;
  while (s21_is_less(value_1, value_2) && scale < 28) {
    s21_mul_by_10(&value_1);
    scale++;
  }
  for (int i = 0; i < 96; i++) {
    s21_left_shift(&quotient);
    s21_left_shift(&remainder);
    if (s21_get_bit(value_1, 95 - i)) {
      s21_set_bit(&remainder, 0, 1);
    }

    if (s21_is_greater_or_equal(remainder, value_2)) {
      s21_sub(remainder, value_2, &remainder);
      s21_set_bit(&quotient, 0, 1);
    }
  }
  while (!s21_is_zero(&remainder) && scale < 28) {
    s21_mul_by_10(&remainder);
    s21_mul_by_10(&quotient);
    scale++;
    s21_decimal temp = {0};
    for (int i = 0; i < 10; i++) {
      if (s21_is_less(remainder, value_2)) break;
      s21_sub(remainder, value_2, &temp);
      remainder = temp;
      s21_add(quotient, (s21_decimal){{1, 0, 0, 0}}, &temp);
      quotient = temp;
    }
  }
  if (!s21_is_zero(&remainder) && scale == 28) {
    s21_decimal half = {0};
    s21_div(value_2, (s21_decimal){{2, 0, 0, 0}}, &half);
    if (s21_is_greater(remainder, half)) {
      s21_add(quotient, (s21_decimal){{1, 0, 0, 0}}, &quotient);
    }
  }
  *result = quotient;
  s21_set_sign(result, result_sign);
  s21_set_scale(result, scale);
  return S21_OK;
}
