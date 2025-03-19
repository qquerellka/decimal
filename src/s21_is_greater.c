#include "s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    for (int i = 2; i >= 0; i--) {
      if (a.bits[i] > b.bits[i]) return S21_TRUE;
      if (a.bits[i] < b.bits[i]) return S21_FALSE;
    }
    return S21_FALSE;
  }
  