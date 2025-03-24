#include "s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int sign1 = s21_get_sign(&value1);
  int sign2 = s21_get_sign(&value2);

  if (sign1 != sign2) {
    return sign1 ? S21_TRUE : S21_FALSE;
  }

  s21_normalize(&value1, &value2);

  if (s21_is_equal(value1, value2)) {
    return S21_FALSE;
  }

  for (int i = 2; i >= 0; i--) {
    if (value1.bits[i] > value2.bits[i]) {
      return sign1 ? S21_TRUE : S21_FALSE;
    }
    if (value1.bits[i] < value2.bits[i]) {
      return sign1 ? S21_FALSE : S21_TRUE;
    }
  }

  return S21_FALSE;
}