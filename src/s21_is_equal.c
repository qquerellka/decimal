#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_is_zero(&value_1) && s21_is_zero(&value_2)) {
    return S21_TRUE;
  }

  if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) {
    return S21_FALSE;
  }

  if (!s21_normalize(&value_1, &value_2)) {
    return S21_FALSE;
  }

  for (int i = 0; i < 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      return S21_FALSE;
    }
  }

  return S21_TRUE;
}
